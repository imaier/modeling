//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma warn -pck

#include "QuantityByGroupeUnit.h"
#include "DistributionUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TAtomCntBase::TAtomCntBase()
{
	Zero();
}
//---------------------------------------------------------------------------
TAtomCntBase::TAtomCntBase(const AnsiString &strIdString)
{
	SetIdString(strIdString);
}
//---------------------------------------------------------------------------
TAtomCntBase::TAtomCntBase(const TAtomCntBase &R)
{
	IBaseProbSet *pPs = R.m_vnSortAttom.GetInterface();
	if(pPs==NULL)
	{
		m_vnSortAttom.ClearInterface();
	}
	else
	{
		SetIdString(pPs->GetGlobalData().GetProbSetIdString());
	}
	Add(R);
	m_nLayer = R.m_nLayer;
}
//---------------------------------------------------------------------------
TAtomCntBase::~TAtomCntBase()
{
	m_vnSortAttom.ClearInterface();
}
//---------------------------------------------------------------------------
void TAtomCntBase::SetIdString(const AnsiString &strIdString)
{
	m_vnSortAttom.ClearInterface();
	m_vnSortAttom.CreateInterfaceByIdString(strIdString);
	Zero();
}
//---------------------------------------------------------------------------
void TAtomCntBase::Zero()
{
	int i;
	m_nLayer = 0;
	IBaseProbSet *pSelfPS = m_vnSortAttom.GetInterface();
	if(pSelfPS != NULL)
	{
	 int nSelfCnt = pSelfPS->GetGlobalData().GetAllNumProbality();
	 for(i=0; i<nSelfCnt; i++)
	 {
	  pSelfPS->SetProbValue(i, 0);
	 }
	}

	m_nFourLinkAtom = 0;
	m_nNoDelAtom = 0;
	m_nDelAtom = 0;
	m_nAllAtom = 0;
}
//---------------------------------------------------------------------------
void TAtomCntBase::Add(const TAtomCntBase& b)
{
	IBaseProbSet *pbPS = b.m_vnSortAttom.GetInterface();
	if(pbPS != NULL)
	{
	 IBaseProbSet *pSelfPS = m_vnSortAttom.GetInterface();
	 if(pSelfPS != NULL)
	 {
	  if(pSelfPS->GetGlobalData().GetProbSetIdString() !=
			pbPS->GetGlobalData().GetProbSetIdString() )
	  {
	   SetIdString(pbPS->GetGlobalData().GetProbSetIdString());
	  }
	 }
	 else
	 {
	  SetIdString(pbPS->GetGlobalData().GetProbSetIdString());
	 }
	 pSelfPS = m_vnSortAttom.GetInterface();
	 int nSelfCnt = pSelfPS->GetGlobalData().GetAllNumProbality();
	 double dProbVal;
	 int i;
	 for(i=0; i<nSelfCnt; i++)
	 {
	  dProbVal = pbPS->GetProbValue(i);
	  dProbVal += pSelfPS->GetProbValue(i);
	  pSelfPS->SetProbValue(i, dProbVal);
	 }
	 m_nFourLinkAtom += b.m_nFourLinkAtom;
	 m_nNoDelAtom += b.m_nNoDelAtom;
	 m_nDelAtom += b.m_nDelAtom;
	 m_nAllAtom += b.m_nAllAtom;
	}
}
//---------------------------------------------------------------------------
TAtomCntInSubLayer::TAtomCntInSubLayer()
:TAtomCntBase()
{
}
//---------------------------------------------------------------------------
TAtomCntInSubLayer::TAtomCntInSubLayer(const AnsiString &strIdString)
:TAtomCntBase(strIdString)
{
}
//---------------------------------------------------------------------------
TAtomCntInSubLayer::TAtomCntInSubLayer(const TAtomCntInSubLayer &R)
:TAtomCntBase(R)
{
}
//---------------------------------------------------------------------------
TAtomCntInLayer::TAtomCntInLayer()
:TAtomCntBase()
{
}
//---------------------------------------------------------------------------
TAtomCntInLayer::TAtomCntInLayer(const AnsiString &strIdString)
:TAtomCntBase(strIdString)
{

}
//---------------------------------------------------------------------------
TAtomCntInLayer::TAtomCntInLayer(const TAtomCntInLayer &R)
:TAtomCntBase(R)
{
	IBaseProbSet *pPs = R.m_vnSortAttom.GetInterface();
	if(pPs==NULL)
	{
		m_vnSortAttom.ClearInterface();
	}
	else
	{
		SetIdString(pPs->GetGlobalData().GetProbSetIdString());
	}
	Add(R);
	m_nLayer = R.m_nLayer;
	m_SubLayers = R.m_SubLayers;
}
//---------------------------------------------------------------------------
TAtomCntInLayer::~TAtomCntInLayer()
{
	m_SubLayers.clear();
}
//---------------------------------------------------------------------------
void TAtomCntInLayer::SetIdString(const AnsiString &strIdString)
{
	UINT j;
	for(j=0; j < m_SubLayers.size() ; j++)
	{
	 m_SubLayers[j].m_vnSortAttom.ClearInterface();
	 m_SubLayers[j].m_vnSortAttom.CreateInterfaceByIdString(strIdString);
	}

	TAtomCntBase::SetIdString(strIdString);
}
//---------------------------------------------------------------------------
void TAtomCntInLayer::Zero()
{
	TAtomCntBase::Zero();
	UINT j;
	for(j=0; j < m_SubLayers.size() ; j++)
	{
	 m_SubLayers[j].Zero();
	}
}
//---------------------------------------------------------------------------
void TAtomCntInLayer::Add(const TAtomCntInLayer& b)
{
	TAtomCntBase::Add(b);

	IBaseProbSet *pSelfPS = m_vnSortAttom.GetInterface();
	IBaseProbSet *pbPS = b.m_vnSortAttom.GetInterface();
	if(pbPS != NULL && pSelfPS != NULL)
	{
	 UINT nSubLayersSize = m_SubLayers.size();
	 UINT nB_SubLayersSize = b.m_SubLayers.size();
	 UINT nMaxSize=max(nSubLayersSize, nB_SubLayersSize);

	 //добавить подслои
	 AnsiString IdStr;
	 IdStr = pSelfPS->GetGlobalData().GetProbSetIdString();
	 TAtomCntInSubLayer zeroSubLayer(IdStr);
	 const TAtomCntInSubLayer *pBSubLayer = NULL;
	 UINT i;
	 for(i=0; i<nMaxSize; i++)
	 {
		if(i>=nSubLayersSize)
		{
		 m_SubLayers.push_back(TAtomCntInSubLayer(IdStr));
		}

		TAtomCntInSubLayer& SelfSubLayer = m_SubLayers[i];

		if(i < nB_SubLayersSize)
		{
		 pBSubLayer = &(b.m_SubLayers[i]);
		}
		else
		{
		 pBSubLayer = &zeroSubLayer;
		}

		SelfSubLayer.Add(*pBSubLayer);
	 }
	}
}
//---------------------------------------------------------------------------

