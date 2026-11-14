// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B9A0 rf_gameplay_priority_scroll_up
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Noarg. Decrement scroll6F7B84;only signednegative clamps0. x87 signed scroll/(count6F7B7C-visibleRows6F7B68),roundfloat,set slider6F7D58. NO
// zero-denominator/equality guard;negative denominator allowed;no upper-scroll repair or stored-scroll correction from slider clamp. No selection/swap/sound/save.
void rf_gameplay_priority_scroll_up()
{
  float v0; // [esp+4h] [ebp-8h]

  if ( (int)--dword_6F7B84 < 0 )
    dword_6F7B84 = 0;
  v0 = (double)(int)dword_6F7B84 / (double)(unk_6F7B7C - unk_6F7B68);
  rf_ui_slider_set_value_clamped(unk_6F7D58, v0);
}

