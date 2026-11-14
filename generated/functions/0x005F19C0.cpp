// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F19C0 rf_ui_state_image_set_bitmap
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls state-image reset0x5F1950 (may destroy owned animation),stores bitmap handle+4=input,mode DWORD+0=1;returns this. No bitmap release/load/validation;does not alter ring link+24.
_DWORD *__thiscall rf_ui_state_image_set_bitmap(_DWORD *this, int a2)
{
  rf_ui_state_image_reset(this);
  *(this + 1) = a2;
  *this = 1;
  return this;
}

