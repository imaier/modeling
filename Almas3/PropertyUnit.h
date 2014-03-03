//---------------------------------------------------------------------------
#ifndef PropertyUnitH
#define PropertyUnitH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
#include "MaskUnit.h"
#include "ProbalityUnit.h"
#include "QuantityByGroupeUnit.h"
//---------------------------------------------------------------------------
class TExperimentProperty
{
public:
    int W,H;//размер образца

    TProbPovider SP;

    TMaskVec m_vMask;
    //int CountMask;//маска
    //TMask* MasksArray;

    int DelAtoms;//удалЄнных атомов
    int DeletedLayers;//растворившихс€ слоЄв
    int DeletingLayers;//раствор€ющихс€ слоЄв
    int N1,N2,N3;//число одно- дву- трЄхсв€зных атомов
    int* Layers;//число атомов в расствор€ющихс€ сло€х
    TDateTime BeginTime;//дата и врем€ начала опыта
    TDateTime DissolutionTime;//длительность опыта
    TDateTime EndTime;//дата и врем€ после удалени€ DelAtoms атомов
    double AverageSpeed;//средн€€ скорость процесса

	AnsiString Description;//ќписание ќпыта
    AnsiString FileName;//им€ файла

    TAtomCntInLayerVector m_vAtomCntInLayer; //атомы по сло€м

    TExperimentProperty();
};
//---------------------------------------------------------------------------
class TPropertyForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *ButtonsPanel;
	TPanel *SavePanel;
	TButton *SaveButton;
	TPanel *CancelPanel;
	TButton *CancelButton;
	TPanel *DataPanel;
	TPanel *DescriptionGroupBoxPanel;
	TGroupBox *DescriptionGroupBox;
	TPanel *DescriptionPanel;
	TMemo *DescriptionMemo;
	TPanel *SourceDataGroupBoxPanel;
	TGroupBox *SourceDataGroupBox;
	TPanel *ResultDataGroupBoxPanel;
	TGroupBox *ResultDataGroupBox;
	TGroupBox *SizeGroupBox;
	TGroupBox *ProbabilityGroupBox;
	TGroupBox *MaskGroupBox;
	TListBox *MaskListBox;
	TLabel *XTextLabel;
	TLabel *YTextLabel;
	TLabel *XNumLabel;
	TLabel *YNumLabel;
	TLabel *N1ProbabilityTextLabel;
	TLabel *N2ProbabilityTextLabel;
	TLabel *N3ProbabilityTextLabel;
	TLabel *N1ProbabilityNumLabel;
	TLabel *N2ProbabilityNumLabel;
	TLabel *N3ProbabilityNumLabel;
	TLabel *DelAtomsTextLabel;
	TLabel *DeletedLayersTextLabel;
	TLabel *DeletingLayersTextLabel;
	TLabel *N1NumLabel;
	TLabel *N1TextLabel;
	TLabel *N2TextLabel;
	TLabel *N2NumLabel;
	TLabel *N3TextLabel;
	TLabel *N3NumLabel;
	TListBox *NumOfAtomsInLayerListBox;
	TLabel *StartTimeTextLabel;
	TLabel *StartTimeNumLabel;
	TLabel *DissolutionTimeTextLabel;
	TLabel *DissolutionTimeNumLabel;
	TLabel *AverageSpeedTextLabel;
	TLabel *AverageSpeedNumLabel;
	TLabel *DelAtomsNumLabel;
	TLabel *DeletedLayersNumLabel;
	TLabel *DeletingLayersNumLabel;
	TPanel *ClientPanel;
	TPanel *MaskPanel;
	TPanel *PaintPanel;
	TPaintBox *MaskPaintBox;

	TPanel *OkPanel;
	TButton *OkButton;
	void __fastcall MaskPaintBoxPaint(TObject *Sender);
	void __fastcall MaskPanelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SaveButtonClick(TObject *Sender);
private:	// User declarations
    //Graphics::TBitmap *Bmp;
public:		// User declarations
	TExperimentProperty *ExpProperty;
    void InitPropertyForm(TExperimentProperty *ExpProp);
	__fastcall TPropertyForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TPropertyForm *PropertyForm;
//---------------------------------------------------------------------------
#endif
