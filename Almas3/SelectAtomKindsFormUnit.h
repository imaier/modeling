//---------------------------------------------------------------------------

#ifndef SelectAtomKindsFormUnitH
#define SelectAtomKindsFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "Dissolution.h"
//---------------------------------------------------------------------------
enum TContTypeOnAxis
{
	eOneLinkType = 0,
	eTwoLinkType,
	eThreeLinkType,
	eMostPopularType,
	eDeleted,           //количество удаленных атомов
	eSCount,            //количество непрямых соседей
	eContTypeOnAxisCount
};
//---------------------------------------------------------------------------
class TAtomKindsOnAxes
{
public:
	TAtomKindsOnAxes();
	TAtomKindsOnAxes(const TAtomKindsOnAxes &r);

	AnsiString GetXAxisDiscription(void);
	AnsiString GetYAxisDiscription(void);

	float GetXAxisCount(const TStatisticsData &SD);
	float GetYAxisCount(const TStatisticsData &SD);

	TContTypeOnAxis XAxis;
	TContTypeOnAxis YAxis;

	static AnsiString GetAxisDiscription(TContTypeOnAxis AxisType);
	static float GetCountForAxisType(TContTypeOnAxis AxisType, const TStatisticsData &SD);
};
//---------------------------------------------------------------------------
class TSelectAtomKindsForm : public TForm
{
__published:	// IDE-managed Components
	TComboBox *YComboBox;
	TComboBox *XComboBox;
	TPanel *ButtonsPanel;
	TPanel *OkPanel;
	TButton *OkButton;
	TPanel *CancelPanel;
	TButton *CancelButton;
	TLabel *YLabel;
	TLabel *XLabel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall OkButtonClick(TObject *Sender);
private:	// User declarations
	void FillComboBox(TComboBox *ComboBox);
public:		// User declarations
	TAtomKindsOnAxes EditData;
	__fastcall TSelectAtomKindsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectAtomKindsForm *SelectAtomKindsForm;
//---------------------------------------------------------------------------
#endif
