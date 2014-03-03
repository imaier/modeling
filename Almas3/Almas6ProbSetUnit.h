//---------------------------------------------------------------------------

#ifndef Almas6ProbSetUnitH
#define Almas6ProbSetUnitH
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

class TAlmas6ProbSetKey
{
public:
	TAlmas6ProbSetKey();

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




class TAlmas6ProbSetGlobal : public IBaseProbSetGlobalData
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
	TAlmas6ProbSetGlobal();
	~TAlmas6ProbSetGlobal();

	static TAlmas6ProbSetGlobal& Get(void);//��������� ������ �� ���������� �����

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
class TAlmas6ProbSetCreator : public IBaseProbSetCreator
{
public:
    TAlmas6ProbSetCreator();
    virtual IBaseProbSet* Create();//�������� ������ ������������
};
//---------------------------------------------------------------------------
/*
 * ��������� ������ ������������
 */
class TAlmas6ProbSet : public IBaseProbSet
{
private:
protected:
	TAlmas6ProbSet(IBaseProbSetCreator& Creator);
    //~TAlmas6ProbSet();

	//virtual bool SaveToFile(HANDLE hFile);
	//virtual bool LoadFromFile(HANDLE hFile);

	friend TAlmas6ProbSetCreator;
	friend TProbPovider;
public:
	//virtual int GetAllNumProbality(void);//���������� ���������� ������������ ������������ � ������
	//virtual AnsiString GetProbName(int Index);//��������� �������� (�����) �����������
	//virtual AnsiString GetProbValue(int Index);//��������� �������� �����������
	//virtual int GetProbIndexFromAtomShema(TAtomShema &as);//��������� ������� �� ������ ��� ������� ������������ ������
	//virtual int GetNumLayerAtomShema();//��������� ���������� ���� �� �������� ������ ���� ������� ���������
    //virtual const AnsiString& GetProbSetIdString();//��������� ����������������� ������ ������ �����������

	virtual ~TAlmas6ProbSet(){};//
};
//---------------------------------------------------------------------------
#endif
