// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F2180 rf_ui_checkbox_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls gadget constructor,installs ui_checkbox vtable,sets visual state DWORD908=0,label BYTE640=0. Does not initialize checked628,box dimensions632/636,font896,offsets900/904,palette912 or bitmap handles916..928;initializer does. Returns this.
int __thiscall rf_ui_checkbox_construct(int this)
{
  rf_ui_gadget_construct((char *)this);
  *(_DWORD *)this = &ui_checkbox::`vftable';
  *(_DWORD *)(this + 908) = 0;
  *(_BYTE *)(this + 640) = 0;
  return this;
}

