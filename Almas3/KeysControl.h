//---------------------------------------------------------------------------
#ifndef KeysControlH
#define KeysControlH
//---------------------------------------------------------------------------
class TKeyState
{
public:
	unsigned short Key;
    Classes::TShiftState Shift;
    TDateTime TimePress;
};
//---------------------------------------------------------------------------
class TKeysState
{
private:
	TList *KeysList;
    TKeyState* __fastcall GetKey(int i);
    int __fastcall GetPressingKeyCount(void);
public:

    int __fastcall ExistKey(unsigned short Key);
    void __fastcall PressKey(unsigned short Key,  Classes::TShiftState Shift);
    void __fastcall UnPressKey(unsigned short Key,  Classes::TShiftState Shift);
    int a, b[4], c;
    //__property TKeyState Key[int i] = {read = *(TKeyState*)KeysList->Items[i]};
    __property TKeyState* Key[int i] = {read = GetKey};
	__property int PressingKeyCount = {read=GetPressingKeyCount };

    TKeysState(void);
    ~TKeysState(void);
};
//---------------------------------------------------------------------------
#endif
