//---------------------------------------------------------------------------


#pragma hdrstop

#include "Almas4ProbSetKeyUnit.h"
#include <math.h>
//---------------------------------------------------------------------------
#define INTERFACE_ID          "Almas4ProbSet"
#define INTERFACE_NAME        "�������-������������� (������ � �� ������)"
#define INTERFACE_DISCRIPTION "����������� ��� ������ ��� � �� ������ �������� � ������������� ����� ������ � ������ �������"
//---------------------------------------------------------------------------
//����� ������ � ���������
#define Adg1Base 1
//���������� ������ �������
#define Adg1State 4
//���������� ������ �������
#define Adg2Num 3
//���������� ��������� ������ �������
#define Adg2State 5
//��������� ������ ������� ���������� ��������� ������� ������
#define NoAdg2Val (Adg2State-1)
//������� ��������� ��� ������ j �������
#define Adg3State(i) IntPow(IntPow(Adg2State,Adg2Num), i)
//����
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
:TBaseProbSetKey()
{
	n1s = 0;
	n1v = 0;
	n2v = 0;
	n2s = 0;
	nns = 0;
}
//---------------------------------------------------------------------------
void __fastcall TAlmas4ProbSetKey::fill2(TProbKey nKey)
{
	int i,j;
	int nAdjTtpeI;
	bool bNoVol;

	n1s = 0;
	n1v = divGetAdg1(nKey)+1;//�� ��������� ������� ������ �������� ��������� (4-� ��������)
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
	  {//������� ������ ����
	   bNoVol = true;
	  }
	  else
	  {
	   if(nAdjTtpeI == 3)
	   {//������ ����� ��������
		n2v++;
	   }
	   else
	   {//������ ����� �������������
		n2s++;
	   }
	  }
	 }
	 if(bNoVol == true)
	 {//����� �� ������������� - ������ �� �������������
	  n1s++;//���� ������������� ���������
	  n1v--;//����� �������� ���������
	 }
	}

	for(i = divGetAdg1(nKey)+1; i < Adg1State; i++)
	{
	 for(j = 0; j < Adg2Num; j++)
	 {
	  nAdjTtpeI = divGetAdg2(nKey, i, j);
	  if(nAdjTtpeI == NoAdg2Val)
	  {//������� ������ ����
	   //bNoVol = true;
	  }
	  else
	  {//���� ������ ����� ��� ���������� ������� - �� ������ ������ �����
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
AnsiString __fastcall TAlmas4ProbSetKey::GetProbSetId()
{
	return AnsiString(INTERFACE_ID);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)

