//---------------------------------------------------------------------------

#ifndef Almas3ProbSetUnitH
#define Almas3ProbSetUnitH
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

class TAlmas3ProbSetKey
{
public:
	TAlmas3ProbSetKey();

	int Adg1;
	int Adg2_i0_j0;
	int Adg2_i1_j0;
	int Adg2_i2_j0;
	int Adg2_i0_j1;
	int Adg2_i1_j1;
	int Adg2_i2_j1;
	int Adg2_i0_j2;
	int Adg2_i1_j2;
	int Adg2_i2_j2;

	int n1s;
	int n1v;
	int n2s;
	int n2v;

	TProbKey2 Key2;

	AnsiString strName;

	void __fastcall fill(TProbKey nKey);
	void __fastcall fill2(TProbKey nKey);//только n1 n2 посчитать
};




class TAlmas3ProbSetGlobal : public IBaseProbSetGlobalData
{
private:
	/*
	струтура ключа
	--------------------------------------
	| биты     | значение
	--------------------------------------
	| 0-3      | первые соседи главного атома
	| 4-5      | связность второго соседа без учета первого соседа
	*/
	TProbKey __fastcall RemoveLeftFromKey(TProbKey BaseKey);//убрать лишние биты из ключа
	TProbKey __fastcall CanonateKey(TProbKey BaseKey);//привести к канонической форме
	int      __fastcall GetTypeFromKey(TProbKey BaseKey);//вычислить тип атома по ключу
	AnsiString GetProbNameFromKey(TProbKey nKey);


	TProbKey __fastcall RemoveLeftFromKey2(TProbKey BaseKey);//убрать лишние биты из ключа
	TProbKey __fastcall CanonateKey2(TProbKey BaseKey);//привести к канонической форме
	TProbKey __fastcall KeyToKey2(TProbKey BaseKey);

public:
	static int 	 __fastcall GetTypeFromKey2(TProbKey BaseKey);//вычислить тип атома по ключу
	static void __fastcall GetProbNameFromKey2(TProbKey nKey, int &nType, int &nNumber, AnsiString& strName);
private:


	TProbKeyMap m_PiKeyMap;//мап соответсвия ключа атомсхемы и индекса вероятности
	TKey2ToKeyMap m_Key2ToKeyMap;//мап соответсвия ключа 1 ключу 2

	void Init(void);//инициализация набора вероятностей
public:
	TAlmas3ProbSetGlobal();
	~TAlmas3ProbSetGlobal();

	static TAlmas3ProbSetGlobal& Get(void);//получение ссылки на глобальный класс

	//доступны после инициализации (создание обекта набора вероятностей)
	//virtual int GetAllNumProbality(void);//количество уникальных вероятностей вероятностей в наборе
	//virtual AnsiString GetProbName(int Index);//получение названия (имени) внроятности
	virtual TProbIndex GetProbIndexFromAtomShema(TAtomShema &as);//получение индекса из набора для данного расположения атомов
	//virtual int GetNumLayerAtomShema();//получение количества слоёв до которого должна быть описана атомсхема
	//virtual const AnsiString& GetProbSetIdString();//получение идентификационной строки набора вероятности
	virtual int GetMainAtomTypeForProb(int Index);//получение типа главного атома для данной вероятности
};
//---------------------------------------------------------------------------
/*
 * создатель набора вероятностей
 */
class TAlmas3ProbSetCreator : public IBaseProbSetCreator
{
public:
    TAlmas3ProbSetCreator();
    virtual IBaseProbSet* Create();//создание набора вероятностей
};
//---------------------------------------------------------------------------
/*
 * интерфейс набора вероятностей
 */
class TAlmas3ProbSet : public IBaseProbSet
{
private:
protected:
    TAlmas3ProbSet(IBaseProbSetCreator& Creator);
    //~TAlmas3ProbSet();

	//virtual bool SaveToFile(HANDLE hFile);
	//virtual bool LoadFromFile(HANDLE hFile);

	friend TAlmas3ProbSetCreator;
	friend TProbPovider;
public:
	//virtual int GetAllNumProbality(void);//количество уникальных вероятностей вероятностей в наборе
	//virtual AnsiString GetProbName(int Index);//получение названия (имени) внроятности
	//virtual AnsiString GetProbValue(int Index);//получение значения вероятности
	//virtual int GetProbIndexFromAtomShema(TAtomShema &as);//получение индекса из набора для данного расположения атомов
	//virtual int GetNumLayerAtomShema();//получение количества слоёв до которого должна быть описана атомсхема
    //virtual const AnsiString& GetProbSetIdString();//получение идентификационной строки набора вероятности

	virtual ~TAlmas3ProbSet(){};//
};
//---------------------------------------------------------------------------
#endif
