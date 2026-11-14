// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F24A0 rf_ui_checkbox_set_checked_raw
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Stores supplied BYTE into checked+628 without normalization. Returns this;no event,visual-state update or eligibility check.
_BYTE *__thiscall rf_ui_checkbox_set_checked_raw(_BYTE *this, char a2)
{
  *(this + 628) = a2;
  return this;
}

