// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FCD0 rf_ui_v_panel_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall ECX=this. Calls base v_control constructor46FBF0, installs v_panel vtable, sets bitmap handle DWORD+40=-1 and returns this. Does not load
// resources or initialize further derived fields.
_DWORD *__thiscall rf_ui_v_panel_construct(_DWORD *this)
{
  rf_ui_control_construct(this);
  *this = &v_panel::`vftable';
  *(this + 10) = -1;
  return this;
}

