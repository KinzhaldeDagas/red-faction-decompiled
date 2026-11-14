// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00401250 rf_reset_global_dword6663D4
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout):
// Noarg. Exactly one store global DWORD6663D4=0, then RET. No runtime admission, memory release or other state mutation. Semantic ownership beyond call from split respawn-reset4AE2F0
// is not established by this body; EAX not assigned, no success result.
void rf_reset_global_dword6663D4()
{
  dword_6663D4 = 0;
}

