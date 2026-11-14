// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00487460 rf_mover_registries_initialize
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL volume/decal layouts, cumulative corner room queries, mover list and auxiliary-node ownership, linked physics flags and native debug draw arguments): 
// Cdecl no arguments. Sets mover sequence counterDWORD704608=0. Initializes common mover sentinel704610 next652/prev656 (absolute70489C/7048A0) toself, and moving-solid
// sentinel704940 next652/prev656 (704BCC/704BD0) toself. Sets auxiliary20-byte moving-solid ring head704600=NULL. Registers auxiliary-ring cleanup4874C0 through atexit and returns
// registration result. Native XOR/JNZ loops are dead, each assignment group runs once. No freeing existing live objects/ring before overwriting heads; repeated calls register
// repeated exit callbacks.
int rf_mover_registries_initialize()
{
  unk_704608 = 0;
  unk_70489C = &unk_704610;
  unk_7048A0 = &unk_704610;
  unk_704BCC = &unk_704940;
  unk_704BD0 = &unk_704940;
  unk_704600 = 0;
  return atexit(rf_moving_solid_aux_ring_free_at_exit);
}

