#pragma once
#include "stdafx.h"
#include "Operate.h"
#include "Convertstr.h"
#include "mysql.h"

MYSQL m_sqlCon;

Operate::Operate()
{
	CString  pStrtolerate;
	int nSize = 254;
	GetPrivateProfileString("Setting", "tolerate", NULL, pStrtolerate.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini"); //配置文件中读取tolerate
	tolerate = atoi(pStrtolerate);
	pStrtolerate.ReleaseBuffer();
}

Operate::~Operate()
{
}

/***********************************************************************
* DESCRIPTION:读取txt文件
* Returns: 是否成功读取
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
int Operate::Readfile()
{
	CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY, "*.*|*.*||");
	CString csFileName;
	CString str;
//	CString pStrOut;
	CString No;//指纹机自动生成的流水编号
	CString Mchn;//指纹机编号
	CString EnNo;//对应每个考勤人员的编号
	CString Name;//考勤人员姓名
	CString DateTime;// 打卡日期和具体时间。
	if (dlg.DoModal() == IDOK)
	{
		csFileName = dlg.GetPathName(); //选择的文件路径
	}
	if (strlen(csFileName) == 0)
	{
		return 0;
	}
	csFileName.Replace(_T("\\"), _T("\/\/"));
	char * pszFileName;
	CString address = csFileName;
	pszFileName = (LPSTR)(LPCTSTR)address;
	CStdioFile myFile;
	CFileException fileException;
	if (myFile.Open(pszFileName, CFile::typeText | CFile::modeReadWrite), &fileException)
	{
		ansi = 1; //utf -8 or ansi?
		myFile.SeekToBegin();
		while (myFile.ReadString(str))
		{
			wchar_t * vstr;//vstr unicode 行
			Convertstr conv;//新建utf-8->unicode->ansi实体
			int sBufSize = strlen(str);
			if (ansi == 0)
			{
				vstr = conv.UTF8ToUnicode(str);
				str = conv.UnicodeToANSI(vstr);
			}
			//AfxMessageBox(str);
			//读取的信息进行分解
			No = str.Mid(0, 6);
			Mchn = str.Mid(7, 1);
			EnNo = str.Mid(9, 9);
			Name = str.Mid(19, 9);
			Name.Replace(_T(" "), _T(""));
			DateTime = str.Right(17);
			Savetosql(No, Mchn, EnNo, Name, DateTime);
		}
		CString out;
		if (count > 0)
		{
			out.Format("%d", count);
			AfxMessageBox("受影响的行数：" + out);
		}
		count = 0;
	}
	else
	{
		TRACE("Can't open file %s,error=%u/n", pszFileName, fileException.m_cause);
	}
	myFile.Close();
	Exec(0);
	return 1;
}

/***********************************************************************
* DESCRIPTION:将数据存取到数据库
* Input:流水号、机器号、成员号、姓名、日期
* Returns: 是否成功执行
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
int Operate::Savetosql(CString No, CString Mchn, CString EnNo, CString Name, CString DateTime)
{
	CString Year, Month, Day;
	CString Hour, Minute;
	CString str;//SQl语句 
	Year = DateTime.Mid(0, 4);
	Month = DateTime.Mid(5, 2);
	Day = DateTime.Mid(8, 2);
	Hour = DateTime.Mid(12, 2);
	Minute = DateTime.Mid(15, 2);
	ConnectMySQL();
	/*条目用户信息核验*/
	if (Checkuser(EnNo, Name) == -1)
	{
		return 0;
	}
	str = "INSERT INTO signoridata VALUES(" + No + "," + Mchn + "," + EnNo + ",\"" + Name + "\",\"" + Year + "-" + Month + "-" + Day + "\",\"" + Hour + ":" + Minute + ":" + "00\")";
	mysql_query(&m_sqlCon, str);
	count += mysql_affected_rows(&m_sqlCon);//返回操作影响的行数  
											//AfxMessageBox(str);
	mysql_close(&m_sqlCon);//关闭Mysql连接
	return 1;
}

