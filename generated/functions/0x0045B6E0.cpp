// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045B6E0 rf_multiplayer_level_scroll_up
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Decrement32-bit scroll6F2D04,if signed negative set0;no separate upper-bound clamp. Convert scroll to
// double,divide by signed(levelCount-visibleRows) with x87,round to float,pass to slider setter4719F0,then always play event46(0,0.0,1.0),including already at top. No denominator
// zero guard or short-list special case before floating division;setter applies its own range clamp. No current-row/selected-rotation mutation. Nominal int return sound delegate
// residue.
int rf_multiplayer_level_scroll_up()
{
  float v1; // [esp+8h] [ebp-10h]
  double v2; // [esp+10h] [ebp-8h]

  if ( (int)--dword_6F2D04 < 0 )
    dword_6F2D04 = 0;
  v2 = (double)(int)dword_6F2D04;
  v1 = v2 / (double)(rf_receiver_get_first_dword(&unk_6F2DC4) - unk_6F2CF0);
  rf_ui_slider_set_value_clamped(flt_6F3740, v1);
  return rf_gamesound_play_event(46, 0, 0.0, 1.0);
}

