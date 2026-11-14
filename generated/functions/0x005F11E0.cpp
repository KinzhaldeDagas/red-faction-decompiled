// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F11E0 rf_ui_base_get_size
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Writes DWORD width+20,height+24 to two output pointers;returns second output pointer. No NULL check or clamping.
_DWORD *__thiscall rf_ui_base_get_size(_DWORD *this, _DWORD *a2, _DWORD *a3)
{
  *a2 = *(this + 5);
  *a3 = *(this + 6);
  return a3;
}

