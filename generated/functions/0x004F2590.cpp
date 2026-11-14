// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F2590 rf_application_run_frame_and_test_exit_panel
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): No arguments, returns canonical EAX BOOL determined solely by panel ID returned earlier from transition manager4461C0==17. Order: reset full-screen viewport,update frame clock,448A10,GeoMod queue update(frame delta),4461C0(capture result),449460,quicksave notification,console update/render(zero-extended dedicated byte), then if dedicated byte NONZERO and global1BC213C nonzero request panel17 with0. This later request does NOT replace captured return ID this frame. Services audio fades,reserved renderer no-op5C1C80,quick actions. If captured ID is5/10/34, skips final overlay/present block. Otherwise queries4461B0; result5/10 draws backing(1,1.0) and
// invokes4703F0(ECX=88E490), then ALWAYS447AE0. Finishes remaining updates even after captured exit ID17. Existing helper receiver artifacts do not imply an incoming frame context.
BOOL rf_application_run_frame_and_test_exit_panel()
{
  int v1; // [esp+4h] [ebp-Ch]
  int v2; // [esp+8h] [ebp-8h]

  rf_renderer_reset_viewport_full_screen();
  rf_frame_clock_update_delta_and_history();
  rf_multiplayer_tick_transfer_and_admitted_level_update();
  rf_geomod_execution_queue_update(rf_frame_delta_seconds);
  v2 = rf_ui_process_panel_transition_and_frame();
  rf_screenshot_capture_pending_and_clear_flag();
  rf_quicksave_notification_update();
  rf_console_update_and_render(byte_704E83);
  if ( byte_704E83 && unk_1BC213C )
    rf_ui_request_panel_immediate(17, 0);
  rf_sound_backend_service_fades_adapter();
  rf_renderer_reserved_noop_5c1c80();
  rf_quick_actions_process_pending();
  if ( v2 != 5 && v2 != 10 && v2 != 34 )
  {
    v1 = rf_ui_pending_panel_id_get();
    if ( v1 == 5 || v1 == 10 )
    {
      rf_pause_overlay_backing_render(1, 1.0);
      rf_ui_label_render((int)dword_88E490);
    }
    rf_ui_draw_cursor_and_present();
  }
  return v2 == 17;
}

