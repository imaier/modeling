//---------------------------------------------------------------------------

#ifndef GlobalUnitH
#define GlobalUnitH
//---------------------------------------------------------------------------
#include <vcl.h>
//#include <System.hpp>
//---------------------------------------------------------------------------
#define CPP_BUILDER_VER2009

//дефайн для 2009 C++ Builder
#ifdef CPP_BUILDER_VER2009
#define _WST(char_string)(wchar_t*)WideString(char_string)
#else
#define _WST(char_string) char_string
#endif

char* _c_str(AnsiString str);
//дефайн для 2009 C++ Builder
#ifdef CPP_BUILDER_VER2009
//#define _c_str(ansi_string)ansi_string.c_str()
//#define _c_str_capt(ansi_string)ansi_string.t_str()
#else
//#define _c_str(ansi_string)ansi_string.c_str()
//#define _c_str_capt(ansi_string)ansi_string.c_str()
#endif

bool GetProbalityValue(AnsiString S, double &dRet, AnsiString &strErr);

AnsiString GetProgramPath(void);
//---------------------------------------------------------------------------
#endif
