//---------------------------------------------------------------------------

#ifndef Almas5ProbSetUnitH
#define Almas5ProbSetUnitH
///---------------------------------------------------------------------------
#include "BaseProbSetUnit.h"
#include "ProbPoviderUnit.h"
#include <map>
//---------------------------------------------------------------------------
typedef UINT TProbKey;
typedef TProbKey TProbKey2;
typedef std::map<TProbKey, TProbIndex> TProbKeyMap;
typedef std::map<TProbKey2, TProbKey> TKey2ToKeyMap;
typedef std::vector<TProbKey> TProbKeyVec;

/*
 * ����� ���������� ������ ��� ������� ������ ������������
 */
int 	 __fastcall IntPow(int x, int p);

class TAlmas5ProbSetKey
{
public:
	TAlmas5ProbSetKey();

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
	void __fastcall fill2(TProbKey nKey);//������ n1 n2 ���������

	TProbKey __fastcall unfill();
};




class TAlmas5ProbSetGlobal : public IBaseProbSetGlobalData
{
private:
	AnsiString GetProbNameFromKey(TProbKey nKey);


	TProbKey __fastcall RemoveLeftFromKey2(TProbKey BaseKey);//������ ������ ���� �� �����
	TProbKey __fastcall CanonateKey2(TProbKey BaseKey);//�������� � ������������ �����
	bool __fastcall ChekKey2(TProbKey nKey);//�������� ����� �� ����������� ������������ �����
	TProbKey __fastcall KeyToKey2(TProbKey BaseKey);

public:
	static int 	 __fastcall GetTypeFromKey2(TProbKey BaseKey);//��������� ��� ����� �� �����
	static void __fastcall GetProbNameFromKey2(TProbKey nKey, int &nType, int &nNumber, AnsiString& strName);
private:


	TProbKeyMap m_PiKeyMap;//��� ����������� ����� ��������� � ������� �����������
	TKey2ToKeyMap m_Key2ToKeyMap;//��� ����������� ����� 1 ����� 2

	void Init(void);//������������� ������ ������������
public:
	TAlmas5ProbSetGlobal();
	~TAlmas5ProbSetGlobal();

	static TAlmas5ProbSetGlobal& Get(void);//��������� ������ �� ���������� �����

	//�������� ����� ������������� (�������� ������ ������ ������������)
	//virtual int GetAllNumProbality(void);//���������� ���������� ������������ ������������ � ������
	//virtual AnsiString GetProbName(int Index);//��������� �������� (�����) �����������
	virtual TProbIndex GetProbIndexFromAtomShema(TAtomShema &as);//��������� ������� �� ������ ��� ������� ������������ ������
	//virtual int GetNumLayerAtomShema();//��������� ���������� ���� �� �������� ������ ���� ������� ���������
	//virtual const AnsiString& GetProbSetIdString();//��������� ����������������� ������ ������ �����������
};
//---------------------------------------------------------------------------
/*
 * ��������� ������ ������������
 */
class TAlmas5ProbSetCreator : public IBaseProbSetCreator
{
public:
    TAlmas5ProbSetCreator();
    virtual IBaseProbSet* Create();//�������� ������ ������������
};
//---------------------------------------------------------------------------
/*
 * ��������� ������ ������������
 */
class TAlmas5ProbSet : public IBaseProbSet
{
private:
protected:
    TAlmas5ProbSet(IBaseProbSetCreator& Creator);
    //~TAlmas5ProbSet();

	//virtual bool SaveToFile(HANDLE hFile);
	//virtual bool LoadFromFile(HANDLE hFile);

	friend TAlmas5ProbSetCreator;
	friend TProbPovider;
public:
	//virtual int GetAllNumProbality(void);//���������� ���������� ������������ ������������ � ������
	//virtual AnsiString GetProbName(int Index);//��������� �������� (�����) �����������
	//virtual AnsiString GetProbValue(int Index);//��������� �������� �����������
	//virtual int GetProbIndexFromAtomShema(TAtomShema &as);//��������� ������� �� ������ ��� ������� ������������ ������
	//virtual int GetNumLayerAtomShema();//��������� ���������� ���� �� �������� ������ ���� ������� ���������
    //virtual const AnsiString& GetProbSetIdString();//��������� ����������������� ������ ������ �����������

	virtual ~TAlmas5ProbSet(){};//
};
//---------------------------------------------------------------------------
#endif
