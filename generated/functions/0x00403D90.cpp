// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00403D90 rf_ai_update_profiled_if_not_pending_delete
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): One required AI-block pointer; owner entity=DWORD block+0. Owner common flags+124 mask2 suppresses all work. Otherwise reads timestamp counter,
// saves LOW32 EAX only, calls403DE0(block), reads timestamp counter again and accumulates wrapping LOW32(end-start) into DWORD6663C8. Does not subtract/use high EDX or convert ticks
// to milliseconds. Pause policy belongs to403DE0, so a paused update still incurs profiling wrapper calls. EAX is owner pointer on skip or final timestamp LOW32, not a success/count
// result.
int *__cdecl rf_ai_update_profiled_if_not_pending_delete(int *a1)
{
  int *result; // eax
  int timestamp_counter; // [esp+4h] [ebp-4h]

  result = a1;
  if ( (*(_DWORD *)(*a1 + 124) & 2) == 0 )
  {
    timestamp_counter = rf_clock_read_timestamp_counter();
    rf_ai_update_one_block(a1);
    result = (int *)rf_clock_read_timestamp_counter();
    dword_6663C8 += (int)result - timestamp_counter;
  }
  return result;
}

