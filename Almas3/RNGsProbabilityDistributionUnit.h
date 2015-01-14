//---------------------------------------------------------------------------

#ifndef RNGsProbabilityDistributionUnitH
#define RNGsProbabilityDistributionUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "ProbabilityDistributionThreadUnit.h"
#include "TeeFunci.hpp"
//---------------------------------------------------------------------------
class TRNGsProbabilityDistributionForm : public TForm
{
__published:	// IDE-managed Components
	TChart *DistributionChart;
	TAreaSeries *DistributionSeries;
	TPanel *InputDataPanel;
	TLabel *ModLabel;
	TEdit *ModEdit;
	TSpeedButton *StartSpeedButton;
	TSpeedButton *StopSpeedButton;
	TLabel *GenLabel;
	TLabel *GenCntLabel;
	TLineSeries *AverageSeries;
	TAverageTeeFunction *AverageTeeFunction;
	TCheckBox *InitRNGCheckBox;
	TCheckBox *RelativeScaleCheckBox;
	void __fastcall StartSpeedButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall StopSpeedButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RelativeScaleCheckBoxClick(TObject *Sender);
private:	// User declarations
	ProbabilityDistributionThread *pdThread;

	void __fastcall UpdateControls();
	void  __fastcall InitSeries(int Module);
public:		// User declarations
	__fastcall TRNGsProbabilityDistributionForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRNGsProbabilityDistributionForm *RNGsProbabilityDistributionForm;
//---------------------------------------------------------------------------
#endif
