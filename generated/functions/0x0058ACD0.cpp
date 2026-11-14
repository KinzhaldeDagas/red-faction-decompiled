// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058ACD0 rf_mouse_get_button_release_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Recovered cdecl button index. Returns raw snapshot release DWORD193A0B8+16*index when initialized, else0. No counter consumption, bounds validation or lock.
int __cdecl rf_mouse_get_button_release_count(int button_index)
{
  if ( byte_193A06D )
    return dword_193A0B8[4 * button_index];
  else
    return 0;
}

