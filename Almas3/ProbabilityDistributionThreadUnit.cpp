//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProbabilityDistributionThreadUnit.h"
#include <stdlib.h>
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ProbabilityDistributionThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall ProbabilityDistributionThread::ProbabilityDistributionThread(bool CreateSuspended, ProbabilityDistributionInputData &InputData)
	: TThread(CreateSuspended), inputData(InputData)
{
	data.Init(inputData.Module);
}
//---------------------------------------------------------------------------
void ProbabilityDistributionThread::SetName()
{
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = "ProbabilityDistribution";
	info.dwThreadID = -1;
	info.dwFlags = 0;

	__try
	{
		RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD),(DWORD*)&info );
	}
	__except (EXCEPTION_CONTINUE_EXECUTION)
	{
	}
}
//---------------------------------------------------------------------------
void __fastcall ProbabilityDistributionThread::Execute()
{
	SetName();
	//---- Place thread code here ----
	if(inputData.InitRng)
	{
		randomize();
	}

	int number;
	while(Terminated == false)
	{
		//number = random(RAND_MAX)%inputData.Module;
		number = random(inputData.Module);
		data.DistributionVec[number]++;
		data.RndCnt++;

		if(data.RndCnt == inputData.PauseGenNum)
		{
			data.SuspedTread = true;
			Synchronize(&PerformCallback);
		}

		if(data.RndCnt%inputData.UpdatePeriod == 0)
		{
			Synchronize(&PerformCallback);
			//PerformCallback();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall ProbabilityDistributionThread::PerformCallback(void)
{
	if (inputData.CallbackFunc != NULL)
	{
		inputData.CallbackFunc(inputData.owner, data);
	}
}
//---------------------------------------------------------------------------
void ProbabilityDistributionData::Init(int Module)
{
	DistributionVec.clear();
	DistributionVec.resize(Module);
	RndCnt = 0;
	SuspedTread = false;
}
//---------------------------------------------------------------------------
ProbabilityDistributionData::ProbabilityDistributionData()
{
	Init(10);
}
//---------------------------------------------------------------------------
ProbabilityDistributionData::ProbabilityDistributionData(const ProbabilityDistributionData &r)
{
	DistributionVec = r.DistributionVec;
	RndCnt = r.RndCnt;
}
//---------------------------------------------------------------------------
void ProbabilityDistributionInputData::Init()
{
	Module = 50 ;
	InitRng = false;
	UpdatePeriod = 500;
	PauseGenNum = 0;
	owner = NULL;
	CallbackFunc = NULL;
}
//---------------------------------------------------------------------------
ProbabilityDistributionInputData::ProbabilityDistributionInputData()
{
	Init();
}
//---------------------------------------------------------------------------
ProbabilityDistributionInputData::ProbabilityDistributionInputData(const ProbabilityDistributionInputData &r)
{
	Module = r.Module;
	InitRng = r.InitRng;
	UpdatePeriod = r.UpdatePeriod;
	PauseGenNum = r.PauseGenNum;
	owner = r.owner;
	CallbackFunc = r.CallbackFunc;
}
//---------------------------------------------------------------------------
