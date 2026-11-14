// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F6390 rf_ui_staticbox_initialize
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args owner,x,y,w,h,id,raw base flag;initializes gadget type3. Clears text628,sets font900=-1,image draw/crop dimensions884=w,888=h,crop offsets892=0/896=0,horizontal justify972=0(left),vertical976=1(center),explicit text x980/y984=-1,palette904=0x1CF762C. Does not reset image908/940 or free prior resources. Returns incidental palette store;no extent guard.
int __thiscall rf_ui_staticbox_initialize(int this, int a2, int a3, int a4, int a5, int a6, int a7, char a8)
{
  rf_ui_gadget_initialize(this, a2, 3, a3, a4, a5, a6, a7, a8);
  *(_BYTE *)(this + 628) = 0;
  *(_DWORD *)(this + 900) = -1;
  *(_DWORD *)(this + 884) = a5;
  *(_DWORD *)(this + 888) = a6;
  *(_DWORD *)(this + 892) = 0;
  *(_DWORD *)(this + 896) = 0;
  *(_DWORD *)(this + 972) = 0;
  *(_DWORD *)(this + 976) = 1;
  *(_DWORD *)(this + 980) = -1;
  *(_DWORD *)(this + 984) = -1;
  *(_DWORD *)(this + 904) = byte_1CF762C;
  return this;
}

