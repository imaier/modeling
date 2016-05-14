//---------------------------------------------------------------------------

#ifndef ProbabilityDistributionThreadUnitH
#define ProbabilityDistributionThreadUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
class ProbabilityDistributionData;

typedef void (*ProbabilityDistributionCallback)(TForm *owner, ProbabilityDistributionData &data);
//---------------------------------------------------------------------------
class ProbabilityDistributionInputData
{
public:
	int Module;
	bool InitRng;
	int UpdatePeriod;
	int PauseGenNum;
	TForm *owner;
	ProbabilityDistributionCallback CallbackFunc;

	void Init();
	ProbabilityDistributionInputData();
	ProbabilityDistributionInputData(const ProbabilityDistributionInputData &r);
};
//---------------------------------------------------------------------------
class ProbabilityDistributionData
{
public:
	std::vector<int> DistributionVec;
	UINT RndCnt;

	bool SuspedTread;

	void Init(int Module);
	ProbabilityDistributionData();
	ProbabilityDistributionData(const ProbabilityDistributionData &r);
};
//---------------------------------------------------------------------------
class ProbabilityDistributionThread : public TThread
{
  typedef struct tagTHREADNAME_INFO
  {
	DWORD dwType;     // must be 0x1000
	LPCSTR szName;    // pointer to name (in user addr space)
	DWORD dwThreadID; // thread ID (-1=caller thread)
	DWORD dwFlags;    // reserved for future use, must be zero
  } THREADNAME_INFO;
private:
  void SetName();

protected:
	void __fastcall Execute();
public:
	ProbabilityDistributionData data;
	ProbabilityDistributionInputData inputData;

	__fastcall ProbabilityDistributionThread(bool CreateSuspended, ProbabilityDistributionInputData &InputData);

	void __fastcall PerformCallback(void);

};
//---------------------------------------------------------------------------
#endif
