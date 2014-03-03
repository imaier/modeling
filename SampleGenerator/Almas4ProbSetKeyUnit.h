//---------------------------------------------------------------------------

#ifndef Almas4ProbSetKeyUnitH
#define Almas4ProbSetKeyUnitH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
//---------------------------------------------------------------------------
typedef UINT TProbKey;
typedef TProbKey TProbKey2;
typedef std::vector<TProbKey> TProbKeyVec;
//---------------------------------------------------------------------------
class TAlmas4ProbSetKey
{
public:
	TAlmas4ProbSetKey();

	int Adg1;
	int Adg2_i0_j0;
	int Adg2_i0_j1;
	int Adg2_i0_j2;
	int Adg2_i1_j0;
	int Adg2_i1_j1;
	int Adg2_i1_j2;
	int Adg2_i2_j0;
	int Adg2_i2_j1;
	int Adg2_i2_j2;
	int Adg2_i3_j0;
	int Adg2_i3_j1;
	int Adg2_i3_j2;

	int n1s;
	int n1v;
	int n2s;
	int n2v;
	int nns;

	TProbKey2 Key2;
	TProbKey Key;

	AnsiString strName;

	void __fastcall fill(TProbKey nKey);
	void __fastcall fill2(TProbKey nKey);//только n1 n2 посчитать
	void __fastcall GetProbNameFromKey2(AnsiString &_strName);

	int __fastcall GetAdjType(int i);
	int __fastcall GetAdj2Type(int i,int j);



	TProbKey __fastcall unfill();
};
//---------------------------------------------------------------------------
#endif
