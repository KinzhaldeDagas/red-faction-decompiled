// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00455F90 rf_ui_button_clear_focus
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall receiver ECX, no stack arguments. Stores exactly BYTE[receiver+8]=0 and returns receiver in full EAX. No null/type guard, other field stores,
// callbacks, redraw or focus transfer. Existing focus-byte role retained; whole button is not reset.
_BYTE *__thiscall rf_ui_button_clear_focus(_BYTE *this)
{
  *(this + 8) = 0;
  return this;
}

