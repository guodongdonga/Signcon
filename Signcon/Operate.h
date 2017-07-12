#pragma once
#include "CApplication.h" 
#include "CWorkbook.h" 
#include "CWorkbooks.h" 
#include "CWorksheet.h" 
#include "CWorksheets.h" 
#include "CRange.h" 
#include <shlobj.h>
class Operate
{
public:
	Operate();
	~Operate();
	int Readfile();
	int Savetosql(CString No, CString Mchn, CString EnNo, CString Name, CString DateTime);
	int count = 0;	//受到txt影响的行数
	int Checkuser(CString EnNo, CString Name);
	int countu = 0; //收到txt影响的用户添加
	int ansi = 1;
	int tolerate = 10;
	int Exec(int pointer);
	// 需要已经建立MYSQL连接
	CString GetDay(CString str);
	// 需要已经建立MySQL连接
	CString GetWeek(CString str);
	int ConnectMySQL();
	CString CheckTime(CString hour, CString minute);
	void layoutxlsx(int GetYear, int GetMonth);
	CApplication app;
	CWorkbook book;
	CWorkbooks books;
	CWorksheet sheet;
	CWorksheets sheets;
	CRange range;
	CFont font;
	CRange cols;
	LPDISPATCH lpDisp;
	void NewSheet(CWorksheets sheets);
	void FillOne(CWorksheet pSheet, CString pAddress, CString pValue);
	void Merge(CWorksheet pSheet, CString pFrom, CString pTo);
	CString GetRealCol(CString pWeek, int E);
	// 表格填充时，sheet5将周转列号	
	CString WeekToCol(int iWeek);
};

