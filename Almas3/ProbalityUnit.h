//---------------------------------------------------------------------------

#ifndef ProbalityUnitH
#define ProbalityUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include <map>
#include "ProbPoviderUnit.h"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
class TProbalityForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *ButtonsPanel;
    TPanel *OkPanel;
    TButton *OkButton;
    TPanel *CancelPanel;
    TButton *CancelButton;
    TPanel *PageControlPanel;
    TPageControl *ProbalityPageControl;
    TTabSheet *OneLinkTabSheet;
    TTabSheet *TwoLinksTabSheet;
    TOpenDialog *ProbOpenDialog;
    TSaveDialog *ProbSaveDialog;
    TSpeedButton *LoadSpeedButton;
    TSpeedButton *SaveSpeedButton;
    TLabel *E0Label;
    TLabel *ELabel;
    TSpeedButton *Prob1SpeedButton;
    TEdit *E0Edit;
    TEdit *EEdit;
    TListView *ProbListView;
    TEdit *ValueEdit;
    TPanel *ProbSetDiscriptionPanel;
    TLabel *ProbSetNameLabel;
	TLabel *ProbSetLabel;
    TLabel *ProbeSetTableLabel;
    TSpeedButton *SetModelSpeedButton;
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall SaveSpeedButtonClick(TObject *Sender);
    void __fastcall LoadSpeedButtonClick(TObject *Sender);
    void __fastcall Prob1SpeedButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
    void __fastcall SetModelSpeedButtonClick(TObject *Sender);
    void __fastcall ProbListViewSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
    void __fastcall ValueEditExit(TObject *Sender);
	void __fastcall ProbListViewColumnDragged(TObject *Sender);
	void __fastcall ProbListViewResize(TObject *Sender);
	void __fastcall ProbListViewCustomDraw(TCustomListView *Sender, const TRect &ARect,
          bool &DefaultDraw);
	void __fastcall ProbListViewMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ProbListViewMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall ProbListViewColumnClick(TObject *Sender, TListColumn *Column);
	void __fastcall OkButtonClick(TObject *Sender);
	void __fastcall ProbListViewKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ProbListViewDataHint(TObject *Sender, int StartIndex, int EndIndex);



private:	// User declarations
    bool ReadAllProbality(bool SetFocusOnError);

    int SetModelDlg();
    int SetModelCntl();
	TListItem *m_EditItem;
	TProbPovider m_EditProb;//провайдер вероятностей (редактируемый)

public:		// User declarations

	bool EditProb(TProbPovider &SP);//редактировать вероятности
	__fastcall TProbalityForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TProbalityForm *ProbalityForm;
//---------------------------------------------------------------------------
#endif
