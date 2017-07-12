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
	GetPrivateProfileString("Setting", "tolerate", NULL, pStrtolerate.GetBuffer(254), nSize, "C:\\Program Files\\DBSetting.ini"); //�����ļ��ж�ȡtolerate
	tolerate = atoi(pStrtolerate);
	pStrtolerate.ReleaseBuffer();
}

Operate::~Operate()
{
}

/***********************************************************************
* DESCRIPTION:��ȡtxt�ļ�
* Returns: �Ƿ�ɹ���ȡ
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
	CString No;//ָ�ƻ��Զ����ɵ���ˮ���
	CString Mchn;//ָ�ƻ����
	CString EnNo;//��Ӧÿ��������Ա�ı��
	CString Name;//������Ա����
	CString DateTime;// �����ں;���ʱ�䡣
	if (dlg.DoModal() == IDOK)
	{
		csFileName = dlg.GetPathName(); //ѡ����ļ�·��
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
			wchar_t * vstr;//vstr unicode ��
			Convertstr conv;//�½�utf-8->unicode->ansiʵ��
			int sBufSize = strlen(str);
			if (ansi == 0)
			{
				vstr = conv.UTF8ToUnicode(str);
				str = conv.UnicodeToANSI(vstr);
			}
			//AfxMessageBox(str);
			//��ȡ����Ϣ���зֽ�
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
			AfxMessageBox("��Ӱ���������" + out);
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
* DESCRIPTION:�����ݴ�ȡ�����ݿ�
* Input:��ˮ�š������š���Ա�š�����������
* Returns: �Ƿ�ɹ�ִ��
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
int Operate::Savetosql(CString No, CString Mchn, CString EnNo, CString Name, CString DateTime)
{
	CString Year, Month, Day;
	CString Hour, Minute;
	CString str;//SQl��� 
	Year = DateTime.Mid(0, 4);
	Month = DateTime.Mid(5, 2);
	Day = DateTime.Mid(8, 2);
	Hour = DateTime.Mid(12, 2);
	Minute = DateTime.Mid(15, 2);
	ConnectMySQL();
	/*��Ŀ�û���Ϣ����*/
	if (Checkuser(EnNo, Name) == -1)
	{
		return 0;
	}
	str = "INSERT INTO signoridata VALUES(" + No + "," + Mchn + "," + EnNo + ",\"" + Name + "\",\"" + Year + "-" + Month + "-" + Day + "\",\"" + Hour + ":" + Minute + ":" + "00\")";
	mysql_query(&m_sqlCon, str);
	count += mysql_affected_rows(&m_sqlCon);//���ز���Ӱ�������  
											//AfxMessageBox(str);
	mysql_close(&m_sqlCon);//�ر�Mysql����
	return 1;
}

