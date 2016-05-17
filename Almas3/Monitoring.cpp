//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#pragma warn -pck

#include "Monitoring.h"
#include "Main.h"
#include "Dissolution.h"
#include "N1N2N3QuantityDiagramUnit.h"
#include "RNGsProbabilityDistributionUnit.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMonitoringForm *MonitoringForm;
//---------------------------------------------------------------------------
__fastcall TMonitoringForm::TMonitoringForm(TComponent* Owner)
	: TForm(Owner)
{
    InnerDataGroupBox->Caption = "Входные данные";
	 PlaneTextLabel->Caption = "Сколько атомов удалить:";
     N1ProbabilityTextLabel->Caption = "Вероятность удаления односвязного атома:";
     N2ProbabilityTextLabel->Caption = "Вероятность удаления двухсвязного атома:";
     N3ProbabilityTextLabel->Caption = "Вероятность удаления трёхсвязного атома:";
    OuterDataGroupBox->Caption = "Выходные данные";
     StateTextLabel->Caption = "Состояние процесса:";
     DeletedAtomTextLabel->Caption = "Число удалённых атомов:";
     DeletingLayersTextLabel->Caption = "Число растворяющихся слоёв:";
     DeletedLayersTextLabel->Caption = "Число растворившихся слоёв:";
     N1TextLabel->Caption = "Число односвязных атомов:";
     N2TextLabel->Caption = "Число двухсвязных атомов:";
     N3TextLabel->Caption = "Число трёхсвязных атомов:";
     EnableCheckBox->Caption = "Разрешить обновления";
    StatisticsGroupBox->Caption = "Время";
     StartTimeTextLabel->Caption = "Время запуска:";
     DissolutionTimeTextLabel->Caption = "Прошло:";
	 RemainedTimeTextLabel->Caption = "Осталось:";
     CompleteTimeTextLabel->Caption = "Время завершения:";
     //SpeedTextLabel->Caption = "Скорость процесса [атом/сек]:";
     AverageSpeedTextLabel->Caption = "Средняя скорость процесса [атом/сек]:";
     FluidSpeedTextLabel->Caption = "Текущаяя скорость процесса [атом/сек]:";

    DelAtomAtLastTime = 0;
    LastTime = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMonitoringForm::MonitoringTimerTimer(TObject *Sender)
{
	AnsiString StateThread;
	static clock_t LastClock = clock();
	clock_t CurrClock = clock();
	clock_t DeltaClock = CurrClock - LastClock;
	LastClock = CurrClock;


	if(DissolutionThread != NULL)
	{
	 int Plane = DissolutionThread->Plane;
	 //DissolutionThread->Plane
	 PlaneNumLabel->Caption = AnsiString(Plane);
	 //N1ProbabilityNumLabel->Caption = AnsiString(DissolutionThread->W1);
	 //N2ProbabilityNumLabel->Caption = AnsiString(DissolutionThread->W2);
	 //N3ProbabilityNumLabel->Caption = AnsiString(DissolutionThread->W3);
	 N1ProbabilityNumLabel->Caption = "Не известно";
	 N2ProbabilityNumLabel->Caption = "Не известно";
	 N3ProbabilityNumLabel->Caption = "Не известно";

	 int DeletedAtom = DissolutionThread->DeletedAtom;
	 if(!DissolutionThread->Suspended) StateNumLabel->Caption = "Выполныется";
	 else
	 {
	  StateNumLabel->Caption = "Остановлен";
	  StateThread = " процесс приостановлен";
	 }
	 DeletedAtomNumLabel->Caption = AnsiString(DeletedAtom) + StateThread;

	 //DissolutionThread->SetStaticticPeriod(1);

	 int DeletingLayers, DeletedLayers;
     DeletingLayers = (int)DissolutionThread->DeletingLayers;
     DeletedLayers = (int)DissolutionThread->DeletedLayers;
     //DeletingLayersNumLabel->Caption = AnsiString((int)DissolutionThread->DeletingLayers) + StateThread;
     //DeletedLayersNumLabel->Caption = AnsiString((int)DissolutionThread->DeletedLayers) + StateThread;
     DeletingLayersNumLabel->Caption = AnsiString((int)DeletingLayers) + StateThread;
     DeletedLayersNumLabel->Caption = AnsiString((int)DeletedLayers) + StateThread;
     N1NumLabel->Caption = AnsiString((int)DissolutionThread->N1) + StateThread;
     N2NumLabel->Caption = AnsiString((int)DissolutionThread->N2) + StateThread;
     N3NumLabel->Caption = AnsiString((int)DissolutionThread->N3) + StateThread;
     //if((DeletingLayers != (int)DissolutionThread->DeletingLayers)||
     //   (DeletedLayers != (int)DissolutionThread->DeletedLayers))
     //{
	 //int DeletingLayers, DeletedLayers;
     //DeletingLayers = (int)DissolutionThread->DeletingLayers;
     //DeletedLayers = (int)DissolutionThread->DeletedLayers;
     //NumOfAtomsInLayerListBox->Items->Clear();
     if(EnableCheckBox->Checked)
     {
      for(int i=0; i< DeletingLayers+DeletedLayers; i++)
      {
       if(i < NumOfAtomsInLayerListBox->Items->Count)
		NumOfAtomsInLayerListBox->Items->Strings[i] = IntToStr(i+1) + ((i==1)?"-ой" :((i==2)?"-ий" : "-ый"))
       									   + " слой содержит "
                                            + IntToStr((int)DissolutionThread->NumOfAtomsInLayer[i])
                                            + " атомов" + StateThread;
       else NumOfAtomsInLayerListBox->Items->Add(IntToStr(i+1) + ((i==2)?"-ой" :(i==3)?"-ий" : "-ый")
      									   +" слой содержит "
                                           + IntToStr((int)DissolutionThread->NumOfAtomsInLayer[i])
                                           + " атомов" + StateThread);
      }
     }
     //}
     StartTimeNumLabel->Caption = DissolutionThread->StartTime.TimeString();
	 TDateTime NadoTime,Proshlo = (MainForm->DissolutionTime);
     DissolutionTimeNumLabel->Caption = Proshlo.TimeString();
     //if(!DissolutionThread->Suspended)
     //{
      if( (double)Proshlo != 0)
      {
       double dAvSpeed,dFlSpeed;
       dAvSpeed = (double)DeletedAtom/((double)Proshlo);
       AverageSpeedNumLabel->Caption = AnsiString(dAvSpeed/86400.0);//24*60*60
       if(((double)LastTime) == 0) LastTime = Proshlo;
	   dFlSpeed = (double)(DeletedAtom - DelAtomAtLastTime)/((double)(LastTime.CurrentDateTime() - LastTime));

	   dFlSpeed = (double)(DeletedAtom - DelAtomAtLastTime)/((double)(LastTime.CurrentDateTime() - LastTime));

	   if(DeltaClock > 0)
		dFlSpeed = (double)(DeletedAtom - DelAtomAtLastTime)*1000.0*86400.0/((double)(DeltaClock));


	   FluidSpeedNumLabel->Caption = AnsiString(dFlSpeed/86400.0);//24*60*60
	   DelAtomAtLastTime = DeletedAtom;
	   LastTime = LastTime.CurrentDateTime();
       if(dFlSpeed*dFlSpeed > 0.0001)
       {
        NadoTime = TDateTime((double)(Plane-DeletedAtom)/dFlSpeed);
        RemainedTimeNumLabel->Caption = NadoTime.TimeString();
        CompleteTimeNumLabel->Caption = (NadoTime.CurrentDateTime() + NadoTime).FormatString("dd.mm.yyyy в hh:nn:ss");
	   }
       else
       {
        if(!DissolutionThread->Suspended)
        {
         RemainedTimeNumLabel->Caption = "Скорость мала, невозможно рассчитать" + StateThread;
         CompleteTimeNumLabel->Caption = "Скорость мала, невозможно рассчитать" + StateThread;
        }
        else
        {
         RemainedTimeNumLabel->Caption = StateThread;
     	 CompleteTimeNumLabel->Caption = StateThread;
		}
       }
      }
      else
      {
       RemainedTimeNumLabel->Caption = "Прошло мало времени, невозможно рассчитать" + StateThread;
       CompleteTimeNumLabel->Caption = "Прошло мало времени, невозможно рассчитать" + StateThread;
       AverageSpeedNumLabel->Caption = "Прошло мало времени, невозможно рассчитать" + StateThread;
       FluidSpeedNumLabel->Caption = "Прошло мало времени, невозможно рассчитать" + StateThread;
      }
     //}
     //else
     //{
     // RemainedTimeNumLabel->Caption = StateThread;
     // CompleteTimeNumLabel->Caption = StateThread;
     // AverageSpeedNumLabel->Caption = StateThread;
     // FluidSpeedNumLabel->Caption = StateThread;
     //}
     if(Plane != 0)
      if(ProgressBar->Position != 100*DeletedAtom/Plane)
     {
      ProgressBar->Position = (TProgressRange)(100*DeletedAtom/Plane);
      ProgressBar->Hint  = IntToStr(ProgressBar->Position) + " %";
     }
     //else
     //{
	 // ProgressBar->Position = (TProgressRange)(0);
     // ProgressBar->Hint  = "Не задано сколько удалить атомов.";
     //}
     //if(ProgressBar->Max != Plane) ProgressBar->Max = (TProgressRange)Plane;
    }
    else
    {
     StateThread = "Недоступно";
	 PlaneNumLabel->Caption = StateThread;
     N1ProbabilityNumLabel->Caption = StateThread;
     N2ProbabilityNumLabel->Caption = StateThread;
     N3ProbabilityNumLabel->Caption = StateThread;

     StateNumLabel->Caption = "Процесс не создан или удалён";

     DeletedAtomNumLabel->Caption = StateThread;
     DeletingLayersNumLabel->Caption = StateThread;
     DeletedLayersNumLabel->Caption = StateThread;
     N1NumLabel->Caption = StateThread;
     N2NumLabel->Caption = StateThread;
     N3NumLabel->Caption = StateThread;

     if(NumOfAtomsInLayerListBox->Items->Count != 0)
      NumOfAtomsInLayerListBox->Items->Clear();

     StartTimeNumLabel->Caption = StateThread;
     DissolutionTimeNumLabel->Caption = StateThread;
     RemainedTimeNumLabel->Caption = StateThread;
     CompleteTimeNumLabel->Caption = StateThread;
     AverageSpeedNumLabel->Caption = StateThread;
     FluidSpeedNumLabel->Caption = StateThread;
     if(ProgressBar->Position != 0)
     {
      ProgressBar->Position = 0;
      ProgressBar->Hint  = StateThread;
     }
    }
/*    AnsiString StateThread;
	if(DissolutionThread != NULL)
    {
     int Plane = DissolutionThread->Sample->Plane;
     //DissolutionThread->Sample->Plane
	 PlaneNumLabel->Caption = AnsiString(Plane);
     N1ProbabilityNumLabel->Caption = AnsiString(DissolutionThread->Sample->N1Probability);
     N2ProbabilityNumLabel->Caption = AnsiString(DissolutionThread->Sample->N2Probability);
     N3ProbabilityNumLabel->Caption = AnsiString(DissolutionThread->Sample->N3Probability);

     int DeletedAtom = DissolutionThread->Sample->DeletedAtom;
     if(!DissolutionThread->Suspended) StateNumLabel->Caption = "Выполныется";
     else
	 {
      StateNumLabel->Caption = "Остановлен";
      StateThread = " процесс приостановлен";
     }
     DeletedAtomNumLabel->Caption = AnsiString(DeletedAtom) + StateThread;
     DeletingLayersNumLabel->Caption = AnsiString((int)DissolutionThread->Sample->DeletingLayers) + StateThread;
     DeletedLayersNumLabel->Caption = AnsiString((int)DissolutionThread->Sample->DeletedLayers) + StateThread;
     N1NumLabel->Caption = AnsiString((int)DissolutionThread->Sample->N1) + StateThread;
     N2NumLabel->Caption = AnsiString((int)DissolutionThread->Sample->N2) + StateThread;
     N3NumLabel->Caption = AnsiString((int)DissolutionThread->Sample->N3) + StateThread;
     //if((DeletingLayers != (int)DissolutionThread->Sample->DeletingLayers)||
     //   (DeletedLayers != (int)DissolutionThread->Sample->DeletedLayers))
     //{
	 int DeletingLayers, DeletedLayers;
     DeletingLayers = (int)DissolutionThread->Sample->DeletingLayers;
     DeletedLayers = (int)DissolutionThread->Sample->DeletedLayers;
     //NumOfAtomsInLayerListBox->Items->Clear();
     for(int i=0; i< DeletingLayers+DeletedLayers; i++)
     {
      if(i < NumOfAtomsInLayerListBox->Items->Count)
       NumOfAtomsInLayerListBox->Items->Strings[i] = IntToStr(i+1) + ((i==1)?"-ой" :((i==2)?"-ий" : "-ый"))
      									   + " слой содержит "
                                           + IntToStr((int)DissolutionThread->Sample->NumOfAtomsInLayer[i])
                                           + " атомов" + StateThread;
      else NumOfAtomsInLayerListBox->Items->Add(IntToStr(i+1) + ((i==2)?"-ой" :(i==3)?"-ий" : "-ый")
      									   +" слой содержит "
										   + IntToStr((int)DissolutionThread->Sample->NumOfAtomsInLayer[i])
                                           + " атомов" + StateThread);
     }
     //}
     StartTimeNumLabel->Caption = DissolutionThread->StartTime.TimeString();
     TDateTime NadoTime,Proshlo = (MainForm->DissolutionTime.CurrentDateTime() - DissolutionThread->StartTime);
     if(!DissolutionThread->Suspended)
     {
      DissolutionTimeNumLabel->Caption = Proshlo.TimeString();
      if( (double)Proshlo != 0)
      {
       double dSpeed;
	   dSpeed = (double)DeletedAtom/((double)Proshlo);
       SpeedNumLabel->Caption = AnsiString(dSpeed/86400.0);//24*60*60
       if(dSpeed != 0)
       {
        NadoTime = TDateTime((double)(Plane-DeletedAtom)/dSpeed);
        RemainedTimeNumLabel->Caption = NadoTime.TimeString();
        CompleteTimeNumLabel->Caption = (NadoTime.CurrentDateTime() + NadoTime).FormatString("dd.mm.yyyy в hh:nn:ss");
       }
       else
       {
        RemainedTimeNumLabel->Caption = "Скорость мала, невозможно рассчитать" + StateThread;
        CompleteTimeNumLabel->Caption = "Скорость мала, невозможно рассчитать" + StateThread;
       }
      }
      else
      {
       RemainedTimeNumLabel->Caption = "Прошло мало времени, невозможно рассчитать" + StateThread;
       CompleteTimeNumLabel->Caption = "Прошло мало времени, невозможно рассчитать" + StateThread;
       SpeedNumLabel->Caption = "Прошло мало времени, невозможно рассчитать" + StateThread;
      }
     }
     if(ProgressBar->Position != 100*DeletedAtom/Plane)
     {
      ProgressBar->Position = (TProgressRange)(100*DeletedAtom/Plane);
      ProgressBar->Hint  = IntToStr(ProgressBar->Position) + " %";
     }
	 //if(ProgressBar->Max != Plane) ProgressBar->Max = (TProgressRange)Plane;
    }
    else
    {
     StateThread = "Недоступно";
	 PlaneNumLabel->Caption = StateThread;
     N1ProbabilityNumLabel->Caption = StateThread;
     N2ProbabilityNumLabel->Caption = StateThread;
	 N3ProbabilityNumLabel->Caption = StateThread;

     StateNumLabel->Caption = "Процесс не создан или удалён";

	 DeletedAtomNumLabel->Caption = StateThread;
     DeletingLayersNumLabel->Caption = StateThread;
     DeletedLayersNumLabel->Caption = StateThread;
     N1NumLabel->Caption = StateThread;
     N2NumLabel->Caption = StateThread;
     N3NumLabel->Caption = StateThread;

     if(NumOfAtomsInLayerListBox->Items->Count != 0)
      NumOfAtomsInLayerListBox->Items->Clear();

     StartTimeNumLabel->Caption = StateThread;
     DissolutionTimeNumLabel->Caption = StateThread;
     RemainedTimeNumLabel->Caption = StateThread;
     CompleteTimeNumLabel->Caption = StateThread;
     SpeedNumLabel->Caption = StateThread;

     if(ProgressBar->Position != 0)
     {
      ProgressBar->Position = 0;
      ProgressBar->Hint  = StateThread;
     }
    }*/
}
//---------------------------------------------------------------------------
void __fastcall TMonitoringForm::FormShow(TObject *Sender)
{
	MonitoringTimer->Enabled = true;
    MonitoringTimerTimer(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMonitoringForm::FormHide(TObject *Sender)
{
	MonitoringTimer->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMonitoringForm::StatisticSpeedButtonClick(TObject *Sender)
{
	if(DissolutionThread != NULL)
	{
	 DissolutionThread->EnterCS();
	 N1N2N3QuantityDiagramForm->SetDataAndShow(DissolutionThread->GetStatistics());
	 DissolutionThread->LeaveCS();
	}

}
//---------------------------------------------------------------------------
void __fastcall TMonitoringForm::DistributionSpeedButtonClick(TObject *Sender)
{
	if(RNGsProbabilityDistributionForm == NULL)
	{
		RNGsProbabilityDistributionForm = new TRNGsProbabilityDistributionForm(this);
	}
	RNGsProbabilityDistributionForm->Show();
}
//---------------------------------------------------------------------------

