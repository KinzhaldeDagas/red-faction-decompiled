// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B9F0 rf_gameplay_priority_scroll_down
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Noarg. Increment scroll6F7B84;if signed>=count-visibleRows,set max(0,difference). Then divide signed scroll by RAW difference (not
// max0),roundfloat,set slider6F7D58. Zero denominator still unguarded;negative difference still divides though scroll clamp0. No selection/swap/sound/save. Differs from controls
// arrow468860 which can store negative scroll.
void rf_gameplay_priority_scroll_down()
{
  float v0; // [esp+4h] [ebp-8h]

  if ( ++dword_6F7B84 >= unk_6F7B7C - unk_6F7B68 )
    dword_6F7B84 = rf_int_max(0, unk_6F7B7C - unk_6F7B68);
  v0 = (double)(int)dword_6F7B84 / (double)(unk_6F7B7C - unk_6F7B68);
  rf_ui_slider_set_value_clamped(unk_6F7D58, v0);
}

