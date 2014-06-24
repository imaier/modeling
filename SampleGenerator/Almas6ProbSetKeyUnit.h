//---------------------------------------------------------------------------

#ifndef Almas6ProbSetKeyUnitH
#define Almas6ProbSetKeyUnitH
//---------------------------------------------------------------------------
#include "BaseProbSetUnit.h"
//---------------------------------------------------------------------------
class TAlmas6ProbSetKey : public TBaseProbSetKey
{
public:
	TAlmas6ProbSetKey();

	int n1s;
	int n1v;
	int n2s;
	int n2v;
	int nns;

	void __fastcall fill2(TProbKey nKey);//только n1 n2 посчитать
	void __fastcall GetProbNameFromKey2(AnsiString &_strName);

	virtual AnsiString __fastcall GetProbSetId();
};
#endif
