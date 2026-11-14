// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00468810 rf_controls_scroll_actions_up
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Decrement scroll6F62B8;only signednegative clamps0. Divide scroll/(actionCount-visibleRows) via x87/roundfloat,call slider6F6428 setter. NO
// zero-denominator guard,negative denominator allowed;no upper-scroll correction. No selected-action/capture/sound change or save.
void rf_controls_scroll_actions_up()
{
  float v0; // [esp+4h] [ebp-8h]

  if ( --dword_6F62B8 < 0 )
    dword_6F62B8 = 0;
  v0 = (double)dword_6F62B8 / (double)(unk_6F62AC - unk_6F62A8);
  rf_ui_slider_set_value_clamped(unk_6F6428, v0);
}

