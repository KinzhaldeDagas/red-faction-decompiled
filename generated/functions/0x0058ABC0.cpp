// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058ABC0 rf_mouse_set_cached_xy_or_warp_cursor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Cursor mode663F4C: if requested X or Y differs from cached XY, calls active-window cursor warp helper; does NOT update cached XY here. Otherwise no warp. DirectInput mode directly stores cached X/Y and returns X. No initialized guard, clamp, lock, baseline/delta update or uniform status return.
int __cdecl rf_mouse_set_cached_xy_or_warp_cursor(LONG a1, LONG a2)
{
  int result; // eax

  if ( dword_663F4C )
  {
    if ( a1 != dword_193A060 )
      return rf_mouse_warp_cursor_client_if_window_active(a1, a2);
    result = a2;
    if ( a2 != dword_193A040 )
      return rf_mouse_warp_cursor_client_if_window_active(a1, a2);
  }
  else
  {
    dword_193A060 = a1;
    dword_193A040 = a2;
    return a1;
  }
  return result;
}

