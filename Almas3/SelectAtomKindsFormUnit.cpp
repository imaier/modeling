//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectAtomKindsFormUnit.h"
#include "GlobalUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TSelectAtomKindsForm *SelectAtomKindsForm;
//---------------------------------------------------------------------------
TAtomKindsOnAxes::TAtomKindsOnAxes()
{
	XAxis = eThreeLinkType;
	YAxis = eTwoLinkType;
}
//---------------------------------------------------------------------------
TAtomKindsOnAxes::TAtomKindsOnAxes(const TAtomKindsOnAxes &r)
{
	XAxis = r.XAxis;
	YAxis = r.YAxis;
}
//---------------------------------------------------------------------------
AnsiString TAtomKindsOnAxes::GetXAxisDiscription(void)
{
	return  GetAxisDiscription(XAxis);
}
//---------------------------------------------------------------------------
AnsiString TAtomKindsOnAxes::GetYAxisDiscription(void)
{
	return  GetAxisDiscription(YAxis);
}
//---------------------------------------------------------------------------
float TAtomKindsOnAxes::GetXAxisCount(const TStatisticsData &SD)
{
	return   GetCountForAxisType(XAxis, SD);
}
//---------------------------------------------------------------------------
float TAtomKindsOnAxes::GetYAxisCount(const TStatisticsData &SD)
{
	return   GetCountForAxisType(YAxis, SD);
}
//---------------------------------------------------------------------------
AnsiString TAtomKindsOnAxes::GetAxisDiscription(TContTypeOnAxis AxisType)
{
	AnsiString sRet = "Тип оси не определен";

	switch (AxisType) {
		case eOneLinkType:
			sRet = "Количество односвязных атомов";
		break;
		case eTwoLinkType:
			sRet = "Количество двухсвязных атомов";
		break;
		case eThreeLinkType:
			sRet = "Количество трехсвязных атомов";
		break;
		case eMostPopularType:
			sRet = "Количество атомов популярного типа";
		break;
		case eDeleted:
			sRet = "Количество удаленных атомов";
		break;
		case enSCount:
			sRet = "Количество непрямых вторых соседей";
		break;
		case edSCount:
			sRet = "Количество прямых вторых соседей";
		break;
		case endSCount:
			sRet = "Количество прямых и непрямых вторых соседей";
		break;
	}

	return sRet;
}
//---------------------------------------------------------------------------
float TAtomKindsOnAxes::GetCountForAxisType(TContTypeOnAxis AxisType, const TStatisticsData &SD)
{
	float fReurn = -1.0f;
	switch (AxisType) {
		case eOneLinkType:
			fReurn = SD.N1;
		break;
		case eTwoLinkType:
			fReurn = SD.N2;
		break;
		case eThreeLinkType:
			fReurn = SD.N3;
		break;
		case eMostPopularType:
			fReurn = SD.MostPopularTypeCount;
		break;
		case eDeleted:
			fReurn = SD.Deleted;
		break;
		case enSCount:
			fReurn = SD.nS_Count;
		break;
		case edSCount:
			fReurn = SD.dS_Count;
		break;
		case endSCount:
			fReurn = SD.nS_Count + SD.dS_Count;
		break;
	}
	return fReurn;
}
//---------------------------------------------------------------------------
__fastcall TSelectAtomKindsForm::TSelectAtomKindsForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSelectAtomKindsForm::FormShow(TObject *Sender)
{
	FillComboBox(XComboBox);
	FillComboBox(YComboBox);
	XComboBox->ItemIndex = (int)EditData.XAxis;
	YComboBox->ItemIndex = (int)EditData.YAxis;
}
//---------------------------------------------------------------------------
void __fastcall TSelectAtomKindsForm::OkButtonClick(TObject *Sender)
{
	if(YComboBox->ItemIndex < 0)
	{
	  AnsiString Text = "Выберите отображаемое количество на оси ординат";
	  Application->MessageBox(_WST(Text),_WST("Ошибка"),MB_OK | MB_ICONEXCLAMATION);
	  if(YComboBox->CanFocus())
	  {
		YComboBox->SetFocus();
	  }
	  return;
	}

	if(XComboBox->ItemIndex < 0)
	{
	  AnsiString Text = "Выберите отображаемое количество на оси абсцисс";
	  Application->MessageBox(_WST(Text),_WST("Ошибка"),MB_OK | MB_ICONEXCLAMATION);
	  if(XComboBox->CanFocus())
	  {
		XComboBox->SetFocus();
	  }
	  return;
	}

	if(XComboBox->ItemIndex == YComboBox->ItemIndex)
	{
	  AnsiString Text = "Выберите разные отображаемые количества на осях";
	  Application->MessageBox(_WST(Text),_WST("Ошибка"),MB_OK | MB_ICONEXCLAMATION);
	  if(XComboBox->CanFocus())
	  {
		XComboBox->SetFocus();
	  }
	  return;
	}

	EditData.XAxis =  (TContTypeOnAxis) XComboBox->ItemIndex;
	EditData.YAxis =  (TContTypeOnAxis) YComboBox->ItemIndex;

	ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void TSelectAtomKindsForm::FillComboBox(TComboBox *ComboBox)
{
	ComboBox->Clear();
	for (int i = 0; i < eContTypeOnAxisCount; i++)
	{
		AnsiString Discription = TAtomKindsOnAxes::GetAxisDiscription((TContTypeOnAxis)i);
		ComboBox->Items->Add(Discription);
	}
}
//---------------------------------------------------------------------------

