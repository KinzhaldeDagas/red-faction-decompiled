// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458100 rf_frontend_help_frame
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one DWORD LOWBYTE option. Only byte0 calls4477F0(callback458130,extraDWORD0); other bytes bypass input polling. Always calls458290 help render and
// forwards its EAX. No own state reset, page normalization, frame-option propagation or modal/interaction guard.
int __cdecl rf_frontend_help_frame(char a1)
{
  if ( !a1 )
    rf_ui_poll_and_dispatch_event((int (__cdecl *)(int))rf_frontend_help_handle_input_event);
  return rf_frontend_help_render_selected_page();
}

