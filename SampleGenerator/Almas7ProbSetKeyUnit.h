//---------------------------------------------------------------------------

#ifndef Almas7ProbSetKeyUnitH
#define Almas7ProbSetKeyUnitH
//---------------------------------------------------------------------------
#include "BaseProbSetUnit.h"
//---------------------------------------------------------------------------
class TAlmas7ProbSetKey : public TBaseProbSetKey
{
public:
	TAlmas7ProbSetKey();

	//�������������� �����������
	int F;  // F � ����� ����� ������ �������
	int dS; // dS � ����� ������ ������ �������
	int nS; // nS � ����� ������ �������� �������

	void __fastcall fill2(TProbKey nKey);//��������� ������ �������������� �����������

	void __fastcall GetProbNameFromKey2(AnsiString &_strName);

	virtual AnsiString __fastcall GetProbSetId();

};
//---------------------------------------------------------------------------
#endif
