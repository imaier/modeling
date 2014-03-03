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
 * Класс глобальных данных для данного набора вероятностей
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
	void __fastcall fill2(TProbKey nKey);//только n1 n2 посчитать

	TProbKey __fastcall unfill();
};




class TAlmas5ProbSetGlobal : public IBaseProbSetGlobalData
{
private:
	AnsiString GetProbNameFromKey(TProbKey nKey);


	TProbKey __fastcall RemoveLeftFromKey2(TProbKey BaseKey);//убрать лишние биты из ключа
	TProbKey __fastcall CanonateKey2(TProbKey BaseKey);//привести к канонической форме
	bool __fastcall ChekKey2(TProbKey nKey);//проверка ключа на соответсвие канонической форме
	TProbKey __fastcall KeyToKey2(TProbKey BaseKey);

public:
	static int 	 __fastcall GetTypeFromKey2(TProbKey BaseKey);//вычислить тип атома по ключу
	static void __fastcall GetProbNameFromKey2(TProbKey nKey, int &nType, int &nNumber, AnsiString& strName);
private:


	TProbKeyMap m_PiKeyMap;//мап соответсвия ключа атомсхемы и индекса вероятности
	TKey2ToKeyMap m_Key2ToKeyMap;//мап соответсвия ключа 1 ключу 2

	void Init(void);//инициализация набора вероятностей
public:
	TAlmas5ProbSetGlobal();
	~TAlmas5ProbSetGlobal();

	static TAlmas5ProbSetGlobal& Get(void);//получение ссылки на глобальный класс

	//доступны после инициализации (создание обекта набора вероятностей)
	//virtual int GetAllNumProbality(void);//количество уникальных вероятностей вероятностей в наборе
	//virtual AnsiString GetProbName(int Index);//получение названия (имени) внроятности
	virtual TProbIndex GetProbIndexFromAtomShema(TAtomShema &as);//получение индекса из набора для данного расположения атомов
	//virtual int GetNumLayerAtomShema();//получение количества слоёв до которого должна быть описана атомсхема
	//virtual const AnsiString& GetProbSetIdString();//получение идентификационной строки набора вероятности
};
//---------------------------------------------------------------------------
/*
 * создатель набора вероятностей
 */
class TAlmas5ProbSetCreator : public IBaseProbSetCreator
{
public:
    TAlmas5ProbSetCreator();
    virtual IBaseProbSet* Create();//создание набора вероятностей
};
//---------------------------------------------------------------------------
/*
 * интерфейс набора вероятностей
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
	//virtual int GetAllNumProbality(void);//количество уникальных вероятностей вероятностей в наборе
	//virtual AnsiString GetProbName(int Index);//получение названия (имени) внроятности
	//virtual AnsiString GetProbValue(int Index);//получение значения вероятности
	//virtual int GetProbIndexFromAtomShema(TAtomShema &as);//получение индекса из набора для данного расположения атомов
	//virtual int GetNumLayerAtomShema();//получение количества слоёв до которого должна быть описана атомсхема
    //virtual const AnsiString& GetProbSetIdString();//получение идентификационной строки набора вероятности

	virtual ~TAlmas5ProbSet(){};//
};
//---------------------------------------------------------------------------
#endif
