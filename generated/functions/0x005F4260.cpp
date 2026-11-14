// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F4260 rf_ui_inputbox_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls gadget constructor,installs ui_inputbox vtable;empties text632,allow888,reject1144;callback1456=NULL,cursor animation1440=NULL,bitmap handles1444/1448/1452=-1. Does not initialize flags628,font1400,palette1404 or geometry/margins/limits;initializer does. Returns this.
int __thiscall rf_ui_inputbox_construct(int this)
{
  rf_ui_gadget_construct((char *)this);
  *(_DWORD *)this = &ui_inputbox::`vftable';
  *(_BYTE *)(this + 632) = 0;
  *(_BYTE *)(this + 888) = 0;
  *(_BYTE *)(this + 1144) = 0;
  *(_DWORD *)(this + 1456) = 0;
  *(_DWORD *)(this + 1440) = 0;
  *(_DWORD *)(this + 1444) = -1;
  *(_DWORD *)(this + 1448) = -1;
  *(_DWORD *)(this + 1452) = -1;
  return this;
}

