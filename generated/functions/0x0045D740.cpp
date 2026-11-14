// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045D740 rf_multiplayer_level_scroll_ensure_current_row_visible
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. If signed current row6F2D08<scroll6F2D04,set scroll=current row. Else if current>=scroll+visibleRows,set
// scroll=current-visibleRows+1. Otherwise retain scroll. Then x87 divide signed scroll by(levelCount-visibleRows),round tofloat,pass slider setter4719F0. No explicit
// zero-denominator,finite,negative/current-row range check,scroll max clamp or selection mutation. Does not use pointer callback's +1 denominator adjustment;no sound.
void rf_multiplayer_level_scroll_ensure_current_row_visible()
{
  float v0; // [esp+4h] [ebp-10h]
  double v1; // [esp+Ch] [ebp-8h]

  if ( dword_6F2D08 >= dword_6F2D04 )
  {
    if ( dword_6F2D08 >= unk_6F2CF0 + dword_6F2D04 )
      dword_6F2D04 = dword_6F2D08 - unk_6F2CF0 + 1;
  }
  else
  {
    dword_6F2D04 = dword_6F2D08;
  }
  v1 = (double)(int)dword_6F2D04;
  v0 = v1 / (double)(rf_receiver_get_first_dword(dword_6F2DC4) - unk_6F2CF0);
  rf_ui_slider_set_value_clamped(flt_6F3740, v0);
}

