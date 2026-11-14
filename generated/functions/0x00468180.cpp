// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00468180 rf_controls_ensure_selected_action_visible
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Signed selected6F62BC<scroll6F62B8 ->scroll=selected;else selected>=scroll+visibleRows6F62A8 ->scroll=selected-visibleRows+1. No selected/scroll bound
// clamp. ALWAYS x87 divide signed scroll/(actionCount6F62AC-visibleRows),roundfloat,delegate clamped slider6F6428. NO equality/zero-denominator guard unlike browser helper;negative
// denominator also allowed. Slider clamp does not repair stored scroll. No selection change,sound or capture mutation.
void rf_controls_ensure_selected_action_visible()
{
  float v0; // [esp+4h] [ebp-8h]

  if ( dword_6F62BC >= dword_6F62B8 )
  {
    if ( dword_6F62BC >= unk_6F62A8 + dword_6F62B8 )
      dword_6F62B8 = dword_6F62BC - unk_6F62A8 + 1;
  }
  else
  {
    dword_6F62B8 = dword_6F62BC;
  }
  v0 = (double)dword_6F62B8 / (double)(unk_6F62AC - unk_6F62A8);
  rf_ui_slider_set_value_clamped(unk_6F6428, v0);
}

