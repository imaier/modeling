//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#pragma warn -pck

#include "ProbalityUnit.h"
#include "math.h"
#include "stdio.h"
#include "ProbSetModelUnit.h"
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProbalityForm *ProbalityForm;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TProbalityForm::TProbalityForm(TComponent* Owner)
    : TForm(Owner)
{
    m_EditItem = NULL;
}
//---------------------------------------------------------------------------
/*
void TProbalityForm::InitForm(TProbPovider &SP)
{
	m_EditProb = SP;
	RetProb = &SP;
}
*/
//---------------------------------------------------------------------------
bool TProbalityForm::ReadAllProbality(bool SetFocusOnError)
{
	ValueEditExit(NULL);

	AnsiString S;
    AnsiString strErr;
    double dProb;
    int nCnt = ProbListView->Items->Count;
    IBaseProbSet *pIProbSet = m_EditProb.GetInterface();
    if(pIProbSet == NULL)
      return false;
    if(pIProbSet->GetGlobalData().GetAllNumProbality() != nCnt)
      return false;
    for(int i = 0; i < nCnt; i++)
    {
	 S = ProbListView->Items->Item[i]->SubItems->Strings[0];
	 if(GetProbalityValue(S, dProb, strErr) == false)
     {
      if(SetFocusOnError == true)
      {
       ProbListView->Items->Item[i]->Selected = true;
       ShowErrorCtrl(strErr, ValueEdit);
      }
      return false;
     }
     pIProbSet->SetProbValue(i, dProb);
    }
/*

    int nAlgoritmKind = GetAlgDiss();
    if(nAlgoritmKind == CB_ERR)
    {
     if(SetFocusOnError == true)
     {
      AnsiString Text = "Не выбран алгоритм расстворения.";
      ShowErrorCtrl(Text, AlgMontecarloRadioButton);
	 }
	 return false;
	}
	else
	{
	 TempSP.m_nAlgoritmKind = nAlgoritmKind;
	}
	if(ReadEditDouble(PorogEdit,SetFocusOnError, TempSP.m_dPorog) == false)
	 return false;

	if(ReadEditDouble(DolaEdit,SetFocusOnError, TempSP.m_dDola) == false)
	 return false;
*/
	return true;
}

