// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448B20 rf_game_clock_pause_depth_decrement_adapter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Exactly one55EF20 call; forwards full EAX new wrapped32-bit pause depth unchanged. Native delegate decrements
// global17F1110 with no lower-bound guard;0 becomes-1 and remains a nonzero pause. This wrapper does not itself tick clocks, check an existing pause owner, resume callbacks or
// canonicalize result.
int rf_game_clock_pause_depth_decrement_adapter()
{
  return rf_game_clock_pause_depth_decrement();
}

