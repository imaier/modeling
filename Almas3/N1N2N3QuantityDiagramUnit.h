//---------------------------------------------------------------------------

#ifndef N1N2N3QuantityDiagramUnitH
#define N1N2N3QuantityDiagramUnitH
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
#include <ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include "DistributionUnit.h"
#include "Dissolution.h"
#include "SelectAtomKindsFormUnit.h"
#include "TeeFunci.hpp"
//---------------------------------------------------------------------------
class TN1N2N3QuantityDiagramForm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *StatisticPageControl;
	TTabSheet *AtomQuantityByDeleteAtomQuantityTabSheet;
	TTabSheet *QuantityDeletedAtomByAtomTypeTabSheet;
	TChart *N1N2N3Chart;
	TFastLineSeries *OneLinkSeries;
	TFastLineSeries *TwoLinkSeries;
	TFastLineSeries *ThreeLinkSeries;
	TFastLineSeries *PopularTypeSeries;
	TFastLineSeries *nS_Series;
	TChart *QuantityDeletedAtomByAtomTypeChart;
	TBarSeries *QuantityDeletedAtomByAtomTypeSeries;
	TTabSheet *ParametricGraphTabSheet;
	TChart *ParametrińChart;
	TFastLineSeries *ParametrińSeries;
	TSpeedButton *SelectAtomKindsSpeedButton;
	TCheckBox *RemovMarksCheckBox;
	TSpeedButton *SaveImageSpeedButton;
	TTabSheet *RoughnessTabSheet;
	TChart *RoughnessChart;
	TAreaSeries *RoughnessSeries;
	TTabSheet *AverageLevelTabSheet;
	TChart *AverageLevelChart;
	TAreaSeries *AverageLevelSeries;
	TLineSeries *ThicknessSeries;
	void __fastcall SelectAtomKindsSpeedButtonClick(TObject *Sender);
	void __fastcall RemovMarksCheckBoxClick(TObject *Sender);
	void __fastcall SaveImageSpeedButtonClick(TObject *Sender);
private:	// User declarations
	TMyCriticalSection m_cs;
	TAtomKindsOnAxes SelectedAxes;
	TStatisticsDataVec m_vecSD;

	void __fastcall TN1N2N3QuantityDiagramForm::UpdateParametrińSeries(void);
public:		// User declarations
	__fastcall TN1N2N3QuantityDiagramForm(TComponent* Owner);

	void SetDataAndShow(const TStatisticsDataVec& vecSD);
};
//---------------------------------------------------------------------------
extern PACKAGE TN1N2N3QuantityDiagramForm *N1N2N3QuantityDiagramForm;
//---------------------------------------------------------------------------
#endif
