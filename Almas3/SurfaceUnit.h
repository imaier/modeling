//---------------------------------------------------------------------------
#ifndef SurfaceUnitH
#define SurfaceUnitH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "ProbalityUnit.h"
#include "DefectUnit.h"
#include "PictUnit.h"
#include "MaskEditUnit.h"
//---------------------------------------------------------------------------
//алгоритмы расстворени€
#define ALG_MONTECARLO 1
#define ALG_POROGOVIY  2
#define ALG_POROG_DOLA 3
#define ALG_DOLA_PROB  4
//---------------------------------------------------------------------------
//поведение неудал€емых атомов
//обычное
#define BHV_USUALLY 	   1
//недал€емый атом ведет себ€ как четырехсв€зный атом
#define BHV_AS_FOUR_LINKS  2
//---------------------------------------------------------------------------
class TAlgoritm //алгорим расстворени€ и параметры алгоритма
{
public:
	TAlgoritm();
	TAlgoritm(const TAlgoritm &r);
	TAlgoritm& operator = (const TAlgoritm &r);

	void Init();

	int m_nAlgoritmKind;//алгоритм растворени€: 1- ћонтекарло 2 - пороговый 3 - ѕороговый дольный 4 - ƒольный, наиболее веро€тных атомов
	double m_dPorog;//порог веро€тности
	double m_dDola;//дол€ количества

	//поведение неудал€емых атомов
	int m_nNoDelAtomsBehaviour;//неудал€емые атомы ведут себ€ как  1 - обычные атомы  2- четырехсва€зные атомы
	bool m_bInitRNG;//инициализировать гсч

	bool SaveToFile(HANDLE hFile, int *pSeek = NULL);//сохранить структуру в поток
	bool LoadFromFile(HANDLE hFile, int *pSeek = NULL);//загрузить структуру из потока
};
//---------------------------------------------------------------------------
class TDissolutionParametries
{
public:
	//размеры
	unsigned int X;
	unsigned int Y;
	unsigned int Z;
	//набор веро€тностей
	TProbPovider SP;
	//алгоритм расстворени€
	TAlgoritm m_Algoritm;
	//удал€емые атомы
	unsigned int Plane;
	//маска
	bool Masked;
	TMaskVec m_vMask;//вектор масок

	//дефекты поверхности
	TDefectVec m_vDefect;//вектор дефектов

	TDissolutionParametries();
	TDissolutionParametries(const TDissolutionParametries &r);
	void Init();
};
//---------------------------------------------------------------------------
enum TInitForm{ifCube, ifNew , ifContinue};
//---------------------------------------------------------------------------
class TSurfaceForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *PlanGroupBox;
	TEdit *PlanEdit;
	TLabel *PlanLabel;
	TLabel *XLabel;
	TLabel *YLabel;
	TLabel *ZLabel;
	TEdit *XEdit;
	TEdit *YEdit;
	TEdit *ZEdit;
	TGroupBox *ProbabilityGroupBox;
	TPanel *ButtonsPanel;
	TPanel *OkPanel;
	TButton *OkButton;
	TPanel *CancelPanel;
	TButton *CancelButton;
	TGroupBox *SizeGroupBox;

	TGroupBox *MaskGroupBox;
	TRadioButton *NoMaskRadioButton;
	TRadioButton *MaskedRadioButton;
	TSpeedButton *PictSpeedButton;
	TPanel *Panel1;
	TButton *StartButton;
    TBitBtn *ProbalityBitBtn;
    TSpeedButton *SaveSpeedButton;
    TSpeedButton *LoadSpeedButton;
    TOpenDialog *MaskOpenDialog;
    TGroupBox *AlgParamGroupBox;
    TLabel *PorogLabel;
    TLabel *DolaLabel;
    TLabel *PorogNeedLabel;
    TLabel *DolaNeedLabel;
    TEdit *PorogEdit;
    TEdit *DolaEdit;
    TRadioButton *AlgMontecarloRadioButton;
    TRadioButton *AlgPorogRadioButton;
    TRadioButton *PorogDolaRadioButton;
    TRadioButton *DolaProbRadioButton;
	TGroupBox *NoDelAtomsBehaviourGroupBox;
	TSaveDialog *MaskSaveDialog;
	TRadioButton *BehaviourUsuallyRadioButton;
	TRadioButton *BehaviourAsFourLinksRadioButton;
	TCheckBox *InitRNGCheckBox;
	TBitBtn *DefectEditBitBtn;
	TLabel *DefectLabel;
	TBitBtn *MaskEditBitBtn;
	void __fastcall OkButtonClick(TObject *Sender);
	void __fastcall MaskedRadioButtonClick(TObject *Sender);
	void __fastcall NoMaskRadioButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall PictSpeedButtonClick(TObject *Sender);
    void __fastcall PlanEditKeyPress(TObject *Sender, char &Key);
    void __fastcall ProbalityBitBtnClick(TObject *Sender);
    void __fastcall LoadSpeedButtonClick(TObject *Sender);
    void __fastcall SaveSpeedButtonClick(TObject *Sender);
    void __fastcall AlgMontecarloRadioButtonClick(TObject *Sender);
	void __fastcall DefectEditBitBtnClick(TObject *Sender);
	void __fastcall MaskEditBitBtnClick(TObject *Sender);
private:	// User declarations
	void __fastcall SetControlButton(void);

	int GetAlgDiss(void);
	void SetOptParam(int nAlgoritmKind);
	void SetAlgDiss(int nAlgoritmKind);


	void SetNoDelAtomsBehaviour(int nKind);
	int  GetNoDelAtomsBehaviour(void);

	TDissolutionParametries EditParams;
	TDissolutionParametries *RetParams;

	TPictuteForm *m_pPictForm;
	TMaskEditForm *m_pMaskEditForm;

public:		// User declarations
	bool MaskChanged;
	void __fastcall InitForm(TInitForm InitForm, TDissolutionParametries &DP);
	__fastcall TSurfaceForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TSurfaceForm *SurfaceForm;
//---------------------------------------------------------------------------
#endif
