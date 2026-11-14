// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058ACB0 rf_mouse_get_button_press_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): When initialized returns raw snapshot press DWORD193A0B4+16*index, else0. No count clearing, normalization, bounds validation or lock.
int __cdecl rf_mouse_get_button_press_count(int a1)
{
  if ( byte_193A06D )
    return unk_193A0B4[4 * a1];
  else
    return 0;
}

