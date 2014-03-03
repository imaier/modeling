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
    TCheckBox *CaptureCheckBox;
    TGroupBox *CaptureGroupBox;
    TGroupBox *DelAtomGroupBox;
    TLabel *FromLabel;
    TEdit *FromEdit;
    TEdit *StepEdit;
    TLabel *StepLabel;
    TLabel *ToLabel;
    TEdit *ToEdit;
    TLabel *BaseNameLabel;
    TEdit *BaseNameEdit;
    TLabel *DirLabel;
    TButton *DirButton;
    TEdit *DirEdit;
    TCheckBox *SeveralOrnCheckBox;
    void __fastcall OkButtonClick(TObject *Sender);
    void __fastcall HeightEditChange(TObject *Sender);
    void __fastcall WidthEditChange(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall CaptureCheckBoxClick(TObject *Sender);
    void __fastcall DirButtonClick(TObject *Sender);
private:	// User declarations
    bool Semapore;
    void __fastcall SetEnabled(bool bEn);
public:		// User declarations
     int OriginalHeight;
     int OriginalWidth;
     int SamHeight;
     int SamWidth;
     int SamQuality;
     bool PrintIndex;
     //захват видеоряда
     bool m_bCapture;
     int m_nFrom;
     int m_nStep;
     int m_nTo;
     bool m_bSeveralOrn;
     AnsiString m_strBaseName;
     AnsiString m_strDir;

    __fastcall TScreenCopyForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TScreenCopyForm *ScreenCopyForm;
//---------------------------------------------------------------------------
#endif
