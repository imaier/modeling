//---------------------------------------------------------------------------
#pragma hdrstop
#include "ProbPoviderUnit.h"
#include "Almas1ProbSetUnit.h"
#include "Almas2ProbSetUnit.h"
#include "Almas3ProbSetUnit.h"
#include "Almas4ProbSetUnit.h"
#include "Almas5ProbSetUnit.h"
#include "Almas6ProbSetUnit.h"
#include "Almas7ProbSetUnit.h"
#include <winbase.h>
#include "GlobalUnit.h"

//---------------------------------------------------------------------------
TProbPoviderGlobal g_ProbPoviderGlobal;

//---------------------------------------------------------------------------
TProbPoviderGlobal::TProbPoviderGlobal()
{
	IBaseProbSetCreator* pBaseProbSetCreator;
	pBaseProbSetCreator = new TAlmas1ProbSetCreator();	m_vProbSetCreator.push_back(pBaseProbSetCreator);
	pBaseProbSetCreator = new TAlmas2ProbSetCreator();	m_vProbSetCreator.push_back(pBaseProbSetCreator);
	pBaseProbSetCreator = new TAlmas3ProbSetCreator();	m_vProbSetCreator.push_back(pBaseProbSetCreator);
	pBaseProbSetCreator = new TAlmas4ProbSetCreator();	m_vProbSetCreator.push_back(pBaseProbSetCreator);
	pBaseProbSetCreator = new TAlmas5ProbSetCreator();	m_vProbSetCreator.push_back(pBaseProbSetCreator);
	pBaseProbSetCreator = new TAlmas6ProbSetCreator();	m_vProbSetCreator.push_back(pBaseProbSetCreator);
	pBaseProbSetCreator = new TAlmas7ProbSetCreator();	m_vProbSetCreator.push_back(pBaseProbSetCreator);
}
//---------------------------------------------------------------------------
TProbPoviderGlobal::~TProbPoviderGlobal()
{
	for(UINT i=0; i < m_vProbSetCreator.size(); i++)
	{
	 IBaseProbSetCreator* pIPSC = m_vProbSetCreator[i];
	 delete pIPSC;
	}
}
//---------------------------------------------------------------------------
TProbPovider::TProbPovider()
{
	pCurrInterface = NULL;
}
//---------------------------------------------------------------------------
TProbPovider::~TProbPovider()
{
	ClearInterface();
}
//---------------------------------------------------------------------------
IBaseProbSet* TProbPovider::GetInterface(void) const
{//получение указателя на интерфейс набора вероятностей
	return pCurrInterface;
}
//---------------------------------------------------------------------------
void TProbPovider::CreateInterfaceByIdString(AnsiString strIdString)
{//создать интерфейс набора вероятностей по его уину
    ClearInterface();
	for(UINT i=0; i < g_ProbPoviderGlobal.m_vProbSetCreator.size(); i++)
    {
	 IBaseProbSetCreator* pIPSC = g_ProbPoviderGlobal.m_vProbSetCreator[i];
	 if(pIPSC->GetInfo().GetProbSetIdString() == strIdString)
	 {//нашли нужный креатор
		pCurrInterface = pIPSC->Create();//создаём
		pCurrInterface->FillDefault();//инициализируем по умолчанию
	 }
	}
}
//---------------------------------------------------------------------------
void TProbPovider::ClearInterface()
{//удалить интерфейс набора вероятностей
    if(pCurrInterface != NULL)
    {
     delete pCurrInterface;
     pCurrInterface = NULL;
    }
}
//---------------------------------------------------------------------------
bool TProbPovider::SaveToFile(HANDLE hFile, int *pSeek)
{//сохранить текущий набор вероятностей в файл
    bool bRet = false;
    if(pCurrInterface != NULL)
    {
        AnsiString strIdString = pCurrInterface->GetCreator().GetInfo().GetProbSetIdString();
        int nLen = strIdString.Length();
        DWORD nNumberOfBytesToWrite = sizeof(nLen);
        DWORD nNumberOfBytesWritten=0;
        BOOL nRet;
        nRet = WriteFile(
         hFile,	                // handle to file to write to
         &nLen,	        // pointer to data to write to file
         nNumberOfBytesToWrite,	// number of bytes to write
         &nNumberOfBytesWritten,// pointer to number of bytes written
         NULL 	                // pointer to structure needed for overlapped I/O
         );
        bRet = (nRet != FALSE);
        if(bRet == true)
        {
         nNumberOfBytesToWrite = nLen*sizeof(char);
         nNumberOfBytesWritten=0;
         nRet = WriteFile(
          hFile,	               // handle to file to write to
		  _c_str(strIdString),     // pointer to data to write to file
          nNumberOfBytesToWrite,   // number of bytes to write
          &nNumberOfBytesWritten,  // pointer to number of bytes written
          NULL 	                   // pointer to structure needed for overlapped I/O
          );
         bRet = (nRet != FALSE);
         if(bRet == true)
         {
          bRet = pCurrInterface->SaveToFile(hFile);
         }
        }
    }
    return bRet;
}
//---------------------------------------------------------------------------
bool TProbPovider::LoadFromFile(HANDLE hFile, int *pSeek)
{//загрузить набор вероятностей из файла
    bool bRet = false;

	if(pCurrInterface != NULL)
	{
		ClearInterface();//удалить интерфейс набора вероятностей
	}
    int nLen = 0;

    DWORD nNumberOfBytesToRead = sizeof(nLen);
	DWORD nNumberOfBytesRead = 0;
    BOOL nRet = ReadFile(
     hFile,	                // handle of file to read
     &nLen,	                // address of buffer that receives data
     nNumberOfBytesToRead,	// number of bytes to read
     &nNumberOfBytesRead,	// address of number of bytes read
     NULL 	                // address of structure for data
    );
    bRet = (nRet != FALSE);
    if(bRet == true)
    {
     if(nLen <= 0)
     {
      bRet == false;
     }
    }

    if(bRet == true)
    {
     unsigned int nMaxLen = nLen+10;
     char *szIdString = new char[nMaxLen];
     //szIdString[nLen] = 0;
     memset(szIdString,0,nMaxLen);

     nNumberOfBytesToRead = nLen*sizeof(char);
     nNumberOfBytesRead = 0;
     BOOL nRet = ReadFile(
      hFile,	                // handle of file to read
      szIdString,              // address of buffer that receives data
      nNumberOfBytesToRead,	// number of bytes to read
      &nNumberOfBytesRead,	// address of number of bytes read
      NULL 	                // address of structure for data
     );
     bRet = (nRet != FALSE);
     AnsiString strIdString(szIdString);
     delete [] szIdString;
     if(bRet == true)
     {
      bRet = false;
      CreateInterfaceByIdString(strIdString);//создать интерфейс набора вероятностей по его уину
      if(pCurrInterface != NULL)
      {
       bRet = pCurrInterface->LoadFromFile(hFile);
      }
     }
    }
    return bRet;
}
//---------------------------------------------------------------------------
//Перечисление возможных интерефейсов
int TProbPovider::EnumirateGetCount()
{//максимальное количество интерфейсов
	return g_ProbPoviderGlobal.m_vProbSetCreator.size();
}
//---------------------------------------------------------------------------
AnsiString TProbPovider::EnumirateGetIdString(unsigned int nIndex)
{//получение уина интерфейса по индексу
    AnsiString strRet = "Ошибка";
	if(/*nIndex>=0 &&*/ nIndex < g_ProbPoviderGlobal.m_vProbSetCreator.size())
	{
		IBaseProbSetCreator* pIPSC = g_ProbPoviderGlobal.m_vProbSetCreator[nIndex];
		strRet = pIPSC->GetInfo().GetProbSetIdString();
	}
	return strRet;
}
//---------------------------------------------------------------------------
AnsiString TProbPovider::EnumirateGetName(unsigned int nIndex)
{//получение имени интерфейса по индексу
    AnsiString strRet = "Ошибка";
    if(/*nIndex>=0 && */nIndex < g_ProbPoviderGlobal.m_vProbSetCreator.size())
	{
		IBaseProbSetCreator* pIPSC = g_ProbPoviderGlobal.m_vProbSetCreator[nIndex];
        strRet = pIPSC->GetInfo().GetProbSetNameString();
    }
    return strRet;
}
//---------------------------------------------------------------------------
AnsiString TProbPovider::EnumirateGetDiscrption(unsigned int nIndex)
{//получение описания интерфейса по индексу
    AnsiString strRet = "Ошибка";
	if(/*nIndex>=0 && */nIndex < g_ProbPoviderGlobal.m_vProbSetCreator.size())
	{
		IBaseProbSetCreator* pIPSC = g_ProbPoviderGlobal.m_vProbSetCreator[nIndex];
		strRet = pIPSC->GetInfo().GetProbSetDiscrptionString();
	}
    return strRet;
}
//---------------------------------------------------------------------------
bool TProbPovider::SaveToFile(AnsiString strFileName)
{//сохранить текущий набор вероятностей в файл
    bool bRet = false;
    HANDLE hFile = CreateFile(
		_c_str(strFileName),	// pointer to name of the file
        GENERIC_WRITE,	// access (read-write) mode
        0,	// share mode
        NULL,	// pointer to security attributes
        CREATE_ALWAYS,	// how to create
        FILE_ATTRIBUTE_NORMAL,	// file attributes
        NULL 	// handle to file with attributes to copy
       );
    if(hFile != INVALID_HANDLE_VALUE)
    {
	 bRet = SaveToFile(hFile);
	 CloseHandle(hFile);
    }
    else
    {
    }
    return bRet;
}
//---------------------------------------------------------------------------
bool TProbPovider::LoadFromFile(AnsiString strFileName)
{//загрузить набор вероятностей из файла
    bool bRet = false;
    HANDLE hFile = CreateFile(
		_c_str(strFileName),	// pointer to name of the file
		GENERIC_READ,	// access (read-write) mode
        0,	// share mode
        NULL,	// pointer to security attributes
        OPEN_EXISTING,	// how to create
        FILE_ATTRIBUTE_NORMAL,	// file attributes
        NULL 	// handle to file with attributes to copy
       );
    if(hFile != INVALID_HANDLE_VALUE)
    {
     bRet = LoadFromFile(hFile);
     CloseHandle(hFile);
    }
    else
    {
    }
    return bRet;
}
//---------------------------------------------------------------------------
TProbPovider::TProbPovider(const TProbPovider &r)
{
	pCurrInterface = NULL;
	*this = r;
}
//---------------------------------------------------------------------------
TProbPovider& TProbPovider::operator=(const TProbPovider &r)
{
	ClearInterface();//удалить интерфейс набора вероятностей
	IBaseProbSet* pPS = r.GetInterface();
	if(pPS != NULL)
	{
	 pCurrInterface = pPS->GetCreator().Create();
	 pCurrInterface->Copy(*pPS);
	}
	return *this;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
