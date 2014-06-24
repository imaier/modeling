//---------------------------------------------------------------------------

#ifndef MaimUnitH
#define MaimUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "Almas4ProbSetKeyUnit.h"
#include "Almas5ProbSetKeyUnit.h"
#include "Almas6ProbSetKeyUnit.h"
#include "Almas7ProbSetKeyUnit.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TAtomCrd
{
public:
    TAtomCrd();
    int x,y,z;//кординаты
    int nV;//связность

    TAtomCrd GetAdj(int i);//получить координаты итого соседа
    int GetColor();//
    int GetLinkColor(TAtomCrd b);//
};
//---------------------------------------------------------------------------
class TMaimForm : public TForm
{
__published:	// IDE-managed Components
    TButton *GenerateButton;
    TButton *StopButton;
    TProgressBar *StatusProgressBar;
    TLabel *StatusLabel;
    TCheckBox *SplitCheckBox;
    TCheckBox *CubeCheckBox;
	TRadioGroup *ProbSetRadioGroup;
    void __fastcall StopButtonClick(TObject *Sender);
	void __fastcall GenerateButtonClick(TObject *Sender);
private:	// User declarations
    void __fastcall GenFile(int nPosition, bool bSplit, bool bCube);
	AnsiString __fastcall GenFileName(int nPosition);
	void __fastcall GenerateAlmas2(void);
	void __fastcall GenerateProbSet3thGeneratiom(void);

	void __fastcall GenFile(TBaseProbSetKey *ProbSet, bool bSplit, bool bCube, AnsiString &strFileName);

	AnsiString __fastcall GenerateCube(void);

	bool m_bStop;
public:		// User declarations
	__fastcall TMaimForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMaimForm *MaimForm;
//---------------------------------------------------------------------------
#endif
