// (c) dzmat@yandex.ru 2015-2017 --------------------------------------------


#pragma hdrstop

#include "common.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString getwin32_errmsg(int err)
{
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR) &lpMsgBuf,
        0,
        NULL
    );
    AnsiString t;
    t.sprintf("%s",lpMsgBuf);
    // Free the buffer.
    LocalFree( lpMsgBuf );
    return t;
}


bool skip_head_extract_value(const AnsiString& s,const char* h,AnsiString& res)
{
    int h_len=strlen(h);
    int s_len=s.Length();
    if (strncmp(s.c_str(),h,h_len)!=0)return false;
    //string found, start exctracting value
    res="";
    int j=h_len+1;
    while (j<=s_len){
        char ch=s[j];
        if( isdigit(ch) || ch=='.'){
            res+=ch;
            ++j;
        }else break;
    }
    return true;
}

