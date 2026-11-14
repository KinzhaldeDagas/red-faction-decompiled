// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EE4C0 rf_ui_slider_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls gadget constructor,installs ui_slider vtable;calls existing deadline constructor at+628,sets decrement pointer676=NULL,increment672=NULL,state632=0. Does not initialize position/range/thumb/orientation/palette. Returns this.
_DWORD *__thiscall rf_ui_slider_construct(_DWORD *this)
{
  rf_ui_gadget_construct((char *)this);
  *this = &ui_slider::`vftable';
  rf_clock_deadline_construct_invalid(this + 157);
  *(this + 169) = 0;
  *(this + 168) = 0;
  *(this + 158) = 0;
  return this;
}

