// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004655D0 rf_browser_ensure_selected_row_visible
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. If signed selectedDisplay6F52E0<scroll6F52E4,set scroll=selected. Else if selected>=scroll+visibleRows6F508C,set scroll=selected-visibleRows+1. No
// index/row-count/minimum/maximum clamp. If visibleCount6F5088==visibleRows,set slider6F53F0 float0;otherwise x87 signed scroll/(visibleCount-visibleRows),round binary32,call clamped
// slider setter. Negative denominator allowed;clamping slider does not write back corrected scroll. No selected raw-row change,display rebuild,sound or query.
void rf_browser_ensure_selected_row_visible()
{
  float v0; // [esp+4h] [ebp-8h]

  if ( dword_6F52E0 >= dword_6F52E4 )
  {
    if ( dword_6F52E0 >= unk_6F508C + dword_6F52E4 )
      dword_6F52E4 = dword_6F52E0 - unk_6F508C + 1;
  }
  else
  {
    dword_6F52E4 = dword_6F52E0;
  }
  if ( MEMORY[0x6F5088] == unk_6F508C )
  {
    rf_ui_slider_set_value_clamped(unk_6F53F0, 0.0);
  }
  else
  {
    v0 = (double)dword_6F52E4 / (double)(int)(MEMORY[0x6F5088] - unk_6F508C);
    rf_ui_slider_set_value_clamped(unk_6F53F0, v0);
  }
}

