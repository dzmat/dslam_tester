//---------------------------------------------------------------------------

#ifndef commonH
#define commonH
#include <vcl.h>
//---------------------------------------------------------------------------

//#define NO_HARDWARE

enum DEBUG_LEVEL{DB_NONE,DB_ERR,DB_WARN,DB_INFO};
void debug_log(DEBUG_LEVEL lvl,char* funk,char* message); // implemented in unit1.cpp
void console_write(char* prefix,char* message); // implemented in unit1.cpp

AnsiString getwin32_errmsg(int err);
bool skip_head_extract_value(const AnsiString& s,const char* h,AnsiString& res);
#endif
