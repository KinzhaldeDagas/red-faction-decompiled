// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00447AE0 rf_ui_draw_cursor_and_present
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Reads BYTE704E83: EXACT1 returns full EAX1 immediately, without cursor or present calls. Every other value calls
// mouse-centering permission58AD80; only AL0 draws4478D0, then ALWAYS calls571C90 to present with full viewport and forwards that delegate's EAX. No window-active or
// console-visibility check here.
int rf_ui_draw_cursor_and_present()
{
  int result; // eax

  result = (unsigned __int8)byte_704E83;
  if ( byte_704E83 != 1 )
  {
    if ( !rf_mouse_get_centering_permission_byte() )
      rf_ui_draw_mouse_cursor();
    return rf_renderer_present_with_full_viewport();
  }
  return result;
}

