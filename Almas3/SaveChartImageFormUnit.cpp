//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SaveChartImageFormUnit.h"
#include "Chart.hpp"
#include <vector>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSaveChartImageForm::TSaveChartImageForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TSaveChartImageForm::InitAndShowDialog(TStrings *ChartList)
{
	ChartComboBox->Clear();
	for (int i = 0; i < ChartList->Count; i++)
	{
		ChartComboBox->AddItem(ChartList->Strings[i], ChartList->Objects[i]);
	}
	ChartComboBox->ItemIndex = 0;

	ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TSaveChartImageForm::OkButtonClick(TObject *Sender)
{
	ChartSaveDialog->FileName =  ChartComboBox->Items->Strings[ChartComboBox->ItemIndex];
	if(ChartSaveDialog->Execute())
	{

		TChart *Chart = (TChart*)(ChartComboBox->Items->Objects[ChartComboBox->ItemIndex]);

		bool SavedLegend = Chart->Legend->Visible;
		Chart->Legend->Visible = !RemoveLegendCheckBox->Checked;
		std::vector<TColor> vSavedColor;
		if(BlackSeriesCheckBox->Checked)
		{
			for (int i = 0; i < Chart->SeriesCount(); i++)
			{
				vSavedColor.push_back(Chart->Series[i]->Color);
				Chart->Series[i]->Color = clBlack;
			}
		}

		if(ChartSaveDialog->FilterIndex == 1 )
		{
			Chart->SaveToMetafile(ChartSaveDialog->FileName);
		}
		else
		{
			Chart->SaveToBitmapFile(ChartSaveDialog->FileName);
		}

		Chart->Legend->Visible = SavedLegend;
		for (UINT i = 0; i < vSavedColor.size() ; i++)
		{
			Chart->Series[i]->Color = vSavedColor[i];
		}

	}

	Close();
}
//---------------------------------------------------------------------------

