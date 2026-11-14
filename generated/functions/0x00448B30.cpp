// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448B30 rf_game_clock_pause_depth_increment_adapter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Exactly one55EF00 call; forwards full EAX new wrapped32-bit pause depth. Delegate increments global17F1110 with
// no maximum/overflow guard; this wrapper adds no nesting validation, clock update, callback or normalized bool.
int rf_game_clock_pause_depth_increment_adapter()
{
  return rf_game_clock_pause_depth_increment();
}

