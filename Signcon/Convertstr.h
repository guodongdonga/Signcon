#pragma once
/**************************************************************************
* Copyright (c) 2017 damaowo.cn
* File: Convertstr.h
* Description : ANSI¡¢Unicode¡¢UTF-8Ö®¼ä×ª»»
* modification history
* --------------------
* author: liang 2017-7-8
* --------------------
**************************************************************************/

class Convertstr
{
public:

	Convertstr();
	~Convertstr();
public:
	wchar_t * ANSIToUnicode(const char* str);
	char * UnicodeToANSI(const wchar_t *str);
	wchar_t * UTF8ToUnicode(const char* str);
	char * UnicodeToUTF8(const wchar_t *str);

};