/***********************************************************************
* DESCRIPTION:用户查重：检查参数EnNo对应的名字是否和数据库中一样
* Input:成员号，姓名
* Returns: 是否成功执行
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
int Operate::Checkuser(CString EnNo, CString Name)
{
	st_mysql_res *  res;
	//mysql_free_result(res);
	//AfxMessageBox(EnNo);
	if (mysql_real_query(&m_sqlCon, "select Name from user where EnNo = " + EnNo, (unsigned long)strlen("select Name from user where EnNo = " + EnNo)))// 查询数据库中的"signoridata"表  
	{
		//AfxMessageBox("get");
		return 0;
	}
	res = mysql_store_result(&m_sqlCon);//得到存储结果集 
	if (NULL == res)//如果出错空则返回
	{
		//AfxMessageBox("space");
		return 0;
	}
	CString out;
	MYSQL_ROW row;
	if (row = mysql_fetch_row(res)) //行数据集为row
	{
		CString myreaddata(row[0]);//读row rols列
		if (myreaddata != Name)
		{
			AfxMessageBox("发现与成员列表记录不匹配的数据，导入即将取消");
			return -1;
		}
	}
	else
	{
		CString str;//SQl语句 
		str = "INSERT INTO user VALUES(" + EnNo + ", \"" + Name + "\")";
		mysql_query(&m_sqlCon, str);
		countu += mysql_affected_rows(&m_sqlCon);//返回操作影响的行数  
	}

	mysql_free_result(res);
	return 0;
}

/***********************************************************************
* DESCRIPTION:预处理：对源数据进行预处理，方便导出excel文件
* Input:参数
* Returns: 是否成功执行
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
int Operate::Exec(int pointer)
{
	AfxMessageBox("接下来进行数据预处理与整理，请耐心等待，这可能需要一点时间。");
	//AfxMessageBox(_T("数据库测试"));
	ConnectMySQL();
	CString str;
	CString tempNo, tempDate, tempTime;
	CString Day, Month, Year, Hour, Minute;
	str = "delete  FROM preprocess";
	mysql_real_query(&m_sqlCon, str, (unsigned long)strlen(str));//先清空预处理库
	str = "select * FROM signoridata";
	if (mysql_real_query(&m_sqlCon, str, (unsigned long)strlen(str)))// 查询数据库中的"signoridata"表  
	{
		return 0;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//得到存储结果集 
	if (NULL == res)//如果为空则返回
	{
		return 0;
	}
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res)) //行数据集为row
	{
		int rols;
		CString colname;
		for (rols = 2; rols < 6; rols++)
		{
			CString myreaddata(row[rols]);//读row rols列
			if (rols == 2)
			{
				tempNo = myreaddata;
			}
			if (rols == 4)
			{
				tempDate = myreaddata;
			}
			if (rols == 5)
			{
				tempTime = myreaddata;
			}
		}
		//读完一行数据，获取到3个变量
		//拆分，判断，存储。
		Hour = tempTime.Mid(0, 2);
		Minute = tempTime.Mid(3, 2);
		CString result = CheckTime(Hour, Minute);
		//写入主键等关键值
		CString strm;//SQl语句 
		CString week = GetWeek(tempDate);
		CString day = GetDay(tempDate);
		ConnectMySQL();
		strm = "INSERT INTO preprocess (Caseid,WeekNo,Week,EnNo,Date) VALUES (\"" + tempDate + tempNo + "\"," + week + "," + day + "," + tempNo + ",\"" + tempDate + "\")";
		mysql_query(&m_sqlCon, strm);
		mysql_close(&m_sqlCon);//关闭Mysql连接
		ConnectMySQL();
		if (result != "il")
		{
			//执行SQL ，写入预处理表
			CString str1;//SQl语句 
			str1 = "UPDATE preprocess SET " + result + "= \"" + Hour + ":" + Minute + ":00" + "\"  where Caseid = \"" + tempDate + tempNo + "\"";
			mysql_query(&m_sqlCon, str1);
		}
		mysql_close(&m_sqlCon);//关闭Mysql连接
	}
	mysql_free_result(res);
	mysql_close(&m_sqlCon);//关闭Mysql连接
	AfxMessageBox("就绪");
}

/***********************************************************************
* DESCRIPTION:查询某日期是周内第几天，周日是第一天
			需要已建立数据库连接。因为是依赖SQL查询
* Input: 日期（格式：YYYY-MM-DD）
* Returns: CString：本周第几天
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
CString Operate::GetDay(CString str) //Get 周内第几天
{
	ConnectMySQL();
	CString Day;
	CString sql;
	CString out;
	MYSQL_ROW row;
	sql = "select DAYOFWEEK(\"" + str + "\")";
	if (mysql_real_query(&m_sqlCon, sql, (unsigned long)strlen(sql)))// 查询数据库中的""表  
	{
		return 0;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//得到存储结果集 

	if (NULL == res)//如果为空则返回
	{
		return 0;
	}

	while (row = mysql_fetch_row(res)) //行数据集为row
	{
		CString myreaddata(row[0]);//读row rols列
		Day = myreaddata;
	}
	mysql_free_result(res);
	mysql_close(&m_sqlCon);//关闭Mysql连接
	return Day; //每周第一天是周日
}

/***********************************************************************
* DESCRIPTION:查询某日期在第几周
			需要已建立数据库连接。因为是依赖SQL查询
* Input: 日期（格式：YYYY-MM-DD）
* Returns: CString：周号
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
CString Operate::GetWeek(CString str)
{
	ConnectMySQL();
	CString Week;
	CString sql;
	CString out;
	MYSQL_ROW row;
	sql = "SELECT weekofyear(\"" + str + "\")";
	if (mysql_real_query(&m_sqlCon, sql, (unsigned long)strlen(sql)))// 查询数据库中的""表  
	{
		return 0;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//得到存储结果集 

	if (NULL == res)//如果为空则返回
	{
		return 0;
	}

	while (row = mysql_fetch_row(res)) //行数据集为row
	{
		CString myreaddata(row[0]);//读row rols列
		Week = myreaddata;//
						  //AfxMessageBox(Week);
	}
	mysql_free_result(res);
	mysql_close(&m_sqlCon);//关闭Mysql连接
	return Week;
}

/***********************************************************************
* DESCRIPTION:建立数据库连接
* Returns: 建立状态
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
int Operate::ConnectMySQL()
{
	CString pStrip, pStrdatabase, pStruser, pStrpassword, pStrport;
	int nSize = 254;
	GetPrivateProfileString("Database connection Info", "IP", NULL, pStrip.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini");
	GetPrivateProfileString("Database connection Info", "user", NULL, pStruser.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini");
	GetPrivateProfileString("Database connection Info", "password", NULL, pStrpassword.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini");
	GetPrivateProfileString("Database connection Info", "port", NULL, pStrport.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini");
	GetPrivateProfileString("Database connection Info", "database", NULL, pStrdatabase.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini");
	int port = atoi(pStrport);

	mysql_init(&m_sqlCon);
	if (!mysql_real_connect(&m_sqlCon, pStrip, pStruser, pStrpassword, pStrdatabase, port, NULL, 0))
	{
		AfxMessageBox(_T("访问数据库失败!"));
		CString e = mysql_error(&m_sqlCon);//需要将项目属性中字符集修改为“使用多字节字符集”或“未设置”  
		return 0;
	}
	else
	{
		mysql_query(&m_sqlCon, "SET NAMES 'GB2312'");//解决从数据库中读取数据后汉字乱码显示的问题  
	}
	return 0;
}

/***********************************************************************
* DESCRIPTION:时间合法性检查
* Input:CString 小时，CString 分钟
* Returns: 时间锁对应的签到点
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
CString Operate::CheckTime(CString hour, CString minute)//返回值是数据库的列名
{
	//上午两次（8:00-12:00），下午两次（14:00-18:00），晚上两次（19:00-22:00）
	//M、N、E分别对应早上下午晚上签到，ME、EE、EE分别对应早上下午晚上签退
	CString test;
	int h = atoi(hour);
	int m = atoi(minute);

	if (h == 8 || h == 14 || h == 19)//早上合法性判断
	{
		if (m <= tolerate)
		{
			switch (h)
			{
			case 8:
				return "M";//合法的早签到
				break;
			case 14:
				return "N";
				break;
			case 19:
				return "E";
				break;
			}
		}
	}
	if ((h >= 8 && h < 14))
	{
		return "ME";//合法的签退时间，m为实际签退分钟数
	}
	if ((h >= 14 && h < 19))
	{
		return "NE";//合法的签退时间，m为实际签退分钟数
	}
	if ((h >= 19 && h < 24))
	{
		return "EE";//合法的签退时间，m为实际签退分钟数
	}
	return "il";//return il 时间不合法
}

/***********************************************************************
* DESCRIPTION:导出到excel
* Input:CString 年，CString 月
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
void Operate::layoutxlsx(int GetYear, int GetMonth)
{
	int memnum;
	CString pStrFileName;//文件目录
	CString Getname, Getno;//查库得到的用户名和密码
	CString Weekno;//这个月开始的周号
				   //示例
	if (GetMonth < 1 || GetMonth>12)//非必要的数据正确性检查
	{
		AfxMessageBox("查询时间不合法");
		return;
	}
	CString Firstday;
	Firstday.Format("%d-%d", GetYear, GetMonth);
	CString fix = GetDay(Firstday + "-1");//获得第一天是周几，推算GetMonth第一个周是哪一天开始的
	int ifix = atoi(fix);
	CString Daystart;//格式形如 5，这个月第一个周开始的日子
	if (ifix == 1)
	{
		Daystart.Format("%d", 1);
	}
	else
	{
		Daystart.Format("%d", 9 - ifix);
	}
	Daystart = Firstday + "-" + Daystart;
	BROWSEINFO stInfo = { NULL };//下面是路径选择
	LPCITEMIDLIST pIdlst;
	TCHAR szPath[MAX_PATH];
	stInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
	stInfo.lpszTitle = "注意！\n文件会默认以YYYY-MM的形式命名。";
	pIdlst = SHBrowseForFolder(&stInfo);
	if (!pIdlst)
		return;
	if (!SHGetPathFromIDList(pIdlst, szPath))
		return;
	//Excel表格内容初始化
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		return;
	}
	books = app.get_Workbooks();
	book = books.Add(covOptional);
	sheets = book.get_Worksheets();
	NewSheet(sheets);
	sheet = sheets.get_Item(COleVariant((short)5)); //换sheet5
	FillOne(sheet, "A1", "实验室" + Firstday + "签到汇总表");
	FillOne(sheet, "A2", "姓名\\周");
	FillOne(sheet, "B2", "第一周");
	FillOne(sheet, "C2", "第二周");
	FillOne(sheet, "D2", "第三周");
	FillOne(sheet, "E2", "第四周");
	FillOne(sheet, "F2", "本月合计");
	for (short vsheet = 1; vsheet <= 4; vsheet++)
	{
		CString vsheetprint;
		vsheetprint.Format("%d", vsheet);
		CString pWeektop = "实验室第" + vsheetprint + "周签到表";
		sheet = sheets.get_Item(COleVariant((short)vsheet)); //换sheet
		FillOne(sheet, "A2", "姓名");
		Merge(sheet, "F1", "I1");
		FillOne(sheet, "F1", pWeektop);
		Merge(sheet, "C2", "D2");
		FillOne(sheet, "C2", "周一");
		Merge(sheet, "E2", "F2");
		FillOne(sheet, "E2", "周二");
		Merge(sheet, "G2", "H2");
		FillOne(sheet, "G2", "周三");
		Merge(sheet, "I2", "J2");
		FillOne(sheet, "I2", "周四");
		Merge(sheet, "K2", "L2");
		FillOne(sheet, "K2", "周五");
		Merge(sheet, "M2", "N2");
		FillOne(sheet, "M2", "周六");
		Merge(sheet, "O2", "P2");
		FillOne(sheet, "O2", "周日");
		FillOne(sheet, "Q2", "周合计");		
		ConnectMySQL();//下面是每个表的人数循环
		CString sql;
		MYSQL_ROW row;
		sql = "SELECT * from user";
		if (mysql_real_query(&m_sqlCon, sql, (unsigned long)strlen(sql)))// 查询数据库中的""表  
		{
			return;
		}
		st_mysql_res *  res = mysql_store_result(&m_sqlCon);//得到存储结果集 
		if (NULL == res)//如果为空则返回
		{
			return;
		}
		memnum = 0;
		while (row = mysql_fetch_row(res)) //行数据集为row
		{
			for (int rols = 0; rols < 2; rols++)//这里注意要同时读到
			{
				CString myreaddata(row[rols]);//读row rols列
				if (rols == 0)
				{
					Getno = myreaddata;
				}
				if (rols == 1)
				{
					Getname = myreaddata;
				}
			}//致此已经获得了一表的一名字和号码，进行循环绘制，以及内容计算填充
			int header = 3 + memnum * 4;	//每个用户的第一栏列坐标是3+4*n
			CString headaddress, endaddress;
			headaddress.Format("%d", header);//第一行数
			endaddress.Format("%d", header + 4);//最后行数
			CString Namecl = "A" + headaddress;//名字地址
			CString Namecle = "A" + endaddress;
			CString Totalcl = "Q" + headaddress;//总计地址
			CString Totalcle = "Q" + endaddress;
			range = sheet.get_Range(COleVariant(Namecl), COleVariant(Namecl));//range定制范围
			Merge(sheet, Namecl, Namecle);
			FillOne(sheet, Namecl, Getname);
			//AfxMessageBox(Getname);
			for (int t = 0; t < 4; t++)//填充早午晚合计
			{
				CString Filler, Filler2, Fillin;
				Filler.Format("%d", t + header);
				Filler2 = Filler;
				Filler = "B" + Filler;
				range = sheet.get_Range(COleVariant(_T(Filler)), COleVariant(_T(Filler)));//range定制范围
				if (t == 0)
				{
					Fillin = "早";
				}
				if (t == 1)
				{
					Fillin = "午";
				}
				if (t == 2)
				{
					Fillin = "晚";
				}
				if (t == 3)
				{
					Fillin = "合计";
					//合并单日合计
					Merge(sheet, "C" + Filler2, "D" + Filler2);
					Merge(sheet, "E" + Filler2, "F" + Filler2);
					Merge(sheet, "G" + Filler2, "H" + Filler2);
					Merge(sheet, "I" + Filler2, "J" + Filler2);
					Merge(sheet, "K" + Filler2, "L" + Filler2);
					Merge(sheet, "M" + Filler2, "N" + Filler2);
					Merge(sheet, "O" + Filler2, "P" + Filler2);
				}
				range.put_Value2(COleVariant(Fillin));	//填入早午晚

			}
			//memnum++;
			//接下来应该根据数据库来按照本月第一周，读取一周内的情况，每个月也就4个周
			//已知信息 no。week号，第一天，查询当天的数据

			Weekno = GetWeek(Daystart);
			int vWeekno = atoi(Weekno);//将这个月开始的周号转换为int
			vWeekno = vsheet + vWeekno;
			Weekno.Format("%d", vWeekno);
			CString pRealLocate, pStrTotalColEnd;
			for (int tday = 1; tday < 8; tday++)
			{
				CString sqltemp;
				CString uday;
				CString M, ME, N, NE, E, EE;
				M = "";
				ME = "";
				NE = "";
				N = "";
				E = "";
				EE = "";
				CString MF, NF, EF;
				MYSQL_ROW rowtemp;
				uday.Format("%d", tday);
				ConnectMySQL();
				sqltemp = "SELECT * from preprocess where EnNo = " + Getno + " and Weekno = " + Weekno + " and week = " + uday;
				//AfxMessageBox(sqltemp);
				int Getnoi = atoi(Getno);
				if (mysql_real_query(&m_sqlCon, sqltemp, (unsigned long)strlen(sqltemp)))// 查询数据库中的""表  
				{
					return;
				}
				st_mysql_res *  restemp = mysql_store_result(&m_sqlCon);//得到存储结果集 
				mysql_free_result(restemp);
				if (NULL == restemp)//如果为空则返回
				{
					return;
				}
				CString pStrIntervalFunc = "=TEXT((AND(MST<>\"\",MEN<>\"\")*(MEN-MST)+AND(NST<>\"\",NEN<>\"\")*(NEN-NST)+AND(EST<>\"\",EEN<>\"\")*(EEN-EST)),\"[h]:mm\")";
				//AfxMessageBox(pStrIntervalFunc);
				while (rowtemp = mysql_fetch_row(restemp)) //行数据集为row
				{
					for (int temp = 4; temp < 10; temp++)
					{
						CString myreaddata(rowtemp[temp]);//读row rols列
						if (temp == 4)
						{

							M = myreaddata;
							pRealLocate.Format("%d", memnum * 4 + 3);
							pStrIntervalFunc.Replace("MST", GetRealCol(uday, temp) + pRealLocate);
							FillOne(sheet, GetRealCol(uday, temp) + pRealLocate, M);
						}
						if (temp == 5)
						{
							ME = myreaddata;
							pRealLocate.Format("%d", memnum * 4 + 3);
							pStrIntervalFunc.Replace("MEN", GetRealCol(uday, temp) + pRealLocate);
							FillOne(sheet, GetRealCol(uday, temp) + pRealLocate, ME);
						}
						if (temp == 6)
						{
							N = myreaddata;
							pRealLocate.Format("%d", memnum * 4 + 4);
							pStrIntervalFunc.Replace("NST", GetRealCol(uday, temp) + pRealLocate);
							FillOne(sheet, GetRealCol(uday, temp) + pRealLocate, N);

						}
						if (temp == 7)
						{
							NE = myreaddata;
							pRealLocate.Format("%d", memnum * 4 + 4);
							pStrIntervalFunc.Replace("NEN", GetRealCol(uday, temp) + pRealLocate);
							FillOne(sheet, GetRealCol(uday, temp) + pRealLocate, NE);
						}
						if (temp == 8)
						{
							E = myreaddata;
							pRealLocate.Format("%d", memnum * 4 + 5);
							pStrIntervalFunc.Replace("EST", GetRealCol(uday, temp) + pRealLocate);
							FillOne(sheet, GetRealCol(uday, temp) + pRealLocate, E);
						}
						if (temp == 9)
						{
							EE = myreaddata;
							pRealLocate.Format("%d", memnum * 4 + 5);
							pStrIntervalFunc.Replace("EEN", GetRealCol(uday, temp) + pRealLocate);
							FillOne(sheet, GetRealCol(uday, temp) + pRealLocate, EE);
						}
					}
				}
				//读到所有参数，计算，填表
				pRealLocate.Format("%d", memnum * 4 + 6);//单元格坐标控制在最后一行上							
				int nFirstTag = 0;
				if (pStrIntervalFunc == "=TEXT((AND(MST<>\"\",MEN<>\"\")*(MEN-MST)+AND(NST<>\"\",NEN<>\"\")*(NEN-NST)+AND(EST<>\"\",EEN<>\"\")*(EEN-EST)),\"[h]:mm\")")
				{
					pStrIntervalFunc = "";
				}
				//填充求时间差
				FillOne(sheet, GetRealCol(uday, 0) + pRealLocate, pStrIntervalFunc);
				mysql_close(&m_sqlCon);
			}//以上是周一到周日的循环
			pRealLocate.Format("%d", memnum * 4 + 3);//单元格坐标控制在最后一行上	
			pStrTotalColEnd.Format("%d", memnum * 4 + 6);
			//填入SUM
			CString pStrSumFunc;
			pStrSumFunc = "=TEXT((VALUE(Cblank+Eblank+Gblank+Iblank+Kblank+Mblank+Oblank)),\"[h]:mm:ssS\")";
			pStrSumFunc.Replace("blank", pStrTotalColEnd);
			FillOne(sheet, "Q" + pStrTotalColEnd, pStrSumFunc);
			sheet = sheets.get_Item(COleVariant((short)5)); //换sheet5
			CString pStrRownum, pStrTotalFunc, pStrMonthTotalFunc;
			pStrRownum.Format("%d", memnum + 3);
			pStrTotalFunc = "=第X周!Q" + pStrTotalColEnd;
			pStrTotalColEnd = WeekToCol(vsheet) + pStrRownum;
			switch (vsheet)
			{
			case 1:
				pStrTotalFunc.Replace("X", "一");
			case 2:
				pStrTotalFunc.Replace("X", "二");
			case 3:
				pStrTotalFunc.Replace("X", "三");
			case 4:
				pStrTotalFunc.Replace("X", "四");
			}
			pStrMonthTotalFunc = "=TEXT(SUM(VALUE(Baddress+Caddress+Daddress+Eaddress)),\"[h]:mm:ss\")";
			pStrMonthTotalFunc.Replace("address", pStrRownum);
			FillOne(sheet, "A" + pStrRownum, Getname);
			FillOne(sheet, "F" + pStrRownum, pStrMonthTotalFunc);
			FillOne(sheet, pStrTotalColEnd, pStrTotalFunc);
			memnum++;//成员数+1
			sheet = sheets.get_Item(COleVariant((short)vsheet)); //换vsheet
		}
		mysql_free_result(res);
		mysql_close(&m_sqlCon);//关闭Mysql连接
	}
	app.put_Visible(TRUE);
	app.put_UserControl(FALSE); 
	pStrFileName.Format(_T("%s"), szPath);
	book.SaveAs(COleVariant(pStrFileName +"\\"+Firstday + ".xlsx"), covOptional, covOptional,
		covOptional, covOptional, covOptional, 0,
		covOptional, covOptional, covOptional, covOptional, covOptional, covOptional); 
}

/***********************************************************************
* DESCRIPTION:在新的xlsx文件中添加新的sheet
* Input:WorkSheets
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
void Operate::NewSheet(CWorksheets sheets) //创建新的excel表后，添加sheets
{
	const char * week1 = "第一周";
	const char * week2 = "第二周";
	const char * week3 = "第三周";
	const char * week4 = "第四周";
	const char * weeks = "周汇总";
	sheet = sheets.get_Item(COleVariant((short)1));
	sheets.Add(vtMissing, _variant_t(sheet), COleVariant((short)4), vtMissing);
	sheet.put_Name(week1);
	sheet = sheets.get_Item(COleVariant((short)2));
	sheet.put_Name(week2);
	sheet = sheets.get_Item(COleVariant((short)3));
	sheet.put_Name(week3);
	sheet = sheets.get_Item(COleVariant((short)4));
	sheet.put_Name(week4);
	sheet = sheets.get_Item(COleVariant((short)5));
	sheet.put_Name(weeks);
	/*
	//sheet1后新建3个表
	//range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("B1")));//range定制范围
	//range.put_Value2(COleVariant(temp));//填充数值
	//range.Merge(_variant_t(1));//合并range的单元格
	//为sheet设定名字

	*/
}

