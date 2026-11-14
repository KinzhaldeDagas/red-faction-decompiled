// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F0120 rf_ui_button_get_flags
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Returns raw DWORD button flags+628. No mutation or normalization.
int __thiscall rf_ui_button_get_flags(_DWORD *this)
{
  return *(this + 157);
}

