//---------------------------------------------------------------------------
#ifndef MaskUnitH
#define MaskUnitH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
//Type {tpRectangle,tpCircle};
//---------------------------------------------------------------------------
enum TKindFig {kfRectangle,kfCircle};
enum TLogicFunction {lfAND,lfOR,lfXOR};
enum TTypeSuperimproseMask {tsmmBoolean,tsmmImmediately};
enum TInsideFig {ifDeletedAtoms,ifNoDeletedAtoms};
//---------------------------------------------------------------------------
extern const double Mtr[3][3];
extern const double Mtr2[3][3];
extern const int NumSemplsX;//Число семплов вдоль оси X
extern const int NumSemplsY;//Число семплов вдоль оси Y
//---------------------------------------------------------------------------
class TMask
{
private:
    bool __fastcall IsIncludePointRectangle(double x, double y, double z);
    bool __fastcall IsIncludePointCircle(double x, double y, double z);
	bool __fastcall OnOutNorm(double x, double y,double X0,double Y0,double X1,double Y1);
public:
	TKindFig KindFig;
    float X,Y;
    float H,W;
    float Angle;
    float R;

    bool Not;
	TLogicFunction LogicFunction;
    TTypeSuperimproseMask TypeSuperimproseMask;
    TInsideFig InsideFig;

    AnsiString __fastcall TMaskToString();
    bool __fastcall IsIncludePoint(double x, double y, double z);
    void __fastcall CopyMask(const TMask &Mask);
	TMask();
	TMask(const TMask &Mask);
	bool operator==(const TMask &Mask) const;
	//bool operator<(const TMask &Mask);

    bool SaveToFile(HANDLE hFile, int *pSeek);
    bool LoadFromFile(HANDLE hFile, int *pSeek);
};
//---------------------------------------------------------------------------
class TMaskVec: public std::vector<TMask>
{
public:
    bool SaveToFile(HANDLE hFile, int *pSeek);
    bool LoadFromFile(HANDLE hFile, int *pSeek);
};
//---------------------------------------------------------------------------
class TMaskForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *ButtonsPanel;
	TPanel *OkPanel;
	TButton *OkButton;
	TPanel *CancelPanel;
	TButton *CancelButton;
	TGroupBox *KindFigMaskGroup;
	TGroupBox *CircleGroupBox;
	TGroupBox *RectangleGroupBox;
	TLabel *RectangleXLabel;
	TLabel *RectangleYLabel;
	TLabel *RectangleAngleLabel;
	TEdit *RectangleXEdit;
	TEdit *RectangleYEdit;
	TEdit *RectangleAngleEdit;
	TRadioButton *RectangleRadioButton;
	TRadioButton *CircleRadioButton;
	TEdit *RectangleHEdit;
	TEdit *RectangleWEdit;
	TLabel *RectangleWLabel;
	TLabel *RectangleHLabel;
	TLabel *CircleXLabel;
	TLabel *CircleYLabel;
	TEdit *CircleYEdit;
	TEdit *CircleXEdit;
	TLabel *CircleRLabel;
	TEdit *CircleREdit;
	TGroupBox *SuperimproseGroupBox;
	TCheckBox *NOTCheckBox;
	TComboBox *LogicComboBox;
	TLabel *LogicLabel;
	TRadioButton *BoolRadioButton;
	TRadioButton *ImmediatelyRadioButton;
	TPanel *ImmediatelyPanel;
	TRadioButton *DelRadioButton;
	TRadioButton *NoDelRadioButton;
	void __fastcall RectangleRadioButtonClick(TObject *Sender);
	void __fastcall CircleRadioButtonClick(TObject *Sender);
	void __fastcall OkButtonClick(TObject *Sender);

	void __fastcall BoolRadioButtonClick(TObject *Sender);
	void __fastcall ImmediatelyRadioButtonClick(TObject *Sender);
private:	// User declarations
	void __fastcall SetKindFig(bool IfRectangle);
    void __fastcall SetTypeSuperimproseMask(TTypeSuperimproseMask TSM);
public:		// User declarations
	TMask Mask;
    void __fastcall InitForm(TMask &MaskInit);
	__fastcall TMaskForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TMask *DefaultMask;
extern TMaskForm *MaskForm;
//---------------------------------------------------------------------------
#endif
