//---------------------------------------------------------------------------

#ifndef Almas7ProbSetKeyUnitH
#define Almas7ProbSetKeyUnitH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
//---------------------------------------------------------------------------
typedef UINT TProbKey;
typedef TProbKey TProbKey2;
typedef std::vector<TProbKey> TProbKeyVec;
//---------------------------------------------------------------------------
class TAlmas7ProbSetKey
{
public:
	TAlmas7ProbSetKey();

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

	//характеристика вероятности
	int F;  // F – общее число первых соседей
	int dS; // dS – число вторых прямых соседей
	int nS; // nS – число вторых непрямых соседей

	TProbKey2 Key2;
	TProbKey Key;

	AnsiString strName;

	void __fastcall fill(TProbKey nKey);
	void __fastcall fill2(TProbKey nKey);//посчитать только характеристику вероятности

	TProbKey __fastcall unfill();

	int __fastcall GetAdjType(int i);
	int __fastcall GetAdj2Type(int i,int j);
	void __fastcall GetProbNameFromKey2(AnsiString &_strName);
};
//---------------------------------------------------------------------------
#endif
