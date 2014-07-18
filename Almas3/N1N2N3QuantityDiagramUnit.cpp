//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "N1N2N3QuantityDiagramUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TN1N2N3QuantityDiagramForm *N1N2N3QuantityDiagramForm;
//---------------------------------------------------------------------------
__fastcall TN1N2N3QuantityDiagramForm::TN1N2N3QuantityDiagramForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TN1N2N3QuantityDiagramForm::SetDataAndShow(const TStaticticDataVec& vecSD)
{
	TAutoLock lock(m_cs);

	TWaitCursor wc;

	Hide();

	OneLinkSeries->Clear();
	TwoLinkSeries->Clear();
	ThreeLinkSeries->Clear();

	int nCnt = vecSD.size();
	AnsiString strName;
	for(int i=0; i < nCnt; i++)
	{
	 const TStaticticData &sd = vecSD[i];
	 OneLinkSeries->AddXY(sd.Deleted, sd.N1, strName, clTeeColor);
	 TwoLinkSeries->AddXY(sd.Deleted, sd.N2, strName, clTeeColor);
	 ThreeLinkSeries->AddXY(sd.Deleted, sd.N3, strName, clTeeColor);
	}

	Show();

	N1N2N3Chart->UndoZoom();
}
//---------------------------------------------------------------------------

