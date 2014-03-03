//---------------------------------------------------------------------------

#ifndef Almas2ProbSetUnitH
#define Almas2ProbSetUnitH
///---------------------------------------------------------------------------
#include "BaseProbSetUnit.h"
#include "ProbPoviderUnit.h"
//---------------------------------------------------------------------------
/*
 * ����� ���������� ������ ��� ������� ������ ������������
 */
class TAlmas2ProbSetGlobal : public IBaseProbSetGlobalData
{
private:
	void Init(void);//������������� ������ ������������
public:
	TAlmas2ProbSetGlobal();
	~TAlmas2ProbSetGlobal();

	static TAlmas2ProbSetGlobal& Get(void);//��������� ������ �� ���������� �����

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
class TAlmas2ProbSetCreator : public IBaseProbSetCreator
{
public:
    TAlmas2ProbSetCreator();
    virtual IBaseProbSet* Create();//�������� ������ ������������
};
//---------------------------------------------------------------------------
/*
 * ��������� ������ ������������
 */
class TAlmas2ProbSet : public IBaseProbSet
{
private:
protected:
    TAlmas2ProbSet(IBaseProbSetCreator& Creator);
    //~TAlmas2ProbSet();

	//virtual bool SaveToFile(HANDLE hFile);
	//virtual bool LoadFromFile(HANDLE hFile);

	friend TAlmas2ProbSetCreator;
	friend TProbPovider;
public:
	//virtual int GetAllNumProbality(void);//���������� ���������� ������������ ������������ � ������
	//virtual AnsiString GetProbName(int Index);//��������� �������� (�����) �����������
	//virtual AnsiString GetProbValue(int Index);//��������� �������� �����������
	//virtual int GetProbIndexFromAtomShema(TAtomShema &as);//��������� ������� �� ������ ��� ������� ������������ ������
	//virtual int GetNumLayerAtomShema();//��������� ���������� ���� �� �������� ������ ���� ������� ���������
    //virtual const AnsiString& GetProbSetIdString();//��������� ����������������� ������ ������ �����������

	virtual ~TAlmas2ProbSet(){};//
};
//---------------------------------------------------------------------------
#endif
