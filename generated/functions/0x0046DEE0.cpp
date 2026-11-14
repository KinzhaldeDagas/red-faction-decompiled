// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046DEE0 rf_persona_history_scroll_up
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): History Up callback; ignores supplied pointer arguments. Decrements viewoffset6F899C and clamps negative to0. Sets slider6F8A08 to
// binary32(1-(remaining_layout_height()-clipHeight6F8974)/range6F898C), delegating final clamp. Division has no zero/negative-range guard; height helper can return-1. Incidental
// return.
void rf_persona_history_scroll_up()
{
  float v0; // [esp+4h] [ebp-8h]

  if ( --dword_6F899C < 0 )
    dword_6F899C = 0;
  v0 = 1.0 - (double)(rf_persona_history_remaining_layout_height() - unk_6F8974) / (double)unk_6F898C;
  rf_ui_slider_set_value_clamped(unk_6F8A08, v0);
}

