//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DefectEditUnit.h"
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TDefectEditForm *DefectEditForm;
//---------------------------------------------------------------------------
__fastcall TDefectEditForm::TDefectEditForm(TComponent* Owner)
	: TForm(Owner)
{
	m_pMaskEditForm = NULL;
	m_pPictForm = NULL;
}
//---------------------------------------------------------------------------
void TDefect::Init()
{//инициализировать структуру по умолчанию
	//Название
	m_sName = "";
	//Количество циклов
	m_nLoopCount = 1;
	//Mаска
	m_vMask.clear();//вектор масок
}
//---------------------------------------------------------------------------
TDefect::TDefect()
{//конструктор по умолчанию
	Init();
}
//---------------------------------------------------------------------------
TDefect::TDefect(const TDefect& r)
{//конструктор копирования
	*this = r;
}
//---------------------------------------------------------------------------
TDefect& TDefect::operator = (const TDefect &r)
{//оператор копирования
	//Название
	m_sName = r.m_sName;
	//Количество циклов
	m_nLoopCount = r.m_nLoopCount;
	//Mаска
	m_vMask = r.m_vMask;//вектор масок

	return *this;
}
//---------------------------------------------------------------------------
bool TDefect::SaveToFile(HANDLE hFile, int *pSeek/* = NULL*/)
{//сохранить структуру в поток
	bool bRet = false;
	int nSeek = 0;
	DWORD NumberOfBytesToWrite, NumberOfBytesWritten;
	bool bwf = true;
	//int i;
	   //Название
	   int nLen = m_sName.Length();

	   NumberOfBytesToWrite = sizeof(nLen);
	   bwf &= WriteFile(hFile,&(nLen),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   if(nLen >0)
	   {
		char *psz = _c_str(m_sName);

		NumberOfBytesToWrite = nLen*sizeof(psz[0]);
		bwf &= WriteFile(hFile,&(psz[0]),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
		nSeek+= (bwf)?NumberOfBytesWritten:0;
	   }

	   //Количество циклов
	   NumberOfBytesToWrite = sizeof(m_nLoopCount);
	   bwf &= WriteFile(hFile,&(m_nLoopCount),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
	   nSeek+= (bwf)?NumberOfBytesWritten:0;

	   //Mаска
	   bwf &= m_vMask.SaveToFile(hFile, &nSeek) ;

	if(pSeek != NULL)
	{
	 *pSeek += nSeek;
	}
	bRet = bwf;
	return bRet;
}
//---------------------------------------------------------------------------
bool TDefect::LoadFromFile(HANDLE hFile, int *pSeek/* = NULL*/)
{//загрузить структуру из потока
	bool bRet = false;
	int nSeek = 0;
	DWORD NumberOfBytesRead,NumberOfBytesReaded;
	//int i;
	bool bwf = true;
		//Название
		int nLen = 0;

		NumberOfBytesRead = sizeof(nLen);
		bwf &= ReadFile(hFile,&nLen,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;


		m_sName = "";
		if(nLen > 0)
		{
		 unsigned int nMaxLen = nLen+10;
		 char *psz = new char[nMaxLen];
		 memset(psz,0,nMaxLen);

		 NumberOfBytesRead = nLen*sizeof(psz[0]);
		 bwf &= ReadFile(hFile,&(psz[0]),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		 nSeek += (bwf)?NumberOfBytesReaded:0;

		 m_sName = AnsiString(psz);

		 delete psz;
		}

		//Количество циклов
		NumberOfBytesRead = sizeof(m_nLoopCount);
		bwf &= ReadFile(hFile,&m_nLoopCount,NumberOfBytesRead,&NumberOfBytesReaded,NULL);
		nSeek += (bwf)?NumberOfBytesReaded:0;

	   //Mаска
	   bwf &= m_vMask.LoadFromFile(hFile, &nSeek) ;

	if(pSeek != NULL)
	{
	 *pSeek += nSeek;
	}
	bRet = bwf;
	return bRet;
}
//---------------------------------------------------------------------------
AnsiString TDefect::ToStr()
{//описание дефекта строкой
	AnsiString strRet;
	strRet = m_sName + " [" + IntToStr(m_nLoopCount) + "]";
	return strRet;
}
//---------------------------------------------------------------------------
bool TDefectEditForm::EditDefect(TDefect &rec, int nWidth, int nHeight)//тру если изменилось
{
	bool bRet = false;
	m_EditRec = rec;

	m_nWidth = nWidth;
	m_nHeight = nHeight;

	if(ShowModal() == mrOk)
	{
	 bRet = true;
	 rec = m_EditRec;
	}
	m_EditRec.Init();
	return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TDefectEditForm::FormShow(TObject *Sender)
{
	NameEdit->Text = m_EditRec.m_sName;
	CountEdit->Text = IntToStr(m_EditRec.m_nLoopCount);

	SetControlButton();
}
//---------------------------------------------------------------------------
void __fastcall TDefectEditForm::SetControlButton()
{
	int nCount;

	nCount = m_EditRec.m_vMask.size();

	bool bCountGrZero = (nCount > 0);

	PictSpeedButton->Enabled = bCountGrZero;
}
//---------------------------------------------------------------------------
void __fastcall TDefectEditForm::FormDestroy(TObject *Sender)
{
	if (m_pPictForm != NULL)
	{
		m_pPictForm->Close();
		delete m_pPictForm;
		m_pPictForm = NULL;
	}
	if (m_pMaskEditForm != NULL)
	{
		m_pMaskEditForm->Close();
		delete m_pMaskEditForm;
		m_pMaskEditForm = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefectEditForm::PictSpeedButtonClick(TObject *Sender)
{
	if(m_EditRec.m_vMask.size() > 0)
	{
	 if(m_pPictForm == NULL)
	 {
	  m_pPictForm = new TPictuteForm(this);
	 }
	 m_pPictForm->PaintMask(m_EditRec.m_vMask, m_nWidth, m_nHeight);
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefectEditForm::OkButtonClick(TObject *Sender)
{
	NameEdit->Text.Trim();
	if(NameEdit->Text == "")
	{
	 ShowErrorCtrl("Заполните название дефекта.", NameEdit);
	 return;
	}

	m_EditRec.m_sName = NameEdit->Text;
	double dVal;
	if(ReadEditDouble(CountEdit, true, dVal) == false)
	{
	 return;
	}
	m_EditRec.m_nLoopCount = (int)dVal;

	if(m_EditRec.m_vMask.size() == 0)
	{
	 ShowErrorCtrl("Добавьте хотя бы одну маску.", EditBitBtn);
	 return;
	}
	ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TDefectEditForm::EditBitBtnClick(TObject *Sender)
{
	bool bRet;
	if (m_pMaskEditForm == NULL)
	{
	 m_pMaskEditForm = new TMaskEditForm(this);
	}
	bRet = m_pMaskEditForm->EditMask(m_EditRec.m_vMask, m_nWidth, m_nHeight);
	if(bRet == true)
	{
     SetControlButton();
	}
}
//---------------------------------------------------------------------------

