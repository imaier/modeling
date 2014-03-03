//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MaskEditUnit.h"
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMaskEditForm *MaskEditForm;
//---------------------------------------------------------------------------
__fastcall TMaskEditForm::TMaskEditForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool TMaskEditForm::EditMask(TMaskVec &rec, int nWidth, int nHeight)//тру если изменилось
{
	bool bRet = false;
	m_EditRec = rec;

	m_nWidth = nWidth;
	m_nHeight = nHeight;

	if(ShowModal() == mrOk)
	{
	 bRet = true; /*To do*/
	 rec = m_EditRec;
	}
	m_EditRec.clear();
	return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TMaskEditForm::FormShow(TObject *Sender)
{
	MaskListBox->Items->Clear();
	UINT i;
	for(i = 0; i < m_EditRec.size(); i++)
	{
		TMask &rec = m_EditRec[i];
		MaskListBox->Items->Add(rec.TMaskToString());
	}

	SetControlButton();
}
//---------------------------------------------------------------------------
void __fastcall TMaskEditForm::SetControlButton()
{
	int nIndex, nCount;

	nIndex = MaskListBox->ItemIndex;
	nCount = MaskListBox->Items->Count;

	bool bIndexSelected = (nIndex >= 0) && (nCount > 0);
	bool bCountGrZero = (nCount > 0);
	bool bCountGrOne = (nCount > 1);
	bool bIndexFirst = (nIndex == 0) && (nCount > 0);
	bool bIndexLast = (nIndex == nCount -1);

	MoveUpSpeedButton->Enabled = bIndexSelected && !bIndexFirst && bCountGrOne;
	MoveDownSpeedButton->Enabled = bIndexSelected && !bIndexLast && bCountGrOne;
	AddMaskBitBtn->Enabled = true;
	EditMaskBitBtn->Enabled = bIndexSelected;
	DelMaskBitBtn->Enabled = bIndexSelected;
	PictSpeedButton->Enabled = bCountGrZero;
}
//---------------------------------------------------------------------------
void __fastcall TMaskEditForm::MoveUpSpeedButtonClick(TObject *Sender)
{
	int nIndex;

	nIndex = MaskListBox->ItemIndex;

	if(Swap(nIndex, nIndex-1));
	{
	 MaskListBox->ItemIndex = nIndex-1;
	 SetControlButton();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMaskEditForm::MoveDownSpeedButtonClick(TObject *Sender)
{
	int nIndex;

	nIndex = MaskListBox->ItemIndex;

	if(Swap(nIndex, nIndex+1));
	{
	 MaskListBox->ItemIndex = nIndex+1;
	 SetControlButton();
	}
}
//---------------------------------------------------------------------------
bool __fastcall TMaskEditForm::Swap(int nIndex1, int nIndex2)
{
	bool bRet = false;
	int nCount = MaskListBox->Items->Count;
	if((nIndex1 >= 0) && (nIndex2 >= 0) &&
	   (nIndex1 < nCount) && (nIndex2 < nCount) &&
	   (nIndex1 != nIndex2))
	{
	 MaskListBox->Items->Exchange(nIndex1, nIndex2);
	 std::swap(m_EditRec[nIndex1], m_EditRec[nIndex2]);
	 bRet = true;
	}
	return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TMaskEditForm::MaskListBoxClick(TObject *Sender)
{
	SetControlButton();
}
//---------------------------------------------------------------------------
void __fastcall TMaskEditForm::AddMaskBitBtnClick(TObject *Sender)
{
	TMask rec;
	rec.W = m_nWidth;
	rec.H = m_nHeight;

	rec.R = m_nWidth;

	if(EditRec(rec) == true)
	{//пользователь не передумал
	 int nIndex;
	 nIndex = MaskListBox->ItemIndex;
	 nIndex++;
	 if(nIndex < 0 || nIndex >= MaskListBox->Items->Count)
	 {//добавляем в конец
		m_EditRec.push_back(rec);
		MaskListBox->Items->Add(rec.TMaskToString());
		MaskListBox->ItemIndex = MaskListBox->Items->Count - 1;
	 }
	 else
	 {//добавляем в середину
		m_EditRec.insert(m_EditRec.begin() + nIndex, rec);
		MaskListBox->Items->Insert(nIndex, rec.TMaskToString());
	 }
	 SetControlButton();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMaskEditForm::EditMaskBitBtnClick(TObject *Sender)
{
	int nIndex;
	nIndex = MaskListBox->ItemIndex;
	if(nIndex >= 0)
	{
	 TMask &rec = m_EditRec[nIndex];
	 if(EditRec(rec) == true)
	 {
	  MaskListBox->Items->Strings[nIndex] = rec.TMaskToString();
	 }
	}
}
//---------------------------------------------------------------------------
void __fastcall TMaskEditForm::DelMaskBitBtnClick(TObject *Sender)
{
	int nIndex;
	nIndex = MaskListBox->ItemIndex;
	if(nIndex >= 0)
	{
	 MaskListBox->Items->Delete(nIndex);
	 m_EditRec.erase(m_EditRec.begin()+nIndex);
	 MaskListBox->ItemIndex = nIndex;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TMaskEditForm::EditRec(TMask &rec)
{
	bool bRet;
	if (m_pMaskForm == NULL)
	{
	 m_pMaskForm = new TMaskForm(this);
	}
	m_pMaskForm->InitForm(rec);
	if(m_pMaskForm->ShowModal() == mrOk)
	{
	 rec = m_pMaskForm->Mask;
	 bRet = true;
	}
	return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TMaskEditForm::FormDestroy(TObject *Sender)
{
	if (m_pMaskForm != NULL)
	{
		m_pMaskForm->Close();
		delete m_pMaskForm;
		m_pMaskForm = NULL;
	}
	if (m_pPictForm != NULL)
	{
		m_pPictForm->Close();
		delete m_pPictForm;
		m_pPictForm = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMaskEditForm::PictSpeedButtonClick(TObject *Sender)
{
	if(m_EditRec.size() > 0)
	{
 	 if(m_pPictForm == NULL)
	 {
	  m_pPictForm = new TPictuteForm(this);
	 }
	 m_pPictForm->PaintMask(m_EditRec, m_nWidth, m_nHeight);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMaskEditForm::LoadSpeedButtonClick(TObject *Sender)
{
	if(MaskOpenDialog->Execute() == true)
	{
		AnsiString strFileName = MaskOpenDialog->FileName;
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
			TMaskVec Rec;
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
		 AnsiString strErr = "Не удалось открыть файл \"" + strFileName + "\" для чтения.";
		 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TMaskEditForm::SaveSpeedButtonClick(TObject *Sender)
{
	int nMaskCount = MaskListBox->Items->Count;
	if( nMaskCount == 0)
	{
		 AnsiString strErr = "Нельзя сохранить файл не содержащий ниодной маски.";
		 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
		 return;
	}

	if(MaskSaveDialog->Execute() == true)
	{
		AnsiString strFileName = MaskSaveDialog->FileName;
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
void __fastcall TMaskEditForm::AddMaskFromFileSpeedButtonClick(TObject *Sender)
{
	if(MaskOpenDialog->Execute() == true)
	{
		AnsiString strFileName = MaskOpenDialog->FileName;
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
			TMaskVec Rec;
			int nSeek = 0;
			if(Rec.LoadFromFile(hFile, &nSeek) == true )
			{
			 int nIndex;
			 nIndex = MaskListBox->ItemIndex;
			 if(nIndex >= 0)
			 {
			  m_EditRec.insert(m_EditRec.begin()+nIndex + 1, Rec.begin(), Rec.end() );
			 }
			 else
			 {
			  m_EditRec.insert(m_EditRec.end(), Rec.begin(), Rec.end());
			 }
			 FormShow(NULL);
			 MaskListBox->ItemIndex = nIndex;
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
		 AnsiString strErr = "Не удалось открыть файл \"" + strFileName + "\" для чтения.";
		 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
		}
	}
}
//---------------------------------------------------------------------------

