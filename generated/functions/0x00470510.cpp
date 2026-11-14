// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00470510 rf_ui_v_edit_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall ECX=this. Calls v_label constructor46FE40, installs v_edit vtable, clears ONLY first byte of inline text+64, returns this. Does not clear
// remaining31 text bytes or initialize width limit+96/font+100.
int __thiscall rf_ui_v_edit_construct(int this)
{
  rf_ui_v_label_construct((_DWORD *)this);
  *(_DWORD *)this = &v_edit::`vftable';
  *(_BYTE *)(this + 64) = 0;
  return this;
}