//---------------------------------------------------------------------------
void __fastcall TProbalityForm::FormCloseQuery(TObject *Sender,
	  bool &CanClose)
{
	if(ModalResult == mrOk)
	{
	 if(ReadAllProbality(true) == true)
	 {//всё правильно

	 }
	 else
	 {
	  CanClose = false;
	  return;
	 }
	}
	CanClose = true;
}
//---------------------------------------------------------------------------
void __fastcall TProbalityForm::SaveSpeedButtonClick(TObject *Sender)
{
	if(ReadAllProbality(true) == false)
	 return;

	if(ProbSaveDialog->Execute() == true)
	{
		AnsiString strFileExt = ExtractFileExt(ProbSaveDialog->FileName);
		AnsiString strFN =ProbSaveDialog->FileName;
		strFileExt.LowerCase();
		if(strFileExt != ".prb")
		{
			TProbPovider TempSP = m_EditProb;
			double dVal;
			FILE *pFile;
			char szBuff[256];
			pFile = fopen(_c_str(strFN), "w");
			if(pFile != NULL)
			{
				int i;
				int nPobCnt = TempSP.GetInterface()->GetGlobalData().GetAllNumProbality();
				for(i=0; i < nPobCnt; i++)
				{
					dVal = TempSP.GetInterface()->GetProbValue(i);
					sprintf(szBuff, "%g\n", dVal);
					if(0 > fputs(szBuff, pFile))
					{
						break;
					}
				}
				fclose(pFile);

				if(i != nPobCnt)
				{
					 AnsiString strErr = "Не удалось записать в файл \"" + ProbOpenDialog->FileName + "\" нужное количество чисел: \n Нужно " + IntToStr(nPobCnt) + ", записано " + IntToStr(i) + ".\n" + strErr;
					 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
				}
			}
		}
		else
		{
			TProbPovider TempSP = m_EditProb;
			TempSP.SaveToFile(ProbSaveDialog->FileName);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TProbalityForm::LoadSpeedButtonClick(TObject *Sender)
{
	if(ProbOpenDialog->Execute() == true)
	{
		AnsiString strFileExt = ExtractFileExt(ProbOpenDialog->FileName);
		strFileExt.LowerCase();
		if(strFileExt != ".prb")
		{
			TProbPovider TempSP = m_EditProb;
			AnsiString strFN =ProbOpenDialog->FileName;
			AnsiString strVal, strErr;
			double dVal;
			FILE *pFile;
			char szBuff[256];
			pFile = fopen(_c_str(strFN), "r");
			if(pFile != NULL)
			{
				int i;
				int nPobCnt = TempSP.GetInterface()->GetGlobalData().GetAllNumProbality();
				for(i=0; i < nPobCnt; i++)
				{
					if(NULL == fgets(szBuff, sizeof(szBuff), pFile))
					{
						break;
					}
					dVal = atof(szBuff);
					strVal = szBuff;
					if(GetProbalityValue(strVal, dVal, strErr) == false)
					 break;

					TempSP.GetInterface()->SetProbValue(i, dVal);
				}
				fclose(pFile);
				if(i == nPobCnt)
				{
					m_EditProb = TempSP;
					SetModelCntl();
				}
				else
				{
					 AnsiString strErr = "Не удалось прочитать из файла \"" + ProbOpenDialog->FileName + "\" нужное количество чисел: \nнужно " + IntToStr(nPobCnt) + ", прочитано " + IntToStr(i) + ".\n" + strErr;
					 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
				}
			}
			else
			{
             AnsiString strErr = "Не удалось открыть файл \"" + ProbOpenDialog->FileName + "\" для чтения.";
			 MessageBox(NULL, _c_str(strErr), "Ошибка", MB_ICONERROR);
            }
        }
        else
		{
			TProbPovider TempSP = m_EditProb;
			TempSP.LoadFromFile(ProbOpenDialog->FileName);
            m_EditProb = TempSP;
            SetModelCntl();
		}
    }
}
//---------------------------------------------------------------------------
void __fastcall TProbalityForm::Prob1SpeedButtonClick(TObject *Sender)
{
	double dE0,dE;
	dE0=-1;
	dE=-1;
	if(ReadEditDouble(E0Edit,true,dE0)==false)
		return;
	if(ReadEditDouble(EEdit,true,dE)==false)
		return;
	//TempSP.CalcAlg1(dE0,dE);
	//InitForm(&TempSP);
}
//---------------------------------------------------------------------------
void __fastcall TProbalityForm::FormShow(TObject *Sender)
{
	if(m_EditProb.GetInterface() == NULL)
	{
	 if(SetModelDlg()== 0)
	 {
	  ModalResult = mrCancel;
	  //Close();
	  if(CloseQuery())
	  {
		  return;
	  }
	 }
    }
	SetModelCntl();
}
//---------------------------------------------------------------------------
void __fastcall TProbalityForm::SetModelSpeedButtonClick(TObject *Sender)
{
    if(SetModelDlg() != 0)
    {
     SetModelCntl();
    }
}
//---------------------------------------------------------------------------
int TProbalityForm::SetModelDlg(void)
{
    int nRet = 0;
    TProbSetModelForm *pProbSetModelForm;
    pProbSetModelForm = new TProbSetModelForm(this);
    pProbSetModelForm->InitForm(m_EditProb);
    if(pProbSetModelForm->ShowModal() == mrOk)
    {
     nRet = 1;
    }
    delete pProbSetModelForm;
    return nRet;
}
//---------------------------------------------------------------------------
int TProbalityForm::SetModelCntl(void)
{
    ProbListView->Clear();
    ProbSetLabel->Caption = "";
    IBaseProbSet *pPS = m_EditProb.GetInterface();
    if(pPS != NULL)
    {
     int nProbCnt = pPS->GetGlobalData().GetAllNumProbality();
	 ProbListView->Clear();
     for(int i=0; i < nProbCnt; i++)
     {
      TListItem *pItem  = ProbListView->Items->Add();
      pItem->Caption = pPS->GetGlobalData().GetProbName(i);
	  pItem->SubItems->Add(pPS->GetProbValue(i));
     }
     ProbSetLabel->Caption = pPS->GetGlobalData().GetProbSetNameString();
    }
	return 1;
}
//---------------------------------------------------------------------------
void __fastcall TProbalityForm::ProbListViewSelectItem(TObject *Sender,
	  TListItem *Item, bool Selected)
{
	ValueEditExit(Sender);
	IBaseProbSet *pPS = m_EditProb.GetInterface();
	if(Item!=NULL && pPS != NULL && Selected == true)
	{
		ValueEdit->Visible = true;
		ValueEdit->Text = Item->SubItems->Strings[0];
		ValueEdit->SelectAll();
		TPoint pos = Item->GetPosition();
		//ValueEdit->Left = ProbListView->Columns->Items[0]->Width + 3 + ProbListView->Left;
		ValueEdit->Top = pos.y + ProbListView->Top + 1;
		//ValueEdit->Width = ProbListView->Columns->Items[1]->Width;
		ProbListViewColumnDragged(Sender);
		//ValueEdit->Height = ProbListView->i
		m_EditItem = Item;
	}
	else
	{
		ValueEdit->Visible = false;
		m_EditItem = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TProbalityForm::ValueEditExit(TObject *Sender)
{
	if(m_EditItem != NULL)
	{
		m_EditItem->SubItems->Strings[0] = ValueEdit->Text;
	}
}
//---------------------------------------------------------------------------
void __fastcall TProbalityForm::ProbListViewColumnDragged(TObject *Sender)
{
	if(ValueEdit->Visible == true)
	{
		int nLeft = ProbListView->Columns->Items[0]->Width + 3 + ProbListView->Left;
		int nWidth = ProbListView->Columns->Items[1]->Width;

		if(ValueEdit->Left != nLeft)
		{
		 ValueEdit->Left = nLeft;
		 //ProbListView->Invalidate();
		}

		if(ValueEdit->Width != nWidth)
		{
		 ValueEdit->Width = nWidth;
		 //ProbListView->Invalidate();
		}

	}
}
//---------------------------------------------------------------------------
void __fastcall TProbalityForm::ProbListViewResize(TObject *Sender)
{
	//ProbListViewColumnDragged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TProbalityForm::ProbListViewCustomDraw(TCustomListView *Sender, const TRect &ARect,
		  bool &DefaultDraw)
{
	//ProbListViewColumnDragged(Sender);

	static TListItem* pTopItem = NULL;
	TListItem* pCurrTop = ProbListView->TopItem;

	if(pTopItem != pCurrTop)
	{
	 if(m_EditItem != NULL || ValueEdit->Visible == true)
	 {
		TPoint pos = m_EditItem->GetPosition();
		//ValueEdit->Left = ProbListView->Columns->Items[0]->Width + 3 + ProbListView->Left;
		ValueEdit->Top = pos.y + ProbListView->Top + 1;
		//ValueEdit->Width = ProbListView->Columns->Items[1]->Width;
		//ProbListViewColumnDragged(Sender);
		//ValueEdit->Height = ProbListView->i
	 }
	 pTopItem = pCurrTop;
	}



}
//---------------------------------------------------------------------------

void __fastcall TProbalityForm::ProbListViewMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	//ProbListViewColumnDragged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TProbalityForm::ProbListViewMouseMove(TObject *Sender, TShiftState Shift,
		  int X, int Y)
{
	//ProbListViewColumnDragged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TProbalityForm::ProbListViewColumnClick(TObject *Sender, TListColumn *Column)

{
	ProbListViewColumnDragged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TProbalityForm::OkButtonClick(TObject *Sender)
{
	ValueEditExit(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TProbalityForm::ProbListViewKeyPress(TObject *Sender, wchar_t &Key)

{
	if(ValueEdit->Visible == true)
	{
		//ValueEdit->DoKeyPress(Key);
		//ValueEdit->KeyPress(Key);

		//ValueEdit->Broadcast()
		ValueEdit->Perform(WM_CHAR, Key, 0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TProbalityForm::ProbListViewDataHint(TObject *Sender, int StartIndex,
		  int EndIndex)
{
	ProbListViewColumnDragged(Sender);
}
//---------------------------------------------------------------------------
bool TProbalityForm::EditProb(TProbPovider &SP)
{
	bool bRet = false;
	m_EditProb = SP;
	if(m_EditProb.GetInterface() == NULL)
	{
	 if(SetModelDlg() == 0)
	 {
	  return bRet;
	 }
	 SP = m_EditProb;
	}
	if(ShowModal() == mrOk)
	{
	 SP = m_EditProb;
	}
	return bRet;
}
//---------------------------------------------------------------------------

