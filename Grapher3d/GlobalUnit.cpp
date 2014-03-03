//---------------------------------------------------------------------------
#pragma hdrstop

#include "GlobalUnit.h"
//---------------------------------------------------------------------------
bool GetProbalityValue(AnsiString S, double &dRet, AnsiString &strErr)
{
	try
	{
	 AnsiString strComa(0.1);
	 for(int i=0; i< S.Length(); i++)
	 {
	  if(S[i+1] == ',' || S[i+1] == '.')
		S[i+1] = strComa[1+1];
	 }

	 S = S.Trim();


	 dRet = S.ToDouble();
	 if( dRet < 0)
	 {
	  strErr = "«начение не должно быть отрицательным '" + S + "'";
	  return false;
	 }
	}
	catch(EConvertError *EC)
	{
	 strErr = "¬ведено неправильное чиcловое значение '" + S + "'";
	 return false;
	}
	return true;
}
//---------------------------------------------------------------------------
char* _c_str(AnsiString str)
{
	return str. c_str();

}
//---------------------------------------------------------------------------
AnsiString GetProgramPath(void)
{
	AnsiString str = Application->ExeName;
	str = ExtractFileDir(str);
	if(str != NULL)
	{
	 str +="\\";
	}
	return  str;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#pragma package(smart_init)
