// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462A90 rf_browser_scroll_down
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Increment scroll6F52E4;if signed scroll>visibleCount6F5088-visibleRows6F508C (STRICT >),replace with max(0,difference). If visibleCount EXACTLY equals
// visibleRows,set slider6F53F0 tofloat0;otherwise signed scroll/(visibleCount-visibleRows) via x87,round binary32,delegate slider setter. Equality avoids zero denominator;negative
// difference still divides and is not independently rejected. Always sound47(0,0.0,1.0),even at unchanged limit. No selected-row change,query,registry or list rebuild;return sound
// residue. Native integer arithmetic32-bit.
int rf_browser_scroll_down()
{
  float v1; // [esp+8h] [ebp-Ch]
  size_t v2; // [esp+10h] [ebp-4h]

  if ( ++dword_6F52E4 > (int)(MEMORY[0x6F5088] - unk_6F508C) )
  {
    if ( (int)(MEMORY[0x6F5088] - unk_6F508C) >= 0 )
      v2 = MEMORY[0x6F5088] - unk_6F508C;
    else
      v2 = 0;
    dword_6F52E4 = v2;
  }
  if ( MEMORY[0x6F5088] == unk_6F508C )
  {
    rf_ui_slider_set_value_clamped(unk_6F53F0, 0.0);
  }
  else
  {
    v1 = (double)dword_6F52E4 / (double)(int)(MEMORY[0x6F5088] - unk_6F508C);
    rf_ui_slider_set_value_clamped(unk_6F53F0, v1);
  }
  return rf_gamesound_play_event(47, 0, 0.0, 1.0);
}

