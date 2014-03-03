//---------------------------------------------------------------------------


#pragma hdrstop

#include "Almas4ProbSetKeyUnit.h"
#include <math.h>

//---------------------------------------------------------------------------
//новый способ с делениями
#define Adg1Base 1
//количество первых соседей
#define Adg1State 4
//количество вторых соседей
#define Adg2Num 3
//количество состояний вторых соседей
#define Adg2State 5
//состояние вторых соседей означающее отсутсвие второго соседа
#define NoAdg2Val (Adg2State-1)
//емкость состояний для первых j соседей
#define Adg3State(i) IntPow(IntPow(Adg2State,Adg2Num), i)
//база
#define Adg2Base_(i, j) (Adg1State*Adg3State(i)*IntPow(Adg2State,j))
#define Adg2Base(i, j) Adg2Base_4(i, j)

#define divGetAdg1(Key) (Key%Adg1State)
#define divSetAdg1(Key, Data) Key = (Key + ((Data%Adg1State) - divGetAdg1(Key))*Adg1Base)
#define divGetAdg2(Key, i, j) ((Key/Adg2Base(i,j))%Adg2State)
#define divSetAdg2(Key, Data, i, j) Key = (Key + ((Data%Adg2State) - divGetAdg2(Key,i,j))*Adg2Base(i,j))

#define SetKey2(Key, n1s, n1v, n2s, n2v, nns)   Key = (nns%10 + 10*(n2v%10) + 100*(n2s%10) + 1000*(n1v%10) + 10000*(n1s%10))
#define GetKey2(Key, n1s, n1v, n2s, n2v, nns)  nns = ((Key/1)%10); n2v = ((Key/10)%10); n2s = ((Key/100)%10); n1v = ((Key/1000)%10); n1s = ((Key/10000)%10);
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int __fastcall IntPow(int x, int p)
{
	int y=1;
	for(int i = 0; i < p; i++)
	{
	 y*=x;
	}
	return y;
}
//---------------------------------------------------------------------------
TProbKey Adg2Base_4(int i, int j)
{
static TProbKey cvAdg2Base[4][3] = { {Adg2Base_(0,0),Adg2Base_(0,1),Adg2Base_(0,2)},
									 {Adg2Base_(1,0),Adg2Base_(1,1),Adg2Base_(1,2)},
									 {Adg2Base_(2,0),Adg2Base_(2,1),Adg2Base_(2,2)},
									 {Adg2Base_(3,0),Adg2Base_(3,1),Adg2Base_(3,2)}
								   };
	return cvAdg2Base[i][j];
}
//---------------------------------------------------------------------------

