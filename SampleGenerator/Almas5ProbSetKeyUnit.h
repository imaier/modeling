//---------------------------------------------------------------------------

#ifndef Almas5ProbSetKeyUnitH
#define Almas5ProbSetKeyUnitH
//---------------------------------------------------------------------------
#include "BaseProbSetUnit.h"
//---------------------------------------------------------------------------
class TAlmas5ProbSetKey : public TBaseProbSetKey
{
public:
	TAlmas5ProbSetKey();

	int n1s;
	int n1v;
	int n2s;
	int n2v;
	int nns;

	void __fastcall fill2(TProbKey nKey);//только n1 n2 посчитать

	void __fastcall GetProbNameFromKey2(AnsiString &_strName);

	virtual AnsiString __fastcall GetProbSetId();
};
//---------------------------------------------------------------------------
#endif
