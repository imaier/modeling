//---------------------------------------------------------------------------

#ifndef Almas3ProbSetKeyUnitH
#define Almas3ProbSetKeyUnitH
//---------------------------------------------------------------------------
#include "BaseProbSetUnit.h"
//---------------------------------------------------------------------------
class TAlmas3ProbSetKey : public TBaseProbSetKey
{
public:
	TAlmas3ProbSetKey();

	int n1s;
	int n1v;
	int n2s;
	int n2v;

	virtual void __fastcall fill(TProbKey nKey);
	void __fastcall fill2(TProbKey nKey);//только n1 n2 посчитать
	void __fastcall GetProbNameFromKey2(AnsiString &_strName);

	virtual AnsiString __fastcall GetProbSetId();

	virtual int __fastcall GetAdjType(int i);
	virtual int __fastcall GetAdj2Type(int i,int j);
};
//---------------------------------------------------------------------------
#endif
