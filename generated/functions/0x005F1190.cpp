// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1190 rf_ui_base_get_position
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Writes raw local DWORD x+12 to first output,y+16 to second;returns second output pointer. No NULL check,parent accumulation or coordinate conversion.
_DWORD *__thiscall rf_ui_base_get_position(_DWORD *this, _DWORD *a2, _DWORD *a3)
{
  *a2 = *(this + 3);
  *a3 = *(this + 4);
  return a3;
}

