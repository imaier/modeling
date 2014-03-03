//---------------------------------------------------------------------------

#ifndef Almas1ProbSetUnitH
#define Almas1ProbSetUnitH
//---------------------------------------------------------------------------
#include "BaseProbSetUnit.h"
#include "ProbPoviderUnit.h"
//---------------------------------------------------------------------------
/*
 * ����� ���������� ������ ��� ������� ������ ������������
 */
class TAlmas1ProbSetGlobal : public IBaseProbSetGlobalData
{
private:
	void Init(void);//������������� ������ ������������
public:
	TAlmas1ProbSetGlobal();
	~TAlmas1ProbSetGlobal();

	static TAlmas1ProbSetGlobal& Get(void);//��������� ������ �� ���������� �����

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
class TAlmas1ProbSetCreator : public IBaseProbSetCreator
{
public:
    TAlmas1ProbSetCreator();
    virtual IBaseProbSet* Create();//�������� ������ ������������
};
//---------------------------------------------------------------------------
/*
 * ��������� ������ ������������
 */
class TAlmas1ProbSet : public IBaseProbSet
{
private:
protected:
    TAlmas1ProbSet(IBaseProbSetCreator& Creator);
    //~TAlmas1ProbSet();

	//virtual bool SaveToFile(HANDLE hFile);
	//virtual bool LoadFromFile(HANDLE hFile);

	friend TAlmas1ProbSetCreator;
	friend TProbPovider;
public:
	//virtual int GetAllNumProbality(void);//���������� ���������� ������������ ������������ � ������
	//virtual AnsiString GetProbName(int Index);//��������� �������� (�����) �����������
	//virtual AnsiString GetProbValue(int Index);//��������� �������� �����������
	//virtual int GetProbIndexFromAtomShema(TAtomShema &as);//��������� ������� �� ������ ��� ������� ������������ ������
	//virtual int GetNumLayerAtomShema();//��������� ���������� ���� �� �������� ������ ���� ������� ���������
    //virtual const AnsiString& GetProbSetIdString();//��������� ����������������� ������ ������ �����������

	virtual ~TAlmas1ProbSet(){};//
};
//---------------------------------------------------------------------------
#endif
