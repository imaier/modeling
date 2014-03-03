//---------------------------------------------------------------------------

#ifndef DistributionUnitH
#define DistributionUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
#include "QuantityByGroupeUnit.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TWaitCursor
{
private:
	TCursor m_Old;
public:
	TWaitCursor(TCursor NewCursor = crHourGlass)
	{
		m_Old =  Screen->Cursor;
		Screen->Cursor = NewCursor;
	};

	~TWaitCursor()
	{
		Screen->Cursor = m_Old;
	};
};

class TMyCriticalSection
{

private:
	TCriticalSection *m_pCS;
public:
	TMyCriticalSection(void)
	{
		m_pCS = new TCriticalSection();
	};

	~TMyCriticalSection()
	{
		delete m_pCS;
	}


	void Enter(void)
	{
		m_pCS->Enter();
	};
	void Leave(void)
	{
		m_pCS->Leave();
	};
};


class TAutoLock
{
private:
	TMyCriticalSection &m_CS;
public:
	TAutoLock(TMyCriticalSection& CS):m_CS(CS)
	{
		m_CS.Enter();
	};

	~TAutoLock()
	{
		m_CS.Leave();
	};
};
//---------------------------------------------------------------------------
class TDistributionForm : public TForm
{
__published:	// IDE-managed Components
	TChart *DistributionChart;
	TBarSeries *DistributionSeries;
	TPanel *ToolPanel;
	TCheckBox *PrecentCheckBox;
	TCheckBox *LegendCheckBox;
	TSpeedButton *AutoScaleSpeedButton;
	TCheckBox *ProbNameCheckBox;
	void __fastcall AutoScaleSpeedButtonClick(TObject *Sender);
	void __fastcall PrecentCheckBoxClick(TObject *Sender);
	void __fastcall LegendCheckBoxClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ProbNameCheckBoxClick(TObject *Sender);
private:	// User declarations
	TMyCriticalSection m_cs;
public:		// User declarations
	__fastcall TDistributionForm(TComponent* Owner);

	void SetDataAndShow(TAtomCntBase &Layer, AnsiString strName);
};
//---------------------------------------------------------------------------
extern PACKAGE TDistributionForm *DistributionForm;
//---------------------------------------------------------------------------
#endif
