//---------------------------------------------------------------------------
#ifndef PictUnitH
#define PictUnitH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "PropertyUnit.h"
//---------------------------------------------------------------------------
class TPictuteForm : public TForm
{
__published:	// IDE-managed Components
	TPaintBox *PictPaintBox;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormPaint(TObject *Sender);

	void __fastcall FormResize(TObject *Sender);
private:	// User declarations
	//Graphics::TBitmap* Bmp;
	TMaskVec m_vMask;
	int m_nWidth;
	int m_nHeight;
	bool Painted;
public:		// User declarations
	void __fastcall PaintMask(TMaskVec &vMask, int nWidth, int nHeight);
	__fastcall TPictuteForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
void __fastcall PaintPicture(TPaintBox* PB, TMaskVec &vMask, int nSizeX, int nSizeY);
//---------------------------------------------------------------------------
extern TPictuteForm *PictuteForm;
//---------------------------------------------------------------------------
#endif
