// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004549E0 rf_save_list_a_scroll_up_one
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments. Decrement offsetDWORD6F1F9C with32-bit wrap FIRST; JNS tests result sign, negative result stores0. INT_MIN wraps to positive INT_MAX
// and bypasses that lower clamp; no upper/count clamp. Next LIVE count==visible sets slider6F2200 valueFLOAT0. Otherwise reread count for signed wrapped denominator=count-visible;
// signed offset is FILD then explicitly stored as DOUBLE64 before getter, FDIVR numerator/denominator, quotient explicitly stored FLOAT32 and passed to4719F0 slider setter. No
// integer division or pre-division finite/positive-range validation; count and visible globals are not snapshotted across reads. Setter owns slider clamping.
// Always568050(event46,0,float0,float1), including no movement or exhausted range, forwards soundEAX. Does not change selected record or edit text.
int rf_save_list_a_scroll_up_one()
{
  float v1; // [esp+8h] [ebp-10h]
  double v2; // [esp+10h] [ebp-8h]

  if ( --dword_6F1F9C < 0 )
    dword_6F1F9C = 0;
  if ( rf_receiver_get_first_dword(dword_6F21AC) == unk_6F1F80 )
  {
    rf_ui_slider_set_value_clamped(unk_6F2200, 0.0);
  }
  else
  {
    v2 = (double)dword_6F1F9C;
    v1 = v2 / (double)(rf_receiver_get_first_dword(dword_6F21AC) - unk_6F1F80);
    rf_ui_slider_set_value_clamped(unk_6F2200, v1);
  }
  return rf_gamesound_play_event(46, 0, 0.0, 1.0);
}

