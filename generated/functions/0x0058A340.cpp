// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A340 rf_mouse_warp_cursor_client_if_window_active
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): If window active byte from593D20 is nonzero, converts supplied client XY to screen coordinates using main HWND593D10 and calls SetCursorPos. Inactive returns0. No mouse-initialized guard, cached-position update or coordinate clamp; ClientToScreen status unchecked. Return is setter BOOL or0.
int __cdecl rf_mouse_warp_cursor_client_if_window_active(LONG a1, LONG a2)
{
  int result; // eax
  HWND main_hwnd; // eax
  struct tagPOINT Point; // [esp+0h] [ebp-8h] BYREF

  result = (unsigned __int8)rf_window_get_active_byte();
  if ( (_BYTE)result )
  {
    Point.x = a1;
    Point.y = a2;
    main_hwnd = rf_window_get_main_hwnd();
    ClientToScreen(main_hwnd, &Point);
    return SetCursorPos(Point.x, Point.y);
  }
  return result;
}