/***********************************************************************
* DESCRIPTION:�û����أ�������EnNo��Ӧ�������Ƿ�����ݿ���һ��
* Input:��Ա�ţ�����
* Returns: �Ƿ�ɹ�ִ��
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
	if (mysql_real_query(&m_sqlCon, "select Name from user where EnNo = " + EnNo, (unsigned long)strlen("select Name from user where EnNo = " + EnNo)))// ��ѯ���ݿ��е�"signoridata"��  
	{
		//AfxMessageBox("get");
		return 0;
	}
	res = mysql_store_result(&m_sqlCon);//�õ��洢����� 
	if (NULL == res)//���������򷵻�
	{
		//AfxMessageBox("space");
		return 0;
	}
	CString out;
	MYSQL_ROW row;
	if (row = mysql_fetch_row(res)) //�����ݼ�Ϊrow
	{
		CString myreaddata(row[0]);//��row rols��
		if (myreaddata != Name)
		{
			AfxMessageBox("�������Ա�б��¼��ƥ������ݣ����뼴��ȡ��");
			return -1;
		}
	}
	else
	{
		CString str;//SQl��� 
		str = "INSERT INTO user VALUES(" + EnNo + ", \"" + Name + "\")";
		mysql_query(&m_sqlCon, str);
		countu += mysql_affected_rows(&m_sqlCon);//���ز���Ӱ�������  
	}

	mysql_free_result(res);
	return 0;
}

/***********************************************************************
* DESCRIPTION:Ԥ������Դ���ݽ���Ԥ�������㵼��excel�ļ�
* Input:����
* Returns: �Ƿ�ɹ�ִ��
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
int Operate::Exec(int pointer)
{
	AfxMessageBox("��������������Ԥ���������������ĵȴ����������Ҫһ��ʱ�䡣");
	//AfxMessageBox(_T("���ݿ����"));
	ConnectMySQL();
	CString str;
	CString tempNo, tempDate, tempTime;
	CString Day, Month, Year, Hour, Minute;
	str = "delete  FROM preprocess";
	mysql_real_query(&m_sqlCon, str, (unsigned long)strlen(str));//�����Ԥ�����
	str = "select * FROM signoridata";
	if (mysql_real_query(&m_sqlCon, str, (unsigned long)strlen(str)))// ��ѯ���ݿ��е�"signoridata"��  
	{
		return 0;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//�õ��洢����� 
	if (NULL == res)//���Ϊ���򷵻�
	{
		return 0;
	}
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res)) //�����ݼ�Ϊrow
	{
		int rols;
		CString colname;
		for (rols = 2; rols < 6; rols++)
		{
			CString myreaddata(row[rols]);//��row rols��
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
		//����һ�����ݣ���ȡ��3������
		//��֣��жϣ��洢��
		Hour = tempTime.Mid(0, 2);
		Minute = tempTime.Mid(3, 2);
		CString result = CheckTime(Hour, Minute);
		//д�������ȹؼ�ֵ
		CString strm;//SQl��� 
		CString week = GetWeek(tempDate);
		CString day = GetDay(tempDate);
		ConnectMySQL();
		strm = "INSERT INTO preprocess (Caseid,WeekNo,Week,EnNo,Date) VALUES (\"" + tempDate + tempNo + "\"," + week + "," + day + "," + tempNo + ",\"" + tempDate + "\")";
		mysql_query(&m_sqlCon, strm);
		mysql_close(&m_sqlCon);//�ر�Mysql����
		ConnectMySQL();
		if (result != "il")
		{
			//ִ��SQL ��д��Ԥ�����
			CString str1;//SQl��� 
			str1 = "UPDATE preprocess SET " + result + "= \"" + Hour + ":" + Minute + ":00" + "\"  where Caseid = \"" + tempDate + tempNo + "\"";
			mysql_query(&m_sqlCon, str1);
		}
		mysql_close(&m_sqlCon);//�ر�Mysql����
	}
	mysql_free_result(res);
	mysql_close(&m_sqlCon);//�ر�Mysql����
	AfxMessageBox("����");
}

/***********************************************************************
* DESCRIPTION:��ѯĳ���������ڵڼ��죬�����ǵ�һ��
			��Ҫ�ѽ������ݿ����ӡ���Ϊ������SQL��ѯ
* Input: ���ڣ���ʽ��YYYY-MM-DD��
* Returns: CString�����ܵڼ���
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
CString Operate::GetDay(CString str) //Get ���ڵڼ���
{
	ConnectMySQL();
	CString Day;
	CString sql;
	CString out;
	MYSQL_ROW row;
	sql = "select DAYOFWEEK(\"" + str + "\")";
	if (mysql_real_query(&m_sqlCon, sql, (unsigned long)strlen(sql)))// ��ѯ���ݿ��е�""��  
	{
		return 0;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//�õ��洢����� 

	if (NULL == res)//���Ϊ���򷵻�
	{
		return 0;
	}

	while (row = mysql_fetch_row(res)) //�����ݼ�Ϊrow
	{
		CString myreaddata(row[0]);//��row rols��
		Day = myreaddata;
	}
	mysql_free_result(res);
	mysql_close(&m_sqlCon);//�ر�Mysql����
	return Day; //ÿ�ܵ�һ��������
}

/***********************************************************************
* DESCRIPTION:��ѯĳ�����ڵڼ���
			��Ҫ�ѽ������ݿ����ӡ���Ϊ������SQL��ѯ
* Input: ���ڣ���ʽ��YYYY-MM-DD��
* Returns: CString���ܺ�
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
	if (mysql_real_query(&m_sqlCon, sql, (unsigned long)strlen(sql)))// ��ѯ���ݿ��е�""��  
	{
		return 0;
	}
	st_mysql_res *  res = mysql_store_result(&m_sqlCon);//�õ��洢����� 

	if (NULL == res)//���Ϊ���򷵻�
	{
		return 0;
	}

	while (row = mysql_fetch_row(res)) //�����ݼ�Ϊrow
	{
		CString myreaddata(row[0]);//��row rols��
		Week = myreaddata;//
						  //AfxMessageBox(Week);
	}
	mysql_free_result(res);
	mysql_close(&m_sqlCon);//�ر�Mysql����
	return Week;
}

/***********************************************************************
* DESCRIPTION:�������ݿ�����
* Returns: ����״̬
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
		AfxMessageBox(_T("�������ݿ�ʧ��!"));
		CString e = mysql_error(&m_sqlCon);//��Ҫ����Ŀ�������ַ����޸�Ϊ��ʹ�ö��ֽ��ַ�������δ���á�  
		return 0;
	}
	else
	{
		mysql_query(&m_sqlCon, "SET NAMES 'GB2312'");//��������ݿ��ж�ȡ���ݺ���������ʾ������  
	}
	return 0;
}

/***********************************************************************
* DESCRIPTION:ʱ��Ϸ��Լ��
* Input:CString Сʱ��CString ����
* Returns: ʱ������Ӧ��ǩ����
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
CString Operate::CheckTime(CString hour, CString minute)//����ֵ�����ݿ������
{
	//�������Σ�8:00-12:00�����������Σ�14:00-18:00�����������Σ�19:00-22:00��
	//M��N��E�ֱ��Ӧ������������ǩ����ME��EE��EE�ֱ��Ӧ������������ǩ��
	CString test;
	int h = atoi(hour);
	int m = atoi(minute);

	if (h == 8 || h == 14 || h == 19)//���ϺϷ����ж�
	{
		if (m <= tolerate)
		{
			switch (h)
			{
			case 8:
				return "M";//�Ϸ�����ǩ��
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
		return "ME";//�Ϸ���ǩ��ʱ�䣬mΪʵ��ǩ�˷�����
	}
	if ((h >= 14 && h < 19))
	{
		return "NE";//�Ϸ���ǩ��ʱ�䣬mΪʵ��ǩ�˷�����
	}
	if ((h >= 19 && h < 24))
	{
		return "EE";//�Ϸ���ǩ��ʱ�䣬mΪʵ��ǩ�˷�����
	}
	return "il";//return il ʱ�䲻�Ϸ�
}

/***********************************************************************
* DESCRIPTION:������excel
* Input:CString �꣬CString ��
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
void Operate::layoutxlsx(int GetYear, int GetMonth)
{
	int memnum;
	CString pStrFileName;//�ļ�Ŀ¼
	CString Getname, Getno;//���õ����û���������
	CString Weekno;//����¿�ʼ���ܺ�
				   //ʾ��
	if (GetMonth < 1 || GetMonth>12)//�Ǳ�Ҫ��������ȷ�Լ��
	{
		AfxMessageBox("��ѯʱ�䲻�Ϸ�");
		return;
	}
	CString Firstday;
	Firstday.Format("%d-%d", GetYear, GetMonth);
	CString fix = GetDay(Firstday + "-1");//��õ�һ�����ܼ�������GetMonth��һ��������һ�쿪ʼ��
	int ifix = atoi(fix);
	CString Daystart;//��ʽ���� 5������µ�һ���ܿ�ʼ������
	if (ifix == 1)
	{
		Daystart.Format("%d", 1);
	}
	else
	{
		Daystart.Format("%d", 9 - ifix);
	}
	Daystart = Firstday + "-" + Daystart;
	BROWSEINFO stInfo = { NULL };//������·��ѡ��
	LPCITEMIDLIST pIdlst;
	TCHAR szPath[MAX_PATH];
	stInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
	stInfo.lpszTitle = "ע�⣡\n�ļ���Ĭ����YYYY-MM����ʽ������";
	pIdlst = SHBrowseForFolder(&stInfo);
	if (!pIdlst)
		return;
	if (!SHGetPathFromIDList(pIdlst, szPath))
		return;
	//Excel������ݳ�ʼ��
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		return;
	}
	books = app.get_Workbooks();
	book = books.Add(covOptional);
	sheets = book.get_Worksheets();
	NewSheet(sheets);
	sheet = sheets.get_Item(COleVariant((short)5)); //��sheet5
	FillOne(sheet, "A1", "ʵ����" + Firstday + "ǩ�����ܱ�");
	FillOne(sheet, "A2", "����\\��");
	FillOne(sheet, "B2", "��һ��");
	FillOne(sheet, "C2", "�ڶ���");
	FillOne(sheet, "D2", "������");
	FillOne(sheet, "E2", "������");
	FillOne(sheet, "F2", "���ºϼ�");
	for (short vsheet = 1; vsheet <= 4; vsheet++)
	{
		CString vsheetprint;
		vsheetprint.Format("%d", vsheet);
		CString pWeektop = "ʵ���ҵ�" + vsheetprint + "��ǩ����";
		sheet = sheets.get_Item(COleVariant((short)vsheet)); //��sheet
		FillOne(sheet, "A2", "����");
		Merge(sheet, "F1", "I1");
		FillOne(sheet, "F1", pWeektop);
		Merge(sheet, "C2", "D2");
		FillOne(sheet, "C2", "��һ");
		Merge(sheet, "E2", "F2");
		FillOne(sheet, "E2", "�ܶ�");
		Merge(sheet, "G2", "H2");
		FillOne(sheet, "G2", "����");
		Merge(sheet, "I2", "J2");
		FillOne(sheet, "I2", "����");
		Merge(sheet, "K2", "L2");
		FillOne(sheet, "K2", "����");
		Merge(sheet, "M2", "N2");
		FillOne(sheet, "M2", "����");
		Merge(sheet, "O2", "P2");
		FillOne(sheet, "O2", "����");
		FillOne(sheet, "Q2", "�ܺϼ�");		
		ConnectMySQL();//������ÿ���������ѭ��
		CString sql;
		MYSQL_ROW row;
		sql = "SELECT * from user";
		if (mysql_real_query(&m_sqlCon, sql, (unsigned long)strlen(sql)))// ��ѯ���ݿ��е�""��  
		{
			return;
		}
		st_mysql_res *  res = mysql_store_result(&m_sqlCon);//�õ��洢����� 
		if (NULL == res)//���Ϊ���򷵻�
		{
			return;
		}
		memnum = 0;
		while (row = mysql_fetch_row(res)) //�����ݼ�Ϊrow
		{
			for (int rols = 0; rols < 2; rols++)//����ע��Ҫͬʱ����
			{
				CString myreaddata(row[rols]);//��row rols��
				if (rols == 0)
				{
					Getno = myreaddata;
				}
				if (rols == 1)
				{
					Getname = myreaddata;
				}
			}//�´��Ѿ������һ���һ���ֺͺ��룬����ѭ�����ƣ��Լ����ݼ������
			int header = 3 + memnum * 4;	//ÿ���û��ĵ�һ����������3+4*n
			CString headaddress, endaddress;
			headaddress.Format("%d", header);//��һ����
			endaddress.Format("%d", header + 4);//�������
			CString Namecl = "A" + headaddress;//���ֵ�ַ
			CString Namecle = "A" + endaddress;
			CString Totalcl = "Q" + headaddress;//�ܼƵ�ַ
			CString Totalcle = "Q" + endaddress;
			range = sheet.get_Range(COleVariant(Namecl), COleVariant(Namecl));//range���Ʒ�Χ
			Merge(sheet, Namecl, Namecle);
			FillOne(sheet, Namecl, Getname);
			//AfxMessageBox(Getname);
			for (int t = 0; t < 4; t++)//���������ϼ�
			{
				CString Filler, Filler2, Fillin;
				Filler.Format("%d", t + header);
				Filler2 = Filler;
				Filler = "B" + Filler;
				range = sheet.get_Range(COleVariant(_T(Filler)), COleVariant(_T(Filler)));//range���Ʒ�Χ
				if (t == 0)
				{
					Fillin = "��";
				}
				if (t == 1)
				{
					Fillin = "��";
				}
				if (t == 2)
				{
					Fillin = "��";
				}
				if (t == 3)
				{
					Fillin = "�ϼ�";
					//�ϲ����պϼ�
					Merge(sheet, "C" + Filler2, "D" + Filler2);
					Merge(sheet, "E" + Filler2, "F" + Filler2);
					Merge(sheet, "G" + Filler2, "H" + Filler2);
					Merge(sheet, "I" + Filler2, "J" + Filler2);
					Merge(sheet, "K" + Filler2, "L" + Filler2);
					Merge(sheet, "M" + Filler2, "N" + Filler2);
					Merge(sheet, "O" + Filler2, "P" + Filler2);
				}
				range.put_Value2(COleVariant(Fillin));	//����������
			}
			//memnum++;
			//������Ӧ�ø������ݿ������ձ��µ�һ�ܣ���ȡһ���ڵ������ÿ����Ҳ��4����
			//��֪��Ϣ no��week�ţ���һ�죬��ѯ���������
			Weekno = GetWeek(Daystart);
			int vWeekno = atoi(Weekno);//������¿�ʼ���ܺ�ת��Ϊint
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
				if (mysql_real_query(&m_sqlCon, sqltemp, (unsigned long)strlen(sqltemp)))// ��ѯ���ݿ��е�""��  
				{
					return;
				}
				st_mysql_res *  restemp = mysql_store_result(&m_sqlCon);//�õ��洢����� 
				mysql_free_result(restemp);
				if (NULL == restemp)//���Ϊ���򷵻�
				{
					return;
				}
				CString pStrIntervalFunc = "=TEXT((AND(MST<>\"\",MEN<>\"\")*(MEN-MST)+AND(NST<>\"\",NEN<>\"\")*(NEN-NST)+AND(EST<>\"\",EEN<>\"\")*(EEN-EST)),\"[h]:mm\")";
				//AfxMessageBox(pStrIntervalFunc);
				while (rowtemp = mysql_fetch_row(restemp)) //�����ݼ�Ϊrow
				{
					for (int temp = 4; temp < 10; temp++)
					{
						CString myreaddata(rowtemp[temp]);//��row rols��
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
				//�������в��������㣬���
				pRealLocate.Format("%d", memnum * 4 + 6);//��Ԫ��������������һ����							
				int nFirstTag = 0;
				if (pStrIntervalFunc == "=TEXT((AND(MST<>\"\",MEN<>\"\")*(MEN-MST)+AND(NST<>\"\",NEN<>\"\")*(NEN-NST)+AND(EST<>\"\",EEN<>\"\")*(EEN-EST)),\"[h]:mm\")")
				{
					pStrIntervalFunc = "";
				}
				//�����ʱ���
				FillOne(sheet, GetRealCol(uday, 0) + pRealLocate, pStrIntervalFunc);
				mysql_close(&m_sqlCon);
			}//��������һ�����յ�ѭ��
			pRealLocate.Format("%d", memnum * 4 + 3);//��Ԫ��������������һ����	
			pStrTotalColEnd.Format("%d", memnum * 4 + 6);
			//����SUM
			CString pStrSumFunc;
			pStrSumFunc = "=TEXT((VALUE(Cblank+Eblank+Gblank+Iblank+Kblank+Mblank+Oblank)),\"[h]:mm:ssS\")";
			pStrSumFunc.Replace("blank", pStrTotalColEnd);
			FillOne(sheet, "Q" + pStrTotalColEnd, pStrSumFunc);
			sheet = sheets.get_Item(COleVariant((short)5)); //��sheet5
			CString pStrRownum, pStrTotalFunc, pStrMonthTotalFunc;
			pStrRownum.Format("%d", memnum + 3);
			pStrTotalFunc = "=��X��!Q" + pStrTotalColEnd;
			pStrTotalColEnd = WeekToCol(vsheet) + pStrRownum;
			switch (vsheet)
			{
			case 1:
				pStrTotalFunc.Replace("X", "һ");
			case 2:
				pStrTotalFunc.Replace("X", "��");
			case 3:
				pStrTotalFunc.Replace("X", "��");
			case 4:
				pStrTotalFunc.Replace("X", "��");
			}
			pStrMonthTotalFunc = "=TEXT(SUM(VALUE(Baddress+Caddress+Daddress+Eaddress)),\"[h]:mm:ss\")";
			pStrMonthTotalFunc.Replace("address", pStrRownum);
			FillOne(sheet, "A" + pStrRownum, Getname);
			FillOne(sheet, "F" + pStrRownum, pStrMonthTotalFunc);
			FillOne(sheet, pStrTotalColEnd, pStrTotalFunc);
			memnum++;//��Ա��+1
			sheet = sheets.get_Item(COleVariant((short)vsheet)); //��vsheet
		}
		mysql_free_result(res);
		mysql_close(&m_sqlCon);//�ر�Mysql����
	}
	app.put_Visible(TRUE);
	app.put_UserControl(FALSE); 
	pStrFileName.Format(_T("%s"), szPath);
	app.put_DisplayAlerts(FALSE); //��ֹSaveAs������Ч����
	book.SaveAs(COleVariant(pStrFileName +"\\"+Firstday + ".xlsx"), covOptional, covOptional,
		covOptional, covOptional, covOptional, 0,
		covOptional, covOptional, covOptional, covOptional, covOptional, covOptional); //����д��
	app.put_DisplayAlerts(TRUE);
}

/***********************************************************************
* DESCRIPTION:���µ�xlsx�ļ�������µ�sheet
* Input:WorkSheets
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
void Operate::NewSheet(CWorksheets sheets) //�����µ�excel������sheets
{
	const char * week1 = "��һ��";
	const char * week2 = "�ڶ���";
	const char * week3 = "������";
	const char * week4 = "������";
	const char * weeks = "�ܻ���";
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
	//sheet1���½�3����
	//range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("B1")));//range���Ʒ�Χ
	//range.put_Value2(COleVariant(temp));//�����ֵ
	//range.Merge(_variant_t(1));//�ϲ�range�ĵ�Ԫ��
	//Ϊsheet�趨����

	*/
}

/***********************************************************************
* DESCRIPTION:��䵥Ԫ��
* Input:Worksheet����ַ������
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
* DESCRIPTION:�ϲ�Ŀ�굥Ԫ��
* Input:Worksheet����ʼ��Ԫ��Ŀ�굥Ԫ��
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
void Operate::Merge(CWorksheet pSheet, CString pFrom, CString pTo)
{
	CRange rangetemp;
	rangetemp = sheet.get_Range(COleVariant(pFrom), COleVariant(pTo));//range���Ʒ�Χ
	rangetemp.Merge(_variant_t(1));//�ϲ�range�ĵ�Ԫ��
}

/***********************************************************************
* DESCRIPTION:��ȡ��Ӧ���к�
* Input:�ܺţ�ǩ��/ǩ��
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
* DESCRIPTION:��ȡ��Ӧ���к�
* Input:Worksheet����ʼ��Ԫ��Ŀ�굥Ԫ��
* modification history
* --------------------
* author: Liangshoupeng 2017-7-11
* --------------------
***********************************************************************/
CString Operate::WeekToCol(int iWeek)// ������ʱ��sheet5����ת�к�
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
