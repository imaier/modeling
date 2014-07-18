//---------------------------------------------------------------------------
#ifndef MonitoringH
#define MonitoringH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TMonitoringForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *OuterDataGroupBox;
	TPanel *DeletingLayersPanel;
	TLabel *DeletingLayersNumLabel;
	TLabel *DeletingLayersTextLabel;
	TPanel *DeletedLayersPanel;
	TLabel *DeletedLayersNumLabel;
	TLabel *DeletedLayersTextLabel;
	TPanel *N3Panel;
	TLabel *N3NumLabel;
	TLabel *N3TextLabel;
	TPanel *N2Panel;
	TLabel *N2NumLabel;
	TLabel *N2TextLabel;
	TPanel *N1Panel;
	TLabel *N1NumLabel;
	TLabel *N1TextLabel;
	TPanel *DeletedAtomPanel;
	TLabel *DeletedAtomNumLabel;
	TLabel *DeletedAtomTextLabel;
	TGroupBox *InnerDataGroupBox;
	TPanel *PlanePanel;
	TLabel *PlaneNumLabel;
	TLabel *PlaneTextLabel;
	TPanel *N1ProbabilityPanel;
	TLabel *N1ProbabilityNumLabel;
	TLabel *N1ProbabilityTextLabel;
	TPanel *N3ProbabilityPanel;
	TLabel *N3ProbabilityNumLabel;
	TLabel *N3ProbabilityTextLabel;
	TPanel *N2ProbabilityPanel;
	TLabel *N2ProbabilityNumLabel;
	TLabel *N2ProbabilityTextLabel;
	TTimer *MonitoringTimer;
	TPanel *NumOfAtomsInLayerPanel;
	TListBox *NumOfAtomsInLayerListBox;
	TPanel *StatisticsPanel;
	TGroupBox *StatisticsGroupBox;
	TPanel *StartTimePanel;
	TLabel *StartTimeNumLabel;
	TLabel *StartTimeTextLabel;
	TPanel *DissolutionTimePanel;
	TLabel *DissolutionTimeNumLabel;
	TLabel *DissolutionTimeTextLabel;
	TPanel *CompleteTimePanel;
	TLabel *CompleteTimeNumLabel;
	TLabel *CompleteTimeTextLabel;
	TPanel *RemainedTimePanel;
	TLabel *RemainedTimeNumLabel;
	TLabel *RemainedTimeTextLabel;
	TPanel *ProgressPanel;
	TProgressBar *ProgressBar;
	TPanel *StatePanel;
	TLabel *StateNumLabel;
	TLabel *StateTextLabel;
	TPanel *AverageSpeedPanel;
	TLabel *AverageSpeedNumLabel;
	TLabel *AverageSpeedTextLabel;
	TPanel *FluidSpeedPanel;
	TLabel *FluidSpeedNumLabel;
	TLabel *FluidSpeedTextLabel;
	TPanel *EnablePanel;
	TCheckBox *EnableCheckBox;
	TSpeedButton *StatisticSpeedButton;
	void __fastcall MonitoringTimerTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall StatisticSpeedButtonClick(TObject *Sender);
	
	
private:	// User declarations
    TDateTime LastTime;
    int DelAtomAtLastTime;
public:		// User declarations
	__fastcall TMonitoringForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TMonitoringForm *MonitoringForm;
//---------------------------------------------------------------------------
#endif
