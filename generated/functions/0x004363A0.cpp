// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004363A0 rf_entity_sum_selected_secondary_loaded_and_reserve
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required entity), fullEAX wrapping32 sum. Exact selected secondary DWORD680==-1 returns0. Any other
// index calls safe reserve4391D0(entity,current secondary) first; it rejects negative weapon/AmmoID but has no own positive upper bounds. Save returned reserve, RE-READ secondary680,
// then add RAW loaded DWORD[entity+812+4*newIndex] with wrapping32 ADD and return, no clamp. No other negative/upper index guard, ownership, positive-clip, loaded-availability or
// finite/status check; negative indices other than-1 can alias earlier entity fields. Both loaded and reserve are included regardless clip mode; do not substitute selected-primary
// query, nonnegative mathematical sum or reserve-only/loaded-only view. No own state write or snapshot guaranteeing same secondary across delegate.
int __cdecl rf_entity_sum_selected_secondary_loaded_and_reserve(int a1)
{
  if ( *(_DWORD *)(a1 + 680) == -1 )
    return 0;
  else
    return *(_DWORD *)(a1 + 4 * *(_DWORD *)(a1 + 680) + 812) + sub_4391D0(a1, *(_DWORD *)(a1 + 680));
}

