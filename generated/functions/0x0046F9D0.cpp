// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046F9D0 rf_demo_upsell_frame
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): One upsell frame: elapsed display deadline6F9110 calls advance46FA30; dispatches event(key handler46FA80,0); left-button PRESS-count also calls advance. Then signed
// index6F910C<3 renders current slide, otherwise requests immediate panel2 with(2,0). No lower-index bound; separate advance attempts in one frame are normally throttled by1000ms
// minimum deadline. No release/free here.
int rf_demo_upsell_frame()
{
  if ( rf_clock_deadline_has_elapsed_half_period(&dword_6F9110) )
    rf_demo_upsell_advance_if_ready();
  rf_ui_poll_and_dispatch_event(rf_demo_upsell_handle_key);
  if ( rf_mouse_button_has_press_count(0) )
    rf_demo_upsell_advance_if_ready();
  if ( unk_6F910C < 3 )
    return rf_demo_upsell_render();
  else
    return rf_ui_request_panel_immediate(2, 0);
}

