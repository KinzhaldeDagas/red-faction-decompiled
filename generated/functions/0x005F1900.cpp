// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1900 rf_ui_state_image_destruct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls0x5F1950 reset/release;no operator delete this,ring unlink or bitmap release. Returns reset result.
_DWORD *__thiscall rf_ui_state_image_destruct(_DWORD *this)
{
  return rf_ui_state_image_reset(this);
}

