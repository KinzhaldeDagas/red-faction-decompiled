// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B11A0 rf_ui_radio_button_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls checkbox constructor0x5F2180,then installs ui_radio_button vtable. Inherits visual908=0,label640empty;group initialization separate. Returns this;no allocation or parent link here.
_DWORD *__thiscall rf_ui_radio_button_construct(_DWORD *this)
{
  rf_ui_checkbox_construct((int)this);
  *this = &ui_radio_button::`vftable';
  return this;
}

