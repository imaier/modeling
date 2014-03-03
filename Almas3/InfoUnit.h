//---------------------------------------------------------------------------
#ifndef InfoUnitH
#define InfoUnitH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TInfoForm : public TForm
{
__published:	// IDE-managed Components
	TMemo *GL_MODELVIEW_MATRIXMemo;
	TMemo *GL_PROJECTION_MATRIXMemo;
private:	// User declarations
public:		// User declarations
	void AddModelViewMatrix(float *Mtr);
	void AddProjectionMatrix(float *Mtr);
	__fastcall TInfoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TInfoForm *InfoForm;
//---------------------------------------------------------------------------
#endif
