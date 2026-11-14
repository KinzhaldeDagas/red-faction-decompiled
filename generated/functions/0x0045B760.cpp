// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045B760 rf_multiplayer_level_scroll_down
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Increment32-bit scroll; if signed scroll>=levelCount-visibleRows,replace by max(0,levelCount-visibleRows).
// Divide resulting scroll by signed(levelCount-visibleRows),float-round,delegate slider setter,always play event47(0,0.0,1.0),even when unchanged at limit. No division-by-zero/finite
// guard or signed overflow protection. Unlike pointer-slider callback,denominator lacks +1. Does not move current row or alter rotation selection.
int rf_multiplayer_level_scroll_down()
{
  int first_dword; // eax
  float v2; // [esp+8h] [ebp-10h]
  double v3; // [esp+10h] [ebp-8h]

  ++dword_6F2D04;
  if ( dword_6F2D04 >= rf_receiver_get_first_dword(&unk_6F2DC4) - unk_6F2CF0 )
  {
    first_dword = rf_receiver_get_first_dword(&unk_6F2DC4);
    dword_6F2D04 = rf_int_max(0, first_dword - unk_6F2CF0);
  }
  v3 = (double)(int)dword_6F2D04;
  v2 = v3 / (double)(rf_receiver_get_first_dword(&unk_6F2DC4) - unk_6F2CF0);
  rf_ui_slider_set_value_clamped(flt_6F3740, v2);
  return rf_gamesound_play_event(47, 0, 0.0, 1.0);
}

