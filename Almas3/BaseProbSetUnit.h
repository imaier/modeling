//---------------------------------------------------------------------------

#ifndef BaseProbSetUnitH
#define BaseProbSetUnitH
//---------------------------------------------------------------------------
#include <vcl.h>

//---------------------------------------------------------------------------
#define AS_MAX_ATOM_NUM 53
#define AS_MAX_SHEMA (AS_MAX_ATOM_NUM/(sizeof(DWORD)*8)+1)
//---------------------------------------------------------------------------
//ошибочный индекс вероятности
#define PI_ERROR -1
//---------------------------------------------------------------------------
//тип для индекса вероятности
typedef int TProbIndex;
//---------------------------------------------------------------------------
//получение индекса в атомсхеме
//главного атома
#define GetIndex0LevAdj() 0
//первых соседей главного атома
int GetIndex1LevAdj(int nNum1LevAdv);
//вторых соседей главного атома
int GetIndex2LevAdj(int nNum1LevAdv, int nNum2LevAdv);
//третьих соседей главного атома
int GetIndex3LevAdj(int nNum1LevAdv, int nNum2LevAdv, int nNum3LevAdv);
//---------------------------------------------------------------------------
//схема расположения атомов вокруг главного атома (атомсхема)
class TAtomShema
{
private:
	DWORD m_Shema[AS_MAX_SHEMA];

public:
	TAtomShema();
	TAtomShema(const TAtomShema &r);

	TAtomShema& operator = (const TAtomShema &r);

	int GetBit(int nIndex);//1-атом есть, 0 - атом удалён
	void SetBit(int nIndex, int nState);//1-атом есть, 0 - атом удалён

	void Clear(void);//почитстить схему

	AnsiString ToStr(void);//изобразить в виде строки
	AnsiString ToStr2(void);//изобразить в виде строки

	int m_nMaxLayer;//До какого дальнего соседа описана схема
	//-1  - схема не описвывалась
	// 0  - главный атом
	// 1  - первые соседи
	// 2  - вторые соседи
	// 3  - третьи соседи
};
//---------------------------------------------------------------------------


class IBaseProbSet;
/*
 * глобальные данные набора вероятностей
 */
class IBaseProbSetGlobalData
{
protected:
	AnsiString m_IdString;
	AnsiString m_NameString;
	AnsiString m_DiscrptionString;

	bool m_bInit;//класс проинициализирован
	int  m_nAllNumProbality;//количество вероятностей
	int  m_nNumLayerAtomShema;//количество слоёв до которого должна быть описана атомсхема
	CRITICAL_SECTION m_InitCS;//критическая секция инициализации
	AnsiString* m_pstrProbName;//названия вероятностей
	double* m_pdDefaultProbArr;//вероятности по умолчанию

	friend class IBaseProbSet;
	virtual void Init(void) = 0;//инициализация глобальных данных
	//доступны после инициализации (создание обекта набора вероятностей)
	virtual bool FillDefaultProb(double* pdProbArr);//заполнение вероятностями по умолчанию
public:
	IBaseProbSetGlobalData();
	~IBaseProbSetGlobalData();

	virtual const AnsiString& GetProbSetIdString();//получение идентификационной строки набора вероятности
	virtual const AnsiString& GetProbSetNameString();//получение название набора вероятности
	virtual const AnsiString& GetProbSetDiscrptionString();//получение строки описания набора вероятности

	//доступны после инициализации (создание обекта набора вероятностей)
	virtual int GetAllNumProbality(void);//количество уникальных вероятностей вероятностей в наборе
	virtual AnsiString GetProbName(int Index);//получение названия (имени) внроятности
	virtual int GetMainAtomTypeForProb(int Index) = 0;//получение типа главного атома для данной вероятности
	virtual TProbIndex GetProbIndexFromAtomShema(TAtomShema &as) = 0;//получение индекса из набора для данного расположения атомов
	virtual int GetNumLayerAtomShema();//получение количества слоёв до которого должна быть описана атомсхема
	virtual int Get_nS_CountForProb(int Index);//получение количества непрямых вторых соседей для данной вероятности
};
//---------------------------------------------------------------------------
/*
 * Абстрактный класс создателя набора вероятностей
 */
class IBaseProbSetCreator
{
protected:
    IBaseProbSetGlobalData &m_GlobalData;
    IBaseProbSetCreator(IBaseProbSetGlobalData &GlobalData);
public:
    virtual IBaseProbSet* Create() = 0;//создание набора вероятностей
    virtual IBaseProbSetGlobalData& GetInfo();
};
//---------------------------------------------------------------------------
//интерфейс набора вероятностей
class IBaseProbSet
{
private:
protected:
	IBaseProbSetCreator& m_Creator;
	IBaseProbSetGlobalData &m_GD;
    double *m_pdProbArr;
    IBaseProbSet(IBaseProbSetCreator& Creator);

    friend class TProbPovider;

    virtual bool SaveToFile(HANDLE hFile);
    virtual bool LoadFromFile(HANDLE hFile);
public:
//    virtual int GetAllNumProbality(void) = 0;//количество уникальных вероятностей вероятностей в наборе
//    virtual AnsiString GetProbName(int Index) = 0;//получение названия (имени) внроятности
    virtual double GetProbValue(int Index);//получение значения вероятности
    virtual void SetProbValue(int Index, double dProbVal);//установка значения вероятности
//    virtual int GetProbIndexFromAtomShema(TAtomShema &as) = 0;//получение индекса из набора для данного расположения атомов
//    virtual int GetNumLayerAtomShema() = 0;//получение количества слоёв до которого должна быть описана атомсхема
//    virtual AnsiString GetProbSetIdString() = 0;//получение идентификационной строки набора вероятности
    virtual bool FillDefault(void);//заполнить значения вероятности по умолчанию
    virtual bool Copy(IBaseProbSet& ProbSet);//заполнить значения вероятности из другого точно такогоже класса


    virtual IBaseProbSetCreator& GetCreator(void);//получение указателя на класс создателя
    virtual IBaseProbSetGlobalData& GetGlobalData(void);//получение ссылки на клас глобальных данных для этого набора

    virtual ~IBaseProbSet();//
};
//---------------------------------------------------------------------------
#endif
