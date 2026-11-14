// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F24C0 rf_ui_checkbox_get_checked_raw
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Returns raw checked BYTE+628 in AL;not normalized. Upper EAX incidental;no side effects.
char __thiscall rf_ui_checkbox_get_checked_raw(_BYTE *this)
{
  return *(this + 628);
}

