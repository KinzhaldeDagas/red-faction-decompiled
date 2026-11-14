// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449460 rf_screenshot_capture_pending_and_clear_flag
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments; pending BYTE6EDD39==0 returns EAX0 from initialMOVZX with no pause/capture calls. ANYnonzero pending first448B30
// increments pause depth, then rereads format BYTE6EDD40: EXACT1 calls570FF0(GLOBAL base path6EDC38,jpegFlag0,rawDWORD0x0098967F decimal9999999); every other byte usesjpegFlag1 with
// same path/sentinel. Capture result is void/ignored, no own image/file success test. XOR EDX,EDX/JNZ is never taken (no retry/spin). Then clear pending BYTE6EDD39 to0 regardless
// capture outcome and call448B20 once; full EAX is final decremented pause depth. Native calls balance one increment/decrement only on normal return, with no scope cleanup/rollback
// around delegated failure and no check whether flag/path changed during capture.
int rf_screenshot_capture_pending_and_clear_flag()
{
  int result; // eax

  result = unk_6EDD39;
  if ( unk_6EDD39 )
  {
    rf_game_clock_pause_depth_increment_adapter();
    if ( unk_6EDD40 == 1 )
      rf_renderer_capture_viewport_pixels_to_image((int)unk_6EDC38, 0, (int)byte_98967F);
    else
      rf_renderer_capture_viewport_pixels_to_image((int)unk_6EDC38, 1, (int)byte_98967F);
    unk_6EDD39 = 0;
    return rf_game_clock_pause_depth_decrement_adapter();
  }
  return result;
}

