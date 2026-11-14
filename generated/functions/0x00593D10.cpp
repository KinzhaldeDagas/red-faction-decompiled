// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593D10 rf_window_get_main_hwnd
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Returns HWND stored at1BC212C. No validity test, initialization, reference-count operation or state mutation. Mouse client/screen conversion and DirectInput cooperation use this handle.
HWND __cdecl rf_window_get_main_hwnd()
{
  return hWnd;
}

