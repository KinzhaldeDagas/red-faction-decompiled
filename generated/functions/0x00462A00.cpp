// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462A00 rf_browser_scroll_up
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Decrement scroll6F52E4;only signed negative clamps0. If visibleCount EXACTLY equals visibleRows,set slider6F53F0 tofloat0;otherwise signed
// scroll/(visibleCount-visibleRows) via x87,round binary32,delegate slider setter. Equality avoids zero denominator;negative difference still divides and is not independently
// rejected. Always sound46(0,0.0,1.0),even at unchanged limit. No selected-row change,query,registry or list rebuild;return sound residue. Native integer arithmetic32-bit.
int rf_browser_scroll_up()
{
  float v1; // [esp+8h] [ebp-8h]

  if ( --dword_6F52E4 < 0 )
    dword_6F52E4 = 0;
  if ( MEMORY[0x6F5088] == unk_6F508C )
  {
    rf_ui_slider_set_value_clamped(unk_6F53F0, 0.0);
  }
  else
  {
    v1 = (double)dword_6F52E4 / (double)(int)(MEMORY[0x6F5088] - unk_6F508C);
    rf_ui_slider_set_value_clamped(unk_6F53F0, v1);
  }
  return rf_gamesound_play_event(46, 0, 0.0, 1.0);
}

