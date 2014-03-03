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
	  strErr = "Значение не должно быть отрицательным '" + S + "'";
	  return false;
	 }
	}
	catch(EConvertError *EC)
	{
	 strErr = "Введено неправильное чиcловое значение '" + S + "'";
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
bool ReadEditDouble(TEdit *pEdit, bool SetFocusOnError, double &dRet)
{
	AnsiString S;
	S = pEdit->Text;
	AnsiString strErr;
	bool bRet = GetProbalityValue(S, dRet, strErr);
	if(bRet == false)
	{
	  if(SetFocusOnError == true)
	  {
	   ShowErrorCtrl(strErr, pEdit);
	  }
	}
	return bRet;
}
//---------------------------------------------------------------------------
void ShowErrorCtrl(AnsiString strErrText, TWinControl *pControl)
{
	AnsiString Text = strErrText;
	Application->MessageBox(_WST(Text),_WST("Ошибка"),MB_OK | MB_ICONEXCLAMATION);
	if(pControl->CanFocus())
	 pControl->SetFocus();
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
