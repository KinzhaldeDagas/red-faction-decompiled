// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F42E0 rf_ui_inputbox_initialize
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args owner,x,y,w,h,id,flags,raw base flag;gadget type6. Sets flags628,text632 empty,font1400=-1,allow888/reject1144 empty,max length1408=80,passwordBYTE1412=42,vertical justification1416=1,margin1420=2,textYOffset1424=0,cursorYOffset1428=1,cursorWidth1432=2,cursorHeight1436=h-2,palette1404=0x1CF7648. Does not reset callback1456,cursor animation1440 or bitmap handles;constructor handles those. No height/limit clamp;returns this.
int __thiscall rf_ui_inputbox_initialize(int this, int a2, int a3, int a4, int a5, int a6, int a7, int a8, char a9)
{
  rf_ui_gadget_initialize(this, a2, 6, a3, a4, a5, a6, a7, a9);
  *(_DWORD *)(this + 628) = a8;
  *(_BYTE *)(this + 632) = 0;
  *(_DWORD *)(this + 1400) = -1;
  *(_BYTE *)(this + 888) = 0;
  *(_BYTE *)(this + 1144) = 0;
  *(_DWORD *)(this + 1408) = 80;
  *(_BYTE *)(this + 1412) = 42;
  *(_DWORD *)(this + 1416) = 1;
  *(_DWORD *)(this + 1420) = 2;
  *(_DWORD *)(this + 1424) = 0;
  *(_DWORD *)(this + 1428) = 1;
  *(_DWORD *)(this + 1432) = 2;
  *(_DWORD *)(this + 1436) = a6 - 2;
  *(_DWORD *)(this + 1404) = byte_1CF7648;
  return this;
}

