//---------------------------------------------------------------------------
#ifndef DissolutionH
#define DissolutionH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
//---------------------------------------------------------------------------
#include "SurfaceUnit.h"
#include "MaskUnit.h"
#include "ProbalityUnit.h"
//#include "PropertyUnit.h"
#include "DFT.h"
#include "Matrix.h"
#include "QuantityByGroupeUnit.h"
//---------------------------------------------------------------------------
typedef unsigned char DtType;
typedef int DtIndex;
//---------------------------------------------------------------------------
//enum SurfaceMode {smOneLinks,smTreeLinks};
enum SurfaceMode {smFirst,smSecond};
//---------------------------------------------------------------------------
struct TAtom3d
{
	int Coord[3];
    char Type;	//  7  6  5  4  3  2  1  0
				// |--|--------------------|
				// |V |               Type |
				// |--|--------------------|
				//
				//  V - ��������� �����
				//  Type - ��� ����� (��������� ��� �������������)
	int ProbIndex;//��� ����� �� ����������� �������� (������ �����������)
};
//---------------------------------------------------------------------------
struct BigArrayCoord
{
	BigArrayCoord(){};
	BigArrayCoord(unsigned int _Z, unsigned short int _X,unsigned short int _Y, unsigned char _N)
	{
	 Z = _Z;
	 X = _X;
	 Y = _Y;
	 N = _N;
	};
	BigArrayCoord(const BigArrayCoord& BAC);
	unsigned int Z;		   //0  to   4,294,967,295
	unsigned short int X,Y;//16 bits  0  to   65,535//-32,768  to  32,767
	unsigned char N;	   //0  to  7

	BigArrayCoord& operator =(const BigArrayCoord& r);
	bool operator ==(const BigArrayCoord& r);
	bool operator !=(const BigArrayCoord& r);
};
//---------------------------------------------------------------------------
//��������� ������ � ������� ������ ������
struct TCC // CC - Cell Config
{
	int  N;
	int di;
	int dj;
	int dk;
	TCC(int Na, int i, int j, int k);
};
//---------------------------------------------------------------------------
//��������� ������ � ������� ������ ������
struct TCr //Cr - Coordinaty
{
	int dx;
	int dy;
	int dz;
	int SubLayer;
	TCr(int x, int y, int z, int _SubLayer);
};
//---------------------------------------------------------------------------
//������ ��������� ������������� ������
typedef std::vector<BigArrayCoord> TBACVec;
typedef std::vector<TBACVec> TKindAtomVec;
//��������� ������������ ������
class TKindAtoms: public TKindAtomVec
{
public:
	bool SaveToFile(HANDLE hFile, int *pSeek = NULL);//��������� ��������� � �����
	bool LoadFromFile(HANDLE hFile, int *pSeek = NULL);//��������� ��������� �� ������

	bool InitFomProb(TProbPovider &SP);

	int __fastcall GetMainAtomType(TProbIndex Index);//��������� ���� �������� ����� ��� ������ �����������
};
//---------------------------------------------------------------------------
class TUndoDissolutionThread
{
public:
	int *Watch;
	int Count;
	char **Items;

	//BigArrayCoord **KindAtoms;
	//int *KindAtomsCount;

	TKindAtoms KindAtoms;

	//int nProbCnt;//���������� ��������� ������������ (������ KindAtomsCount � KindAtoms)

	int SizeX, SizeY; //������ �����������
	int NumAtomsInCell,NumAtomsInLayer;
	int CopacityMemoryForLayer;
	int OneX, OneY, OneN;
	int SizeDtType, SizeDtIndex, SizeBothDtTypeDtIndex;
	unsigned int iDeletedAtom;
	//double W1,W2,W3;
	TProbPovider SP;
	TAlgoritm m_Algoritm;
	bool Finish;
	unsigned int Plane;
	TDateTime StartTime, FinishTime;

	bool SaveToFile(HANDLE hFile, int *pSeek = NULL);//��������� ��������� � �����
	bool LoadFromFile(HANDLE hFile, int *pSeek = NULL);//��������� ��������� �� ������

