//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProgressUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <math.h>
TProgressForm *ProgressForm;
static TProgressProvider Instanse;
//---------------------------------------------------------------------------
TProgressRec::TProgressRec()
{
	Init();
}
//---------------------------------------------------------------------------
void TProgressRec::Init()
{
	m_strOperation = "";
	m_strState = "";
	m_nMax = 0;
	m_nCurr = 0;
}
//---------------------------------------------------------------------------
bool TProgressRec::operator==(const TProgressRec& r) const
{
	bool bRet = true;
	bRet &= m_strOperation == r.m_strOperation;
	bRet &= m_strState == r.m_strState;
	bRet &= m_nMax == r.m_nMax;
	bRet &= m_nCurr == r.m_nCurr;
	return bRet;
}
//---------------------------------------------------------------------------
TProgressRec&  TProgressRec::operator=(const TProgressRec& r)
{
	m_strOperation = r.m_strOperation;
	m_strState = r.m_strState;
	m_nMax = r.m_nMax;
	m_nCurr = r.m_nCurr;
	return *this;
}
//---------------------------------------------------------------------------
__fastcall TProgressForm::TProgressForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
TProgressProvider::TProgressProvider()
{
	m_pForm = NULL;
	m_bStopped = false;
}
//---------------------------------------------------------------------------
TProgressProvider::~TProgressProvider()
{
	if(m_pForm != NULL)
	{
		delete m_pForm;
	}
}
//---------------------------------------------------------------------------
TProgressProvider& TProgressProvider::GetInstanse()
{
	return Instanse;
}
//---------------------------------------------------------------------------
void TProgressProvider::PostProgress(const TProgressRec& r)
{
	if(m_pForm == NULL)
	{
		m_pForm = new TProgressForm(NULL);
	}

	if(m_pForm->Visible == false)
	{
		m_pForm->Show();
	}

	//m_pForm->BringToFront();

	m_pForm->PostProgress(r);
}
//---------------------------------------------------------------------------
void TProgressProvider::FinishProgress()
{
	if(m_pForm != NULL)
	{
		m_pForm->Close();
		delete m_pForm;
		m_pForm = NULL;
	}

	m_bStopped = false;
}
//---------------------------------------------------------------------------
bool TProgressProvider::IsStopped()
{
	return m_bStopped;
}
//---------------------------------------------------------------------------
void TProgressProvider::SetStopped()
{
	m_bStopped = true;
}
//---------------------------------------------------------------------------
void TProgressForm::PostProgress(const TProgressRec& r)
{
	bool bUpdated = false;
	if (r.m_strOperation != OperationLabel->Caption)
	{
	 OperationLabel->Caption = r.m_strOperation;
	 //OperationLabel->Repaint();
	 bUpdated = true;
	}
	if (r.m_strState != StateLabel->Caption)
	{
	 StateLabel->Caption = r.m_strState;
	 bUpdated = true;
	 //StateLabel->Repaint();
	}
	int pos = ceil((double)r.m_nCurr/(double)r.m_nMax*100.0+0.5);

	if(OperationProgressBar->Position != pos)
	{
	 OperationProgressBar->Position = pos;
	 bUpdated = true;
	 //OperationProgressBar->Repaint();
	}

	if(bUpdated == true)
	{
	 MSG msg;
	 BOOL bRet = TRUE;
	 int i = 1000;


	 //while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
	 while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE) != 0)
	 {
		i--;
		if(i==0)
		{
		// break;
		}

		if (bRet == -1)
		{
			 // обработка ошибки и возможный выход из программы
		}
		 else
		 {
			 TranslateMessage(&msg);
			 DispatchMessage(&msg);
		}
	 }
	}
}
//---------------------------------------------------------------------------
void __fastcall TProgressForm::CancelBitBtnClick(TObject *Sender)
{
	TProgressProvider::GetInstanse().SetStopped();
}
//---------------------------------------------------------------------------

