// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505D20 rf_trigger_clear_global_activation_suppression
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Clears dword0x90B508 to0. No other stores/calls in body; semantic role of this auxiliary trigger global remains unproven.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): No arguments,void; only store DWORD90B508=0, no calls. Semantic role now established by direct native readers: removes EXACT1 gate in505360 central trigger commit and restores normal startup-commit branch in5052B0 (subject to each routine own conditions). Benchmark panel515070 case22 clears it. Does not force activation, reset trigger disabled/count/cooldown state, clear links, or undo the flag8 filter decisions made while suppression was set. This refines the older comment that left the global role unproven.
void rf_trigger_clear_global_activation_suppression()
{
  unk_90B508 = 0;
}

