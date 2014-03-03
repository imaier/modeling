//---------------------------------------------------------------------------

#ifndef QuantityByGroupeUnitH
#define QuantityByGroupeUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "ProbalityUnit.h"
#include <Buttons.hpp>
#include <vector>
//---------------------------------------------------------------------------
class TAtomCntBase
{
public:
	TAtomCntBase();
	TAtomCntBase(const AnsiString &strIdString);
	TAtomCntBase(const TAtomCntBase &R);

	virtual ~TAtomCntBase();

	int m_nLayer;//����� ����/�������
	TProbPovider m_vnSortAttom;//���������� ������ ������� �����
	int m_nFourLinkAtom;//��������� ������������� ������
	int m_nNoDelAtom;//����� �� ��������� ������
	int m_nDelAtom;//����� ������� ������
	int m_nAllAtom;//���������� ���������

	virtual void Zero();
	virtual void SetIdString(const AnsiString &strIdString);
	void Add(const TAtomCntBase& b);
};
//---------------------------------------------------------------------------
//���������� ������ � �������
class TAtomCntInSubLayer : public TAtomCntBase
{
public:
	TAtomCntInSubLayer();
	TAtomCntInSubLayer(const AnsiString &strIdString);
	TAtomCntInSubLayer(const TAtomCntInSubLayer &R);
};
typedef std::vector<TAtomCntInSubLayer> TAtomCntInSubLayerVector;
//---------------------------------------------------------------------------
//���������� ������ � ����
class TAtomCntInLayer : public TAtomCntBase
{
public:
	TAtomCntInLayer();
	TAtomCntInLayer(const AnsiString &strIdString);
	TAtomCntInLayer(const TAtomCntInLayer &R);
	virtual ~TAtomCntInLayer();

	TAtomCntInSubLayerVector m_SubLayers;//������� �������

	virtual void Zero();
	virtual void SetIdString(const AnsiString &strIdString);
	virtual void Add(const TAtomCntInLayer& b);
};
typedef std::vector<TAtomCntInLayer> TAtomCntInLayerVector;
//---------------------------------------------------------------------------
class TQuantityByGroupeForm : public TForm
{
__published:	// IDE-managed Components
    TListView *QuantityListView;
	TTreeView *LayerTreeView;
    TSplitter *LayerSplitter;
	TPanel *ToolPanel;
	TSpeedButton *ChartSpeedButton;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall LayerTreeViewChange(TObject *Sender, TTreeNode *Node);
	void __fastcall ChartSpeedButtonClick(TObject *Sender);
private:	// User declarations
	TAtomCntInLayerVector &m_vData;
	TAtomCntInLayer m_vAllLayer;
public:		// User declarations
    __fastcall TQuantityByGroupeForm(TAtomCntInLayerVector &vect, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQuantityByGroupeForm *QuantityByGroupeForm;
//---------------------------------------------------------------------------
#endif