/***********************************************************************
* DESCRIPTION:填充单元格
* Input:Worksheet，地址，内容
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
void Operate::FillOne(CWorksheet pSheet, CString pAddress, CString pValue)
{
	CRange rangetemp;
	rangetemp = pSheet.get_Range(COleVariant(pAddress), COleVariant(pAddress));
	rangetemp.put_Value2(COleVariant(pValue));
}

/***********************************************************************
* DESCRIPTION:合并目标单元格
* Input:Worksheet，起始单元格，目标单元格
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
void Operate::Merge(CWorksheet pSheet, CString pFrom, CString pTo)
{
	CRange rangetemp;
	rangetemp = sheet.get_Range(COleVariant(pFrom), COleVariant(pTo));//range定制范围
	rangetemp.Merge(_variant_t(1));//合并range的单元格
}

/***********************************************************************
* DESCRIPTION:获取对应的列号
* Input:周号，签到/签退
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
CString Operate::GetRealCol(CString pWeek, int E)
{
	if (pWeek == "2")
	{
		if (E % 2 == 0)
		{
			return "C";
		}
		else
		{
			return "D";
		}
	}
	if (pWeek == "3")
	{
		if (E % 2 == 0)
		{
			return "E";
		}
		else
		{
			return "F";
		}
	}
	if (pWeek == "4")
	{
		if (E % 2 == 0)
		{
			return "G";
		}
		else
		{
			return "H";
		}
	}
	if (pWeek == "5")
	{
		if (E % 2 == 0)
		{
			return "I";
		}
		else
		{
			return "J";
		}
	}
	if (pWeek == "6")
	{
		if (E % 2 == 0)
		{
			return "K";
		}
		else
		{
			return "L";
		}
	}
	if (pWeek == "7")
	{
		if (E % 2 == 0)
		{
			return "M";
		}
		else
		{
			return "N";
		}
	}
	if (pWeek == "1")
	{
		if (E % 2 == 0)
		{
			return "O";
		}
		else
		{
			return "P";
		}
	}
	return CString();
}

/***********************************************************************
* DESCRIPTION:获取对应的列号
* Input:Worksheet，起始单元格，目标单元格
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
CString Operate::WeekToCol(int iWeek)// 表格填充时，sheet5将周转列号
{
	CString pStrRealCol;
	switch (iWeek)
	{
	default:
		return "";
		break;
	case 1:
		return "B";
	case 2:
		return "C";
	case 3:
		return "D";
	case 4:
		return "E";
	case 5:
		return "F";
	}
}