	TUndoDissolutionThread();
	~TUndoDissolutionThread();
	void Clear(void);
};
//---------------------------------------------------------------------------
typedef TComplex::value_type TSurfVal;
/*
class TPoint3d
{
	TSurfVal x,y,z;
};
*/
#define INIT_VAL -1.056e-8
class TSurface
{
public:
	void SetSize(int X, int Y);
	int SizeX;
	int SizeY;

    typedef std::vector<TSurfVal> TValVector;
    std::vector<TValVector> Array2D;

    TValVector XGrid;
    TValVector YGrid;

    void SortValVector(TValVector &SV);
    TSurfVal MinVal;
    TSurfVal MaxVal;

    TSurfVal& GetVal(int i, int j);
    TPoint3d iOrt;//���������� ��������� ������� ��� X � ���������� �����������
    TPoint3d jOrt;//���������� ��������� ������� ��� Y � ���������� �����������
	TPoint3d kOrt;//���������� ��������� ������� ��� Z � ���������� �����������

    TMatrix FromBaseToOrtho;//������� �������������� �� �������� ������� ��������� � ����������
    TMatrix FromOrthoToBase;//�������

    bool FromCoordToIndex(TPoint3d Coord, int &i, int &j, TSurfVal &z);//�� ����� ������ ��������� (��������) � ���� ������� ������� � ��������
	//���������� ����� ������ � ����������
	TSurfVal Distance(TPoint3d APoint, TPoint3d NormVector, TSurfVal D);
};
//---------------------------------------------------------------------------
//��� �������� ����� ������ �����������
typedef unsigned char TTypeAtom;
typedef std::vector<TTypeAtom> TTypeAtomVec;
//---------------------------------------------------------------------------
struct TStaticticData
{
public:
	TStaticticData();
	TStaticticData(const TStaticticData& r);

	void operator=(const TStaticticData& r);
	void Init(void);

	float N1;
	float N2;
	float N3;
	int Deleted;

	float MostPopularTypeCount;
};

class  TStaticticDataVec : public std::vector<TStaticticData>
{
public:
	TStaticticDataVec();
	TStaticticDataVec(const TStaticticDataVec &r);
	int m_MostPopularTypeIndex;
};
//typedef std::vector<TStaticticData> TStaticticDataVec;
//---------------------------------------------------------------------------
class TStaticticParam
{
	TStaticticDataVec m_vStatictic;//�� �����������
	TStaticticDataVec m_vAveragedStatictic;//����������� �����������

	void AverageData(void);
public:
	TStaticticParam();

	void Init(void);

	int m_PeriodOfAverage; //���������� ��������� ������ ����� ������� ���������, ���� 0 �� ����������� �� ����������

	int m_MostPopularTypeIndex;

	void AddStaticticData(TStaticticData &data);
	const TStaticticDataVec& GetStatictic(void);
};
//---------------------------------------------------------------------------
class TDissolutionThread : public TThread
{
private:
	TList *Items,*Watch;//������� ������

	TKindAtoms KindAtoms;//�������� ������

	TProbPovider SPn;//������������ �����������

	//������ ����� �������� ����� ��� ������ �����������
	TTypeAtomVec MainAtomTypeVec;//��� �������� ����� ������ �����������
	AnsiString MainAtomTypeVecProbIdString;//������������� ������ ������������
	unsigned int _N1, _N2, _N3;
	unsigned int CurrDeleted;


	int SizeX, SizeY; //������ �����������
	int NumAtomsInLayer;
	int CopacityMemoryForLayer;
	int OneX, OneY, OneN;
	int SizeDtType, SizeDtIndex, SizeBothDtTypeDtIndex;
	unsigned int iDeletedAtom;
	DtType SecondTypeAtom[4];//��� ����� �� ������� ������
	int iSecondTypeAtom;
	BigArrayCoord m_vTreeNeib[40];//���������� ������ ������

