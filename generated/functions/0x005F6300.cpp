// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F6300 rf_ui_staticbox_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls gadget constructor,installs ui_staticbox vtable;constructs image records908/940 as separate self rings,empties inline label628. Does not initialize dimensions,crop,font,palette or text positions;initializer does. Returns this.
int __thiscall rf_ui_staticbox_construct(int this)
{
  rf_ui_gadget_construct((char *)this);
  *(_DWORD *)this = &ui_staticbox::`vftable';
  rf_ui_state_image_construct((_DWORD *)(this + 908));
  rf_ui_state_image_construct((_DWORD *)(this + 940));
  *(_BYTE *)(this + 628) = 0;
  return this;
}

