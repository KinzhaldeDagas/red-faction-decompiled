// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00452E10 rf_credits_panel_frame_input_scroll_render_and_exit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl LOWBYTE suppressInputAndScroll, void/incidental registers. ALWAYS first571C20 resets
// full-screen viewport. Only argumentBYTE==0 polls4477F0(callback453280,EXTRA ignoredDWORD0), then4533F0 mouse press check, then
// scrollY6EFEB4=F32(oldY-frameFLOATseconds663EC8*DOUBLE40). Preserve event callback mutations BEFORE mouse and baseline scroll; multiple drained events can update scroll separately.
// Compute signed32 NEG of measured heightDWORD6EFEBC BEFORE FILD; INT_MIN negation wraps. Only ORDERED scrollY<that signed threshold resets scrollY toF32(SIGNED physical screen
// height570F70). Equality or NaN does not reset; initial Y used viewport height but wrap uses physical height.  EVERY argument byte, including nonzero, then calls452ED0 renderer,
// which still advances fade state. Afterwards if exitDWORD6F1504 ANYnonzero AND fade-outBYTE6EFEB0==0, call58ADA0(disabled1), then CURRENT BYTE6EDD38 ANYnonzero
// requests446100(panel2,forceBYTE0); zero instead4464A0 requests stack pop. Results ignored, no exit-latch reset or request-success check. Thus suppressed-input frames still
// render/fade and can issue exit requests; render clearing fade-out can enable same-frame exit. Does not reset viewport again after drawing, close/free bitmap/music or normalize
// return.
void __cdecl rf_credits_panel_frame_input_scroll_render_and_exit(char a1)
{
  rf_renderer_reset_viewport_full_screen();
  if ( !a1 )
  {
    rf_ui_poll_and_dispatch_event(rf_credits_event_exit_or_adjust_scroll);
    rf_credits_mouse_press_request_fade_out();
    unk_6EFEB4 = unk_6EFEB4 - rf_frame_delta_seconds * 40.0;
    if ( unk_6EFEB4 < (double)-dword_6EFEBC[0] )
      unk_6EFEB4 = (float)rf_renderer_get_physical_screen_height();
  }
  rf_credits_render_bitmap_fade_and_newline_text();
  if ( unk_6F1504 && !unk_6EFEB0 )
  {
    rf_mouse_set_centering_disabled(1);
    if ( unk_6EDD38 )
      rf_ui_request_panel_immediate(2, 0);
    else
      rf_ui_request_panel_stack_pop();
  }
}