	TStaticticParam m_StaticticParam;//�����������

	void __fastcall AddLayers(unsigned int Indx);
	void __fastcall DecTypeAtom(BigArrayCoord* BAC);
	void __fastcall SetToZeroTypeAtom(BigArrayCoord* BAC);
	unsigned char __fastcall GetTypeAtom(BigArrayCoord* BAC);//��������� �����
	int __fastcall GetIndexAtom(BigArrayCoord* BAC);
	void __fastcall SetNoDeletedTypeAtom(BigArrayCoord* BAC);
	void __fastcall SetIndexAtom(BigArrayCoord* BAC, int Indx);
	void __fastcall SetTypeAtom(BigArrayCoord* BAC);//�� ����� ���� ���
	//������� ������� � ����� ������� � ����������� ��� ���������� ���,
	//���� ��������� ������� � �������� �������. ������� ������ ��� ����,
	//����� ������ ���� ���������.
	void __fastcall DelLBACFromKindsArrays(int Sort, int Indx);
	void __fastcall AddLBACtoKindsArrays(int Sort, BigArrayCoord* BAC);
	void __fastcall AdjacentAtom(int N, BigArrayCoord* BAC);
	TProbIndex __fastcall GetKindAtom(BigArrayCoord* BAC);//��� ����� (������ �����������)
	bool GetAtomShema(BigArrayCoord *pBAC, TAtomShema &as, IBaseProbSet *pPS);
	void __fastcall	DeleteOneLinkAtom(BigArrayCoord* BAC);

	int __fastcall FindTreeNeib(BigArrayCoord& BAC, int MaxSize );// ����� �������� ������


	//void __fastcall AdjacentAtom1(BigArrayCoord* BAC);
	//void __fastcall AdjacentAtom2(BigArrayCoord* BAC);
	//void __fastcall AdjacentAtom3(BigArrayCoord* BAC);
	//void __fastcall AdjacentAtom4(BigArrayCoord* BAC);
	void __fastcall CopyBAC1toBAC2(BigArrayCoord* BAC1,BigArrayCoord* BAC2);
	unsigned int GetN1(void);
	unsigned int GetN2(void);
	unsigned int GetN3(void);
	bool __fastcall CalcN1N2N3(void);
	unsigned int GetDeletingLayers(void);
	unsigned int GetDeletedLayers(void);
	unsigned int GetNumAtomsInLayer(int Index);
	int __fastcall GetMemoryCopacityForBAK(void);
	void __fastcall GetCoordAtomInCell(int N, int &dx, int &dy, int &dz);
	void __fastcall DeleteLeftMaskAtoms(TMaskVec &vMask);
	//bool __fastcall IsAtomVisible(int x,int y,int z,TMask *MaskArray, int CntMsk);
	bool __fastcall IsAtomVisible(BigArrayCoord* BAC,TMaskVec &vMask);

	void __fastcall ConFromXyzToBak(int x,int y,int z,BigArrayCoord &BAC);
	void __fastcall SetNoDeleted2TypeAtom(BigArrayCoord* BAC);
	bool __fastcall DeleteAtom(BigArrayCoord* BAC);
	void __fastcall GetTAtom3dFromBAC(TAtom3d* A3d,BigArrayCoord* BAC);
	//int __fastcall GetSortByKind(TAtomShema PE);
	bool __fastcall HoldAtom(BigArrayCoord* BAC, bool b5Type = false);
	int __fastcall GetAdjTypeAtom(BigArrayCoord* BAC);
	bool __fastcall DelOrHoldAtom(BigArrayCoord* BAC, bool bHold = false, bool b5Type = false);

	CRITICAL_SECTION m_CS;//����������� ������

	//��������� ������������, ����������� 1 ��� ��������
	bool __fastcall AlgMonteCarloDeleteAtom(void);//����������� �� ��������� ����������
	bool __fastcall AlgPorogDeleteAtom(void);//����������� �� ��������� ����������
	bool __fastcall AlgPorogDolaDeleteAtom(void);//����������� �� ��������� ��������� �������
	bool __fastcall AlgDolaProbDeleteAtom(void);//����������� �� ��������� ������� �������� �������� ������

