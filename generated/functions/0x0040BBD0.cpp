// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040BBD0 rf_ai_store_target_position_and_arm_zero_deadline
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): Cdecl(required AI block,source vector pointer). Copies all three floats into block+708 then arms deadline+720 with0 milliseconds relative to
// current wrapped game clock. Does NOT raw-zero or disarm the deadline, change target handle+704, update owner pose or transform input. Return EAX is arm-helper result.
int __cdecl rf_ai_store_target_position_and_arm_zero_deadline(int a1, float *source)
{
  float copy_result[3]; // [esp+0h] [ebp-Ch] BYREF

  rf_vector_copy((float *)(a1 + 708), copy_result, source);
  return rf_replicator_arm_milliseconds((int *)(a1 + 720), 0);
}

