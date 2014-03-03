//---------------------------------------------------------------------------

#ifndef ProbSetModelUnitH
#define ProbSetModelUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "ProbPoviderUnit.h"
//---------------------------------------------------------------------------
class TProbSetModelForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *ButtonsPanel;
    TPanel *OkPanel;
    TButton *OkButton;
    TPanel *CancelPanel;
    TButton *CancelButton;
    TPanel *ClientPanel;
    TRadioGroup *SufModelRadioGroup;
    TSplitter *Splitter1;
    TPanel *InfoPanel;
    TLabel *InfoLabel;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall SufModelRadioGroupClick(TObject *Sender);
    void __fastcall OkButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    TProbPovider EditProb;//провайдер вероятностей (редактируемый)
    TProbPovider *RetProb;//провайдер вероятностей (возращаемый)
    void InitForm(TProbPovider &SP);
    __fastcall TProbSetModelForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
