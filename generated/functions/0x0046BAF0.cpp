// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046BAF0 rf_gameplay_priority_ensure_selected_visible
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Noarg. If signed selected6F7B88<scroll6F7B84,set scroll=selected;else selected>=scroll+visibleRows ->scroll=selected-visibleRows+1. No min/max
// clamp. Divide signed scroll/(count6F7B7C-visibleRows6F7B68),roundfloat,set slider6F7D58;zero/negative denominator unguarded. Slider clamp does not repair stored scroll. No priority
// mutation,selection validation,sound or save.
void rf_gameplay_priority_ensure_selected_visible()
{
  float v0; // [esp+4h] [ebp-8h]

  if ( unk_6F7B88 >= dword_6F7B84 )
  {
    if ( unk_6F7B88 >= unk_6F7B68 + dword_6F7B84 )
      dword_6F7B84 = unk_6F7B88 - unk_6F7B68 + 1;
  }
  else
  {
    dword_6F7B84 = unk_6F7B88;
  }
  v0 = (double)(int)dword_6F7B84 / (double)(unk_6F7B7C - unk_6F7B68);
  rf_ui_slider_set_value_clamped(unk_6F7D58, v0);
}

