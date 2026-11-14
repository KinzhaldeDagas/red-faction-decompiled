// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453920 rf_endgame_panel_frame_event_scroll_and_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl LOWBYTE suppressInputAndScroll. Only byte0 first polls4477F0(callback453A80,EXTRA
// ignoredDWORD0), then scrollY6F158C=F32(currentY-frameFLOATseconds663EC8*DOUBLE20). Compute signed32 NEG of measured text-heightDWORD6F1594 beforeFILD (INT_MIN wraps). Only ORDERED
// scrollY<negated height requests446100(panel13,force0); equality/NaN does not. No own timer test on automatic scroll completion, and callback may already have requested same panel;
// returns ignored without re-gating.  Then for EVERY argument byte reset viewport full-screen571C20 and render453990. Unlike credits frame, viewport reset occurs AFTER input/scroll
// and possible panel request. Nonzero suppresses input/scroll only, not drawing. No transition-success check, close/free resources, mouse/music/pause state reset or rollback. Return
// full453990 EAX (last text-draw result/residue), not normalized panel success.
int __cdecl rf_endgame_panel_frame_event_scroll_and_render(char a1)
{
  if ( !a1 )
  {
    rf_ui_poll_and_dispatch_event(rf_endgame_event_or_elapsed_mouse_request_panel13);
    unk_6F158C = unk_6F158C - rf_frame_delta_seconds * 20.0;
    if ( unk_6F158C < (double)-dword_6F1594 )
      rf_ui_request_panel_immediate(13, 0);
  }
  rf_renderer_reset_viewport_full_screen();
  return rf_endgame_render_background_and_scrolled_centered_text();
}

