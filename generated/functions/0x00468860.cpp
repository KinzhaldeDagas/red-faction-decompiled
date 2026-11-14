// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00468860 rf_controls_scroll_actions_down
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Increment scroll6F62B8;if signed>=actionCount6F62AC-visibleRows6F62A8,set EXACT difference (no max0). Then x87 divide by SAME difference,roundfloat,set
// slider. Can store negative scroll when actionCount<visibleRows;zero denominator unguarded. No selected-action/capture reset,sound or save;slider clamp does not update stored
// scroll.
void rf_controls_scroll_actions_down()
{
  float v0; // [esp+4h] [ebp-8h]

  if ( ++dword_6F62B8 >= unk_6F62AC - unk_6F62A8 )
    dword_6F62B8 = unk_6F62AC - unk_6F62A8;
  v0 = (double)dword_6F62B8 / (double)(unk_6F62AC - unk_6F62A8);
  rf_ui_slider_set_value_clamped(unk_6F6428, v0);
}

