//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProgressUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProgressForm *ProgressForm;
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
bool TProgressRec::operator=(const TProgressRec& r)
{
	m_strOperation = r.m_strOperation;
	m_strState = r.m_strState;
	m_nMax = r.m_nMax;
	m_nCurr = r.m_nCurr;
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
	return TProgressProvider::m_Instanse;
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
		pForm->Close();
		delete pForm;
		pForm = NULL;
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
