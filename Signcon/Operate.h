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
	int count = 0;	//�ܵ�txtӰ�������
	int Checkuser(CString EnNo, CString Name);
	int countu = 0; //�յ�txtӰ����û����
	int ansi = 1;
	int tolerate = 10;
	int Exec(int pointer);
	// ��Ҫ�Ѿ�����MYSQL����
	CString GetDay(CString str);
	// ��Ҫ�Ѿ�����MySQL����
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
	// ������ʱ��sheet5����ת�к�	
	CString WeekToCol(int iWeek);
};

