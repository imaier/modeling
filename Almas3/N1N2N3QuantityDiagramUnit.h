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
//---------------------------------------------------------------------------
#include "DistributionUnit.h"
#include "Dissolution.h"
//---------------------------------------------------------------------------
class TN1N2N3QuantityDiagramForm : public TForm
{
__published:	// IDE-managed Components
	TChart *N1N2N3Chart;
	TFastLineSeries *OneLinkSeries;
	TFastLineSeries *TwoLinkSeries;
	TFastLineSeries *ThreeLinkSeries;
	TFastLineSeries *PopularTypeSeries;
	TFastLineSeries *nS_Series;
private:	// User declarations
	TMyCriticalSection m_cs;
public:		// User declarations
	__fastcall TN1N2N3QuantityDiagramForm(TComponent* Owner);

	void SetDataAndShow(const TStaticticDataVec& vecSD);
};
//---------------------------------------------------------------------------
extern PACKAGE TN1N2N3QuantityDiagramForm *N1N2N3QuantityDiagramForm;
//---------------------------------------------------------------------------
#endif
