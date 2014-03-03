//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DefectUnit.h"
#include "GlobalUnit.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TDefectForm *DefectForm;
//---------------------------------------------------------------------------
bool TDefectVec::SaveToFile(HANDLE hFile, int *pSeek)
{//сохранить вектор масок в файл
	bool bRet;
    int nSeek = 0;
    DWORD NumberOfBytesToWrite, NumberOfBytesWritten;
    bool bwf = true;
	int i, nCountDefect;
	nCountDefect = size();

       NumberOfBytesToWrite = sizeof(nCountDefect);
	   bwf &= WriteFile(hFile,&(nCountDefect),NumberOfBytesToWrite,&NumberOfBytesWritten,NULL);
       nSeek+= (bwf)?NumberOfBytesWritten:0;

    for(i=0; i < nCountDefect && bwf; i++)
    {
		TDefect &Defect = (*this)[i];
		bwf &= Defect.SaveToFile(hFile, &nSeek);
    }

    if(pSeek != NULL)
    {
	 *pSeek += nSeek;
	}
    bRet = bwf;
	return bRet;
}
//---------------------------------------------------------------------------
bool TDefectVec::LoadFromFile(HANDLE hFile, int *pSeek)
{//загрузить вектор масок из файла
    bool bRet = false;
    int nSeek = 0;
    DWORD NumberOfBytesRead,NumberOfBytesReaded;
	int i, nCountDefect;
	bool bwf = true;
    clear();

        NumberOfBytesRead = sizeof(nCountDefect);
        bwf &= ReadFile(hFile,&(nCountDefect),NumberOfBytesRead,&NumberOfBytesReaded,NULL);
        nSeek += (bwf)?NumberOfBytesReaded:0;

	TDefect Defect;
    for(i=0; i < nCountDefect && bwf; i++)
    {
        bwf &= Defect.LoadFromFile(hFile, &nSeek);
        if(bwf == true)
			push_back(Defect);
    }

    if(pSeek != NULL)
    {
     *pSeek += nSeek;
    }
    bRet = bwf;
    return bRet;
}
//---------------------------------------------------------------------------
__fastcall TDefectForm::TDefectForm(TComponent* Owner)
	: TForm(Owner)
{
	m_pPictForm = NULL;
	m_pDefectEditForm = NULL;
}
//---------------------------------------------------------------------------
bool TDefectForm::EditDefect(TDefectVec &rec, int nWidth, int nHeight)
{//тру если изменилось
	bool bRet = false;
	m_EditRec = rec;

	m_nWidth = nWidth;
	m_nHeight = nHeight;

	if(ShowModal() == mrOk)
	{
	 bRet = true;
	 rec = m_EditRec;
	}
	m_EditRec.clear();
	return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TDefectForm::FormShow(TObject *Sender)
{
	DefectListBox->Items->Clear();
	UINT i;
	for(i = 0; i < m_EditRec.size(); i++)
	{
		TDefect &rec = m_EditRec[i];
		DefectListBox->Items->Add(rec.ToStr());
	}
	SetControlButton();
}
//---------------------------------------------------------------------------
void __fastcall TDefectForm::SetControlButton()
{
	int nIndex, nCount;

	nIndex = DefectListBox->ItemIndex;
	nCount = DefectListBox->Items->Count;

	bool bIndexSelected = (nIndex >= 0) && (nCount > 0);
	bool bCountGrOne = (nCount > 1);
	bool bIndexFirst = (nIndex == 0) && (nCount > 0);
	bool bIndexLast = (nIndex == nCount -1);

	MoveUpSpeedButton->Enabled = bIndexSelected && !bIndexFirst && bCountGrOne;
	MoveDownSpeedButton->Enabled = bIndexSelected && !bIndexLast && bCountGrOne;
	AddDefectBitBtn->Enabled = true;
	EditDefectBitBtn->Enabled = bIndexSelected;
	DelDefectBitBtn->Enabled = bIndexSelected;
	PictSpeedButton->Enabled = bIndexSelected;
}
//---------------------------------------------------------------------------
void __fastcall TDefectForm::LoadSpeedButtonClick(TObject *Sender)
{
	if(DefectOpenDialog->Execute() == true)
	{
		AnsiString strFileName = DefectOpenDialog->FileName;
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
			TDefectVec Rec;
			int nSeek = 0;
			if(Rec.LoadFromFile(hFile, &nSeek) == true )
			{
			 m_EditRec = Rec;
			 FormShow(NULL);
			}
			else
			{
			 AnsiString strErr = "Не удалось прочитать из файла \"" + strFileName + "\". Ошибка в позиции " + nSeek;
			 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
			}

			CloseHandle(hFile);
		}
		else
		{
		 AnsiString strErr = "Не удалось открыть файл \"" + DefectSaveDialog->FileName + "\" для чтения.";
		 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefectForm::SaveSpeedButtonClick(TObject *Sender)
{
	int nDefectCount = DefectListBox->Items->Count;
	if( nDefectCount == 0)
	{
		 AnsiString strErr = "Нельзя сохранить файл не содержащий ниодного дефекта.";
		 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
		 return;
	}

	if(DefectSaveDialog->Execute() == true)
	{
		AnsiString strFileName = DefectSaveDialog->FileName;
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
			int nSeek = 0;
			if(m_EditRec.SaveToFile(hFile, &nSeek) == true)
			{
             //всё хорошо
			}
			else
			{
			 AnsiString strErr = "Не удалось записать в файл \"" + strFileName + "\". Ошибка в позиции " + nSeek;
			 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
			}
			CloseHandle(hFile);
		}
		else
		{
		 AnsiString strErr = "Не удалось открыть файл \"" + strFileName + "\" для записи.";
		 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefectForm::MoveUpSpeedButtonClick(TObject *Sender)
{
	int nIndex;

	nIndex = DefectListBox->ItemIndex;

	if(Swap(nIndex, nIndex-1));
	{
	 DefectListBox->ItemIndex = nIndex-1;
	 SetControlButton();
	}
}
//---------------------------------------------------------------------------
bool __fastcall TDefectForm::Swap(int nIndex1, int nIndex2)
{
	bool bRet = false;
	int nCount = DefectListBox->Items->Count;
	if((nIndex1 >= 0) && (nIndex2 >= 0) &&
	   (nIndex1 < nCount) && (nIndex2 < nCount) &&
	   (nIndex1 != nIndex2))
	{
	 DefectListBox->Items->Exchange(nIndex1, nIndex2);
	 std::swap(m_EditRec[nIndex1], m_EditRec[nIndex2]);
	 bRet = true;
	}
	return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TDefectForm::MoveDownSpeedButtonClick(TObject *Sender)
{
	int nIndex;

	nIndex = DefectListBox->ItemIndex;

	if(Swap(nIndex, nIndex+1));
	{
	 DefectListBox->ItemIndex = nIndex+1;
	 SetControlButton();
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefectForm::AddDefectBitBtnClick(TObject *Sender)
{
	TDefect rec;
	if(EditRec(rec) == true)
	{//пользователь не передумал
	 int nIndex;
	 nIndex = DefectListBox->ItemIndex;
	 nIndex++;
	 if(nIndex < 0 || nIndex >= DefectListBox->Items->Count)
	 {//добавляем в конец
		m_EditRec.push_back(rec);
		DefectListBox->Items->Add(rec.m_sName);
		DefectListBox->ItemIndex = DefectListBox->Items->Count - 1;
	 }
	 else
	 {//добавляем в середину
		m_EditRec.insert(m_EditRec.begin() + nIndex, rec);
		DefectListBox->Items->Insert(nIndex, rec.m_sName);
	 }
	 SetControlButton();
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefectForm::EditDefectBitBtnClick(TObject *Sender)
{
	int nIndex;
	nIndex = DefectListBox->ItemIndex;
	if(nIndex >= 0)
	{
	 TDefect &rec = m_EditRec[nIndex];
	 if(EditRec(rec) == true)
	 {
	  DefectListBox->Items->Strings[nIndex] = rec.m_sName;
	 }
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefectForm::DelDefectBitBtnClick(TObject *Sender)
{
	int nIndex;
	nIndex = DefectListBox->ItemIndex;
	if(nIndex >= 0)
	{
	 DefectListBox->Items->Delete(nIndex);
	 m_EditRec.erase(m_EditRec.begin()+nIndex);
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefectForm::PictSpeedButtonClick(TObject *Sender)
{
	int nIndex;
	nIndex = DefectListBox->ItemIndex;
	if(nIndex >= 0)
	{
	 TDefect &rec = m_EditRec[nIndex];
	 if(m_pPictForm == NULL)
	 {
	  m_pPictForm = new TPictuteForm(this);
	 }
	 m_pPictForm->PaintMask(rec.m_vMask, m_nWidth, m_nHeight);
	}
}
//---------------------------------------------------------------------------
bool __fastcall TDefectForm::EditRec(TDefect &rec)
{
	bool bRet;
	if (m_pDefectEditForm == NULL)
	{
	 m_pDefectEditForm = new TDefectEditForm(this);
	}
	bRet = m_pDefectEditForm->EditDefect(rec, m_nWidth, m_nHeight);
	return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TDefectForm::FormHide(TObject *Sender)
{
	if (m_pPictForm != NULL)
	{
		m_pPictForm->Close();
		delete m_pPictForm;
		m_pPictForm = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefectForm::FormDestroy(TObject *Sender)
{
	if (m_pDefectEditForm != NULL)
	{
		m_pDefectEditForm->Close();
		delete m_pDefectEditForm;
		m_pDefectEditForm = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TDefectForm::DefectListBoxClick(TObject *Sender)
{
	SetControlButton();
}
//---------------------------------------------------------------------------