TQuantityByGroupeForm *QuantityByGroupeForm;
//---------------------------------------------------------------------------
__fastcall TQuantityByGroupeForm::TQuantityByGroupeForm(TAtomCntInLayerVector &vect,TComponent* Owner)
	: TForm(Owner), m_vData(vect)
{
}
//---------------------------------------------------------------------------
void __fastcall TQuantityByGroupeForm::FormShow(TObject *Sender)
{
	TTreeNodes *pItems = LayerTreeView->Items;
	TTreeNode *pNode = NULL;
	TTreeNode *pSubNode = NULL;
	TTreeNode *pRootNode = NULL;
	pItems->Clear();
	m_vAllLayer.Zero();
	UINT i, j;
	for(i=0; i < m_vData.size(); i++)
	{
		TAtomCntInLayer &Layer = m_vData[i];
		m_vAllLayer.Add(Layer);
	}
	pNode = pItems->Add(NULL, "Все слои");
	pNode->Data = static_cast<TAtomCntBase*>(&m_vAllLayer);
	pRootNode = pNode;

	for(j=0; j < m_vAllLayer.m_SubLayers.size(); j++)
	{
	 TAtomCntInSubLayer &SubLayer = m_vAllLayer.m_SubLayers[j];
	 SubLayer.m_nLayer = j;
	 pSubNode = pItems->Add(pRootNode, "Суммарный подслой №" + IntToStr(SubLayer.m_nLayer+1));
	 pSubNode->Data = static_cast<TAtomCntBase*>(&SubLayer);
	}

	for(i=0; i < m_vData.size(); i++)
	{
		TAtomCntInLayer &Layer = m_vData[i];
		pNode = pItems->AddChild(pRootNode, "Cлой №" + IntToStr(Layer.m_nLayer+1));
		pNode->Data = static_cast<TAtomCntBase*>(&Layer);
		for(j=0; j < Layer.m_SubLayers.size(); j++)
		{
			TAtomCntInSubLayer &SubLayer = Layer.m_SubLayers[j];
			pSubNode = pItems->AddChild(pNode, "Подслой №" + IntToStr(Layer.m_nLayer+1) + "." + IntToStr(SubLayer.m_nLayer+1));
			pSubNode->Data = static_cast<TAtomCntBase*>(&SubLayer);
		}
	}
	LayerTreeViewChange(Sender,pRootNode);

	LayerTreeView->FullExpand();
	//LayerTreeView->AutoExpand = true;
}
//---------------------------------------------------------------------------
void __fastcall TQuantityByGroupeForm::LayerTreeViewChange(TObject *Sender,
	  TTreeNode *Node)
{
	TAtomCntInLayer &Layer = *((TAtomCntInLayer*)Node->Data);
	TListItems *pItems = QuantityListView->Items;
	int SelItemIndex = QuantityListView->ItemIndex;
	int TopItemIndex = QuantityListView->TopItem->Index;
	TPoint TopItemPosition;
	TopItemPosition = QuantityListView->TopItem->Position;
	TListItem *pItem;
	int i, indx;

	pItems->BeginUpdate();

	pItems->Clear();
	IBaseProbSet *pPS = Layer.m_vnSortAttom.GetInterface();
	if(pPS != NULL)
	{
	 int nCnt = pPS->GetGlobalData().GetAllNumProbality();
	 int nVal;
	 for(i=0; i < nCnt; i++)
	 {
		pItem = pItems->Add();
		pItem->Caption = pPS->GetGlobalData().GetProbName(i);
		nVal = (int)pPS->GetProbValue(i);
		pItem->SubItems->Add(IntToStr(nVal));
	 }
	}

	pItem = pItems->Add();
	pItem->Caption = "Четырёхсвязные атомы";
	pItem->SubItems->Add(IntToStr(Layer.m_nFourLinkAtom));

	pItem = pItems->Add();
	pItem->Caption = "Не удаляемые атомы";
	pItem->SubItems->Add(IntToStr(Layer.m_nNoDelAtom));

	pItem = pItems->Add();
	pItem->Caption = "Удалённые атомы";
	pItem->SubItems->Add(IntToStr(Layer.m_nDelAtom));

	pItem = pItems->Add();
	pItem->Caption = "Количество атомомест";
	pItem->SubItems->Add(IntToStr(Layer.m_nAllAtom));


	pItems->EndUpdate();

	//QuantityListView->Repaint();
	TPoint TopItemPosition2 = QuantityListView->Items->Item[TopItemIndex]->Position;
	int DX = TopItemPosition2.x - TopItemPosition.x;
	int DY = TopItemPosition2.y - TopItemPosition.y;
	QuantityListView->Scroll(DX, DY);
	QuantityListView->ItemIndex = SelItemIndex;

	//QuantityListView->Items->Item[TopItemIndex]->Position = TopItemPosition;
	//QuantityListView->Scroll(0, QuantityListView->Items->Item[TopItemIndex]->Position.y - TopItemPosition.y);

	//QuantityListView->Invalidate();

}
//---------------------------------------------------------------------------
void __fastcall TQuantityByGroupeForm::ChartSpeedButtonClick(TObject *Sender)
{
	TTreeNode *pNode = LayerTreeView->Selected;

	if(pNode == NULL)
	{
		pNode = LayerTreeView->Items->GetFirstNode();
	}

	if(pNode!=NULL)
	{
		if(pNode->Data!=NULL)
		{
			TAtomCntBase &Layer = *((TAtomCntInLayer*)pNode->Data);

			DistributionForm->SetDataAndShow(Layer, pNode->Text);
		}
	}
}
//---------------------------------------------------------------------------

