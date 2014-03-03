//---------------------------------------------------------------------------

#ifndef ScreenCopyUnitH
#define ScreenCopyUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TScreenCopyForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *ButtonsPanel;
    TPanel *OkPanel;
    TButton *OkButton;
    TPanel *CancelPanel;
    TButton *CancelButton;
    TLabel *HeightLabel;
    TEdit *HeightEdit;
    TCheckBox *RatioCheckBox;
    TLabel *WidthLabel;
    TEdit *WidthEdit;
    TEdit *QualityEdit;
    TLabel *QualityLabel;
    TCheckBox *PintIndexCheckBox;
    void __fastcall OkButtonClick(TObject *Sender);
    void __fastcall HeightEditChange(TObject *Sender);
    void __fastcall WidthEditChange(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    bool Semapore;
public:		// User declarations
     int OriginalHeight;
     int OriginalWidth;
     int SamHeight;
     int SamWidth;
     int SamQuality;
     bool PrintIndex;
    __fastcall TScreenCopyForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TScreenCopyForm *ScreenCopyForm;
//---------------------------------------------------------------------------
#endif
