//---------------------------------------------------------------------------

#ifndef ProgressUnitH
#define ProgressUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TProgressRec
{
public:
	TProgressRec();
	void Init();
	bool operator==(const TProgressRec& r) const;
	TProgressRec& operator=(const TProgressRec& r);
	AnsiString m_strOperation;
	AnsiString m_strState;
	int m_nMax;
	int m_nCurr;
};

class TProgressObserver
{
};

class TProgressActon
{
public:
	void SetObserver(const TProgressObserver& obs);
};


//---------------------------------------------------------------------------
class TProgressForm : public TForm
{
__published:	// IDE-managed Components
	TProgressBar *OperationProgressBar;
	TLabel *OperationLabel;
	TLabel *StateNameLabel;
	TBitBtn *CancelBitBtn;
	TLabel *StateLabel;
	void __fastcall CancelBitBtnClick(TObject *Sender);
private:	// User declarations

	TProgressRec m_ProgressRec;
public:		// User declarations

	void PostProgress(const TProgressRec& r);

	__fastcall TProgressForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
class TProgressProvider
{
protected:
public:
	TProgressProvider();
	virtual ~TProgressProvider();

	static TProgressProvider& GetInstanse();

	void PostProgress(const TProgressRec& r);
	void FinishProgress();

	bool IsStopped();
	void SetStopped();
private:

	TProgressForm *m_pForm;
	bool m_bStopped;
};
//---------------------------------------------------------------------------
//extern PACKAGE TProgressForm *ProgressForm;
//---------------------------------------------------------------------------
#endif
