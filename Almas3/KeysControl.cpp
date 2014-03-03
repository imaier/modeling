//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "KeysControl.h"
//---------------------------------------------------------------------------
TKeysState::TKeysState(void)
{
	KeysList = new TList;
}
TKeysState::~TKeysState(void)
{
	delete KeysList;
}
TKeyState* __fastcall TKeysState::GetKey(int i)
{
	return (TKeyState*)KeysList->Items[i];
}
int __fastcall TKeysState::GetPressingKeyCount(void)
{
	return KeysList->Count;
}
int __fastcall TKeysState::ExistKey(unsigned short Key)
{
	int i;
    for(i=0; i < KeysList->Count; i++)
     if (((TKeyState*)KeysList->Items[i])->Key == Key)
      return i;
    return -1;
}
void __fastcall TKeysState::PressKey(unsigned short Key, Classes::TShiftState Shift)
{
	if(ExistKey(Key) == -1)
    {
     int i = KeysList->Add(new TKeyState);
     ((TKeyState*)KeysList->Items[i])->Key = Key;
     ((TKeyState*)KeysList->Items[i])->Shift = Shift;
     ((TKeyState*)KeysList->Items[i])->TimePress = ((TKeyState*)KeysList->Items[i])->TimePress.CurrentDateTime();
     //Key = (unsigned short)i;
    }
}
void __fastcall TKeysState::UnPressKey(unsigned short Key, Classes::TShiftState Shift)
{
	int i = ExistKey(Key);
	if(i != -1)
    {
     delete KeysList->Items[i];
     KeysList->Delete(i);
    }
}
//---------------------------------------------------------------------------
