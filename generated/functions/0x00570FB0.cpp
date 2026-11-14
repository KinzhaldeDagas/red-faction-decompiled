// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570FB0 rf_renderer_set_backend_window_and_reset_full_viewport
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): cdecl(HWND). Calls no-op5738C0. If backend selector==102,calls5C1F10(window) to record client rectangle/apply device viewport,then UNCONDITIONALLY resets viewport full PHYSICAL screen via571C20 and returns that incidental result. Other selectors return selector without window work. Does not update physical screen width/height or recreate backend;no HWND/device/API failure validation.
int __cdecl rf_renderer_set_backend_window_and_reset_full_viewport(HWND window)
{
  int result; // eax

  rf_renderer_reserved_noop_5738C0();
  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
  {
    rf_d3d8_set_window_client_rectangle_and_viewport(window);
    return rf_renderer_reset_viewport_full_screen();
  }
  return result;
}