TAlmas4ProbSetKey::TAlmas4ProbSetKey()
{
	Adg1 = 0;
	Adg2_i0_j0 = 0;
	Adg2_i1_j0 = 0;
	Adg2_i2_j0 = 0;
	Adg2_i3_j0 = 0;
	Adg2_i0_j1 = 0;
	Adg2_i1_j1 = 0;
	Adg2_i2_j1 = 0;
	Adg2_i3_j1 = 0;
	Adg2_i0_j2 = 0;
	Adg2_i1_j2 = 0;
	Adg2_i2_j2 = 0;
	Adg2_i3_j2 = 0;

	n1s = 0;
	n1v = 0;
	n2v = 0;
	n2s = 0;
	nns = 0;

	Key2 = 0;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas4ProbSetKey::fill(TProbKey nKey)
{
	Key = nKey;

	Adg1 = divGetAdg1(nKey);
	Adg2_i0_j0 = divGetAdg2(nKey, 0, 0);
	//Adg2_i1_j0 = Adg2Base(1,0);
	Adg2_i1_j0 = divGetAdg2(nKey, 1, 0);
	Adg2_i2_j0 = divGetAdg2(nKey, 2, 0);
	Adg2_i3_j0 = divGetAdg2(nKey, 3, 0);
	Adg2_i0_j1 = divGetAdg2(nKey, 0, 1);
	Adg2_i1_j1 = divGetAdg2(nKey, 1, 1);
	Adg2_i2_j1 = divGetAdg2(nKey, 2, 1);
	Adg2_i3_j1 = divGetAdg2(nKey, 3, 1);
	Adg2_i0_j2 = divGetAdg2(nKey, 0, 2);
	Adg2_i1_j2 = divGetAdg2(nKey, 1, 2);
	Adg2_i2_j2 = divGetAdg2(nKey, 2, 2);
	Adg2_i3_j2 = divGetAdg2(nKey, 3, 2);

	fill2(nKey);

	GetProbNameFromKey2(strName);
}
//---------------------------------------------------------------------------
TProbKey __fastcall TAlmas4ProbSetKey::unfill()
{
	TProbKey nKey = 0;

	//int ii = Adg3State(0);

	divSetAdg1(nKey,Adg1);
	divSetAdg2(nKey, Adg2_i0_j0, 0, 0);
	divSetAdg2(nKey, Adg2_i0_j1, 0, 1);
	divSetAdg2(nKey, Adg2_i0_j2, 0, 2);
	divSetAdg2(nKey, Adg2_i1_j0, 1, 0);
	divSetAdg2(nKey, Adg2_i1_j1, 1, 1);
	divSetAdg2(nKey, Adg2_i1_j2, 1, 2);
	divSetAdg2(nKey, Adg2_i2_j0, 2, 0);
	divSetAdg2(nKey, Adg2_i2_j1, 2, 1);
	divSetAdg2(nKey, Adg2_i2_j2, 2, 2);
	divSetAdg2(nKey, Adg2_i3_j0, 3, 0);
	divSetAdg2(nKey, Adg2_i3_j1, 3, 1);
	divSetAdg2(nKey, Adg2_i3_j2, 3, 2);

	Key = nKey;

	TAlmas4ProbSetKey k1;
	k1.fill(Key);


	TProbKey nKey30 = 0;
	TProbKey nKey31 = 0;
	TProbKey nKey32 = 0;

	divSetAdg2(nKey30, Adg2_i3_j0, 3, 0);
	divSetAdg2(nKey31, Adg2_i3_j1, 3, 1);
	divSetAdg2(nKey32, Adg2_i3_j2, 3, 2);

	return nKey;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas4ProbSetKey::fill2(TProbKey nKey)
{
	int i,j;
	int nAdjTtpeI;
	bool bNoVol;

	n1s = 0;
	n1v = divGetAdg1(nKey)+1;//по умолчанию считаем первых сосоедей объемными (4-х связными)
	n2v = 0;
	n2s = 0;
	nns = 0;

	for(i = 0; i < (signed)divGetAdg1(nKey)+1; i++)
	{
	 bNoVol = false;
	 for(j = 0; j < Adg2Num; j++)
	 {
	  nAdjTtpeI = divGetAdg2(nKey, i, j);
	  if(nAdjTtpeI == NoAdg2Val)
	  {//второго соседа нету
	   bNoVol = true;
	  }
	  else
	  {
	   if(nAdjTtpeI == 3)
	   {//второй сосед объемный
		n2v++;
	   }
	   else
	   {//второй сосед поверхностный
		n2s++;
	   }
	  }
	 }
	 if(bNoVol == true)
	 {//сосед не четырёхсвязный - значит он поверхностный
	  n1s++;//чило поверхностных увеличить
	  n1v--;//число объемных уменьшить
	 }
	}

	for(i = divGetAdg1(nKey)+1; i < Adg1State; i++)
	{
	 for(j = 0; j < Adg2Num; j++)
	 {
	  nAdjTtpeI = divGetAdg2(nKey, i, j);
	  if(nAdjTtpeI == NoAdg2Val)
	  {//второго соседа нету
	   //bNoVol = true;
	  }
	  else
	  {//есть второй сосед без присутсвия первого - не прямой второй сосед
	   nns++;
	  }
	 }
	}

	SetKey2(Key2, n1s, n1v, n2s, n2v, nns);
}
//---------------------------------------------------------------------------
void __fastcall TAlmas4ProbSetKey::GetProbNameFromKey2(AnsiString &_strName)
{
	_strName.sprintf("%05d (s%d, v%d; s%d, v%d, ns%d)x%d - %d", Key2, n1s, n1v, n2s, n2v, nns, Adg1+1, Key);
}
//---------------------------------------------------------------------------
int __fastcall TAlmas4ProbSetKey::GetAdjType(int i)
{
	int j;
	int Type = 0;
	int Adg2;

	if(Adg1 >= i)
	{
	 Type++;
	 for(j = 0; j < Adg2Num; j++)
	 {
	  Adg2 = divGetAdg2(Key, i, j);
	  if(Adg2 != (Adg2State-1))
	  {
	   Type++;
	  }
	 }
	}

	return Type;
}
//---------------------------------------------------------------------------
int __fastcall TAlmas4ProbSetKey::GetAdj2Type(int i,int j)
{
	int Type = 0;
	int Adg2;
	Adg2 = divGetAdg2(Key, i, j);
	if(Adg2 != (Adg2State-1))
	{
	 Type = Adg2+1;
	}
	return Type;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)

