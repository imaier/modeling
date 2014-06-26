//---------------------------------------------------------------------------

#ifndef BaseProbSetUnitH
#define BaseProbSetUnitH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
//---------------------------------------------------------------------------
typedef UINT TProbKey;
typedef TProbKey TProbKey2;
typedef std::vector<TProbKey> TProbKeyVec;
//---------------------------------------------------------------------------
int __fastcall IntPow(int x, int p);
TProbKey Adg2Base_5(int i, int j);
//---------------------------------------------------------------------------
class TBaseProbSetKey
{
public:
	TBaseProbSetKey();

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

	TProbKey2 Key2;
	TProbKey Key;

	AnsiString strName;

	virtual void __fastcall fill(TProbKey nKey);
	virtual void __fastcall fill2(TProbKey nKey) = 0;
	virtual void __fastcall GetProbNameFromKey2(AnsiString &_strName) = 0;

	virtual AnsiString __fastcall GetProbSetId() = 0;

	virtual TProbKey __fastcall unfill();

	virtual int __fastcall GetAdjType(int i);
	virtual int __fastcall GetAdj2Type(int i,int j);
};
//---------------------------------------------------------------------------
#endif
