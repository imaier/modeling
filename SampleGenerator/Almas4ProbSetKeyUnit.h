//---------------------------------------------------------------------------

#ifndef Almas4ProbSetKeyUnitH
#define Almas4ProbSetKeyUnitH
//---------------------------------------------------------------------------
#include "BaseProbSetUnit.h"
//---------------------------------------------------------------------------
class TAlmas4ProbSetKey : public TBaseProbSetKey
{
public:
	TAlmas4ProbSetKey();

	int n1s;
	int n1v;
	int n2s;
	int n2v;
	int nns;

	void __fastcall fill2(TProbKey nKey);//������ n1 n2 ���������
	void __fastcall GetProbNameFromKey2(AnsiString &_strName);

	virtual AnsiString __fastcall GetProbSetId();
};
//---------------------------------------------------------------------------
#endif