	int GetSubLayer(int N);//��������� ������� �������� ������� ��� ����� ������ ��� ������� N

	TAlgoritm m_Algoritm;//�������� �����������
	void __fastcall SetAlgoritm(TAlgoritm &newAlgoritm);

	int GetPopularTypeCount();//���������� ������ �������� ����������� ����

	bool m_InitRng;//���� ������������� ��� (������������� ���������� � ������ �����������)


protected:
	void __fastcall Execute();
public:
	TProbPovider SP;  //����������� ��������

	void RenderingKindAtomByNewAlgoritm(void);//�������� ����� ��������� �������� ����������� ���� ����� ������������

	bool Finish;
	bool MaskAll;//����������� ��� �������� ����� ��� ������, ����� ������ ������ ���� ����� ��� Z
	unsigned int Plane;
	//TExperimentProperty *ExpPrprt;
	//����������
	TDateTime StartTime, FinishTime;
	__property int Height = {read = SizeY};
	__property int Width = {read = SizeX};
	__property unsigned int N1 = {read = GetN1};
	__property unsigned int N2 = {read = GetN2};
	__property unsigned int N3 = {read = GetN3};
	__property unsigned int DeletingLayers = {read = GetDeletingLayers};
	__property unsigned int DeletedLayers = {read = GetDeletedLayers};
	__property unsigned int NumOfAtomsInLayer[int Index] = { read=GetNumAtomsInLayer };
	__property unsigned int DeletedAtom = {read = iDeletedAtom};
	__property  TAlgoritm Algoritm = {read = m_Algoritm, write = SetAlgoritm};//�������� �����������


	void InitIdealSmoothSurface(int NewX,int NewY);
	//void InitIdealMaskedSurface(int NewX,int NewY, TMaskVec &vMask);
	void InitSurface(TDissolutionParametries &DP);
	void RenderingNewMask(TMaskVec &vMask);
	void DeleteMaskedAtoms(void);
	void InitCube(int NewX,int NewY,int NewZ);

	/*
	int GenerateKindAtoms(int Sort, TAtom3d** A3d);
	int GetMaskedAtoms(TAtom3d** A3d);
	int Get4LnksAtoms(TAtom3d** A3d);
	int GetLinksFromKindAtoms(int Sort, TAtom3d** A3dBegin, TAtom3d** A3dEnd);
	int GetLinksFromMaskedAtoms(TAtom3d** A3dBegin, TAtom3d** A3dEnd);
	*/
	int GetCubeAtoms(TAtom3d** A3d, int CubeZ = 0);
	int GetLinksFromCubeAtoms(TAtom3d** A3dBegin, TAtom3d** A3dEnd, int CubeZ = 0);

	bool __fastcall DeleteAtom(void);//��������� ��� ��������

	unsigned char GetTypeAtom(int x,int y,int z);//��������� �����
	bool __fastcall DeleteAtom(int x,int y,int z);
	bool __fastcall HoldAtom(int x,int y,int z);
	__fastcall TDissolutionThread(bool CreateSuspended);
	__fastcall ~TDissolutionThread();
	bool __fastcall SaveToMem(TUndoDissolutionThread *UDT);
	bool __fastcall LoadFromMem(TUndoDissolutionThread *UDT);
	//bool __fastcall DeleteUDT(TUndoDissolutionThread *UDT);

	void GenerateSurface(TSurface &Surf);

	void GenAtomCntInLayer(TAtomCntInLayerVector& vec);

	void InitRNG(void);

	//���������� ������ ��� ����� ��������� �������������
	void EnterCS(void);
	void LeaveCS(void);


	void SetStaticticPeriod(int PeriodOfAverage);//�������� ���� ���������� � �������� ����������
	const TStaticticDataVec& GetStatictic(void);//�������� ������ ����������� ���������
};
//---------------------------------------------------------------------------
#endif
