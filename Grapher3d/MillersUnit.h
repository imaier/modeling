//---------------------------------------------------------------------------

#ifndef MillersUnitH
#define MillersUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMillersIndexes
{
public:
    TMillersIndexes();
    TMillersIndexes(TMillersIndexes& r);
    TMillersIndexes& operator = (const TMillersIndexes& r);

    double h,k,l;

    TMillersIndexes Perpend();
    double Angle(TMillersIndexes& SecondIndex);
};
//---------------------------------------------------------------------------
class TMillersForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *ButtonsPanel;
    TPanel *OkPanel;
    TButton *OkButton;
    TPanel *CancelPanel;
    TButton *CancelButton;
    TGroupBox *GroupBox1;
    TEdit *DirectIndexHEdit;
    TLabel *DirectIndexHLabel;
    TEdit *DirectIndexKEdit;
    TLabel *DirectIndexKLabel;
    TEdit *DirectIndexLEdit;
    TLabel *DirectIndexLLabel;
    TGroupBox *GroupBox2;
    TLabel *PerpIndexHLabel;
    TLabel *PerpIndexKLabel;
    TLabel *PerpIndexLLabel;
    TEdit *PerpIndexHEdit;
    TEdit *PerpIndexKEdit;
    TEdit *PerpIndexLEdit;
    TGroupBox *GroupBox3;
    TLabel *AngleIndexHLabel;
    TLabel *AngleIndexKLabel;
    TLabel *AngleIndexLLabel;
    TEdit *AngleIndexHEdit;
    TEdit *AngleIndexKEdit;
    TEdit *AngleIndexLEdit;
    TLabel *AngleLabel;
    TLabel *AngleValueLabel;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall DirectIndexHEditChange(TObject *Sender);
    void __fastcall OkButtonClick(TObject *Sender);
private:	// User declarations
    bool m_bCalcs;//вычислять индексы
    bool CalcIndex(void);
public:		// User declarations
    TMillersIndexes MI;
    bool m_bShowExeption;
    __fastcall TMillersForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMillersForm *MillersForm;
//---------------------------------------------------------------------------
#endif
