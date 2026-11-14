// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00469C40 rf_performance_preset_cycle_next
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Noarg. Cycle preset chooser6F75A0 NEXT,apply raw selectedDWORD6F770C via469A50,then sound47(0,0.0,1.0). Bound to LEFT arrow6F7308:choice order
// High,Medium,Low,Custom,so visual arrow direction differs from helper next/previous name. Apply occurs even if chooser unchanged;no own player/index/capability guard or file save.
// Native stack reuses apply argument slot for sound gain1.0 instead of separate cleanup;EAX sound residue.
int rf_performance_preset_cycle_next()
{
  rf_ui_choice_cycle_next((int)&unk_6F75A0);
  rf_performance_options_apply_preset(unk_6F770C);
  return rf_gamesound_play_event(47, 0, 0.0, 1.0);
}

