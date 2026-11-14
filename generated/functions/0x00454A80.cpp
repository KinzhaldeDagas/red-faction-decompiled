// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00454A80 rf_save_list_a_scroll_down_one
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments. Increment offsetDWORD6F1F9C with32-bit wrap FIRST. Compare signed offset against wrapped LIVE count(array6F21AC)-visibleDWORD6F1F80;
// if offset>=range reread count and store signed max(0,count-visible). When that branch is skipped, negative offset from arbitrary input/overflow is NOT repaired. Next LIVE
// count==visible sets slider6F2200 valueFLOAT0. Otherwise reread count for signed wrapped denominator=count-visible; signed offset is FILD then explicitly stored as DOUBLE64 before
// getter, FDIVR numerator/denominator, quotient explicitly stored FLOAT32 and passed to4719F0 slider setter. No integer division or pre-division finite/positive-range validation;
// count and visible globals are not snapshotted across reads. Setter owns slider clamping. Always568050(event46,0,float0,float1), including no movement or exhausted range, forwards
// soundEAX. Does not change selected record or edit text.
int rf_save_list_a_scroll_down_one()
{
  int first_dword; // eax
  float v2; // [esp+8h] [ebp-10h]
  double v3; // [esp+10h] [ebp-8h]

  ++dword_6F1F9C;
  if ( dword_6F1F9C >= rf_receiver_get_first_dword(dword_6F21AC) - unk_6F1F80 )
  {
    first_dword = rf_receiver_get_first_dword(dword_6F21AC);
    dword_6F1F9C = rf_int_max(0, first_dword - unk_6F1F80);
  }
  if ( rf_receiver_get_first_dword(dword_6F21AC) == unk_6F1F80 )
  {
    rf_ui_slider_set_value_clamped(unk_6F2200, 0.0);
  }
  else
  {
    v3 = (double)dword_6F1F9C;
    v2 = v3 / (double)(rf_receiver_get_first_dword(dword_6F21AC) - unk_6F1F80);
    rf_ui_slider_set_value_clamped(unk_6F2200, v2);
  }
  return rf_gamesound_play_event(46, 0, 0.0, 1.0);
}

