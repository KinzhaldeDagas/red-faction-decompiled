// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046DF40 rf_persona_history_scroll_down
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): History Down callback; ignores supplied pointer arguments. Increments viewoffset only if remaining_layout_height()>clipHeight. Then if offset>=fresh historyCount, replaces it
// with max(0,count-1). Recomputes height and sets slider to binary32(1-(height-clipHeight)/range6F898C). No zero/negative-range guard or independent lower-bound correction when
// offset<count. Incidental return.
void rf_persona_history_scroll_down()
{
  int count; // eax
  float v1; // [esp+4h] [ebp-8h]

  if ( rf_persona_history_remaining_layout_height() > dword_6F8974 )
    ++dword_6F899C;
  if ( dword_6F899C >= rf_persona_history_get_count() )
  {
    count = rf_persona_history_get_count();
    dword_6F899C = rf_int_max(0, count - 1);
  }
  v1 = 1.0 - (double)(rf_persona_history_remaining_layout_height() - dword_6F8974) / (double)unk_6F898C;
  rf_ui_slider_set_value_clamped(unk_6F8A08, v1);
}

