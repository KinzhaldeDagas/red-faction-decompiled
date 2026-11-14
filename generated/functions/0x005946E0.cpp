// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005946E0 rf_window_post_destroy_message
// UNREALRED VERIFIED [system-progress-20261028]: Calls PostMessageA(HWND0x1BC212C,WM_DESTROY=2,0,0),returns BOOL. Procedure0x594370 handles it by setting quit flag; this helper does not directly call DestroyWindow or close a handle.
BOOL rf_window_post_destroy_message()
{
  return PostMessageA(hWnd, 2u, 0, 0);
}

