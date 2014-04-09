//---------------------------------------------------------------------------

#ifndef Almas7ProbSetUnitH
#define Almas7ProbSetUnitH
//---------------------------------------------------------------------------
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

	//�������������� �����������
	int F;  // F � ����� ����� ������ �������
	int dS; // dS � ����� ������ ������ �������
	int nS; // nS � ����� ������ �������� �������

	TProbKey2 Key2;
	TProbKey Key;

	AnsiString strName;

	void __fastcall fill(TProbKey nKey);
	void __fastcall fill2(TProbKey nKey);//��������� ������ �������������� �����������

	TProbKey __fastcall unfill();
};




class TAlmas7ProbSetGlobal : public IBaseProbSetGlobalData
{
private:
	AnsiString GetProbNameFromKey(TProbKey nKey);


	TProbKey __fastcall RemoveLeftFromKey2(TProbKey BaseKey);//������ ������ ���� �� �����
	TProbKey __fastcall CanonateKey2(TProbKey BaseKey);//�������� � ������������ �����
	bool __fastcall ChekKey2(TProbKey nKey);//�������� ����� �� ����������� ������������ �����
	TProbKey __fastcall KeyToKey2(TProbKey BaseKey);

public:
	static int 	 __fastcall GetTypeFromKey(TProbKey BaseKey);//��������� ��� ����� �� �����
	static void __fastcall GetProbNameFromKey(TProbKey nKey, int nNumber, AnsiString& strName);
private:


	TProbKeyMap m_PiKeyMap;//��� ����������� ����� ��������� � ������� �����������
	TKey2ToKeyMap m_Key2ToKeyMap;//��� ����������� ����� 1 ����� 2

	void Init(void);//������������� ������ ������������
public:
	TAlmas7ProbSetGlobal();
	~TAlmas7ProbSetGlobal();

	static TAlmas7ProbSetGlobal& Get(void);//��������� ������ �� ���������� �����

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
class TAlmas7ProbSetCreator : public IBaseProbSetCreator
{
public:
    TAlmas7ProbSetCreator();
    virtual IBaseProbSet* Create();//�������� ������ ������������
};
//---------------------------------------------------------------------------
/*
 * ��������� ������ ������������
 */
class TAlmas7ProbSet : public IBaseProbSet
{
private:
protected:
	TAlmas7ProbSet(IBaseProbSetCreator& Creator);
    //~TAlmas7ProbSet();

	//virtual bool SaveToFile(HANDLE hFile);
	//virtual bool LoadFromFile(HANDLE hFile);

	friend TAlmas7ProbSetCreator;
	friend TProbPovider;
public:
	//virtual int GetAllNumProbality(void);//���������� ���������� ������������ ������������ � ������
	//virtual AnsiString GetProbName(int Index);//��������� �������� (�����) �����������
	//virtual AnsiString GetProbValue(int Index);//��������� �������� �����������
	//virtual int GetProbIndexFromAtomShema(TAtomShema &as);//��������� ������� �� ������ ��� ������� ������������ ������
	//virtual int GetNumLayerAtomShema();//��������� ���������� ���� �� �������� ������ ���� ������� ���������
    //virtual const AnsiString& GetProbSetIdString();//��������� ����������������� ������ ������ �����������

	virtual ~TAlmas7ProbSet(){};//
};
//---------------------------------------------------------------------------
#endif
