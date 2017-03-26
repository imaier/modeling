//---------------------------------------------------------------------------

#ifndef SaveChartImageFormUnitH
#define SaveChartImageFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class TSaveChartImageForm : public TForm
{
__published:	// IDE-managed Components
	TComboBox *ChartComboBox;
	TCheckBox *BlackSeriesCheckBox;
	TCheckBox *RemoveLegendCheckBox;
	TLabel *ChartLabel;
	TPanel *ButtonsPanel;
	TPanel *OkPanel;
	TButton *OkButton;
	TPanel *CancelPanel;
	TButton *CancelButton;
	TSaveDialog *ChartSaveDialog;
	void __fastcall OkButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSaveChartImageForm(TComponent* Owner);
	void InitAndShowDialog(TStrings *ChartList);
};
//---------------------------------------------------------------------------
#endif
