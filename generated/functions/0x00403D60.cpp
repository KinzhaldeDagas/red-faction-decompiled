// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00403D60 rf_ai_global_deadlines_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): No arguments. Arms deadline at6663E0 with signed0 milliseconds, then6663DC with0 milliseconds, then resets6663E4 to disarmed-1 through timer helper.
// Arming0 is clock-relative, not raw memory zero and not disarm. Does not clear pause byte/profiling accumulator; EAX is incidental last reset-helper result.
_DWORD *rf_ai_global_deadlines_initialize()
{
  rf_replicator_arm_milliseconds(&dword_6663E0, 0);
  rf_replicator_arm_milliseconds(&dword_6663DC, 0);
  return rf_replicator_reset(&dword_6663E4);
}

