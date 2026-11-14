// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BE920 rf_collision_pair_passes_association_and_inactive_gate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Cdecl16-byte pair record; reads raw object pointers at+4/+8. Rejects if either object association HANDLE512 equals other object HANDLE44. Otherwise true only if neither satisfies respawn-inactive predicate. Returns AL bool without editing pair flags/list membership. No null/membership/type guard, self-pair special case or full type/radius collision filter here; full admission delegate is4BEC10 elsewhere.
bool __cdecl rf_collision_pair_passes_association_and_inactive_gate(int a1)
{
  if ( *(_DWORD *)(*(_DWORD *)(a1 + 4) + 512) == *(_DWORD *)(*(_DWORD *)(a1 + 8) + 44)
    || *(_DWORD *)(*(_DWORD *)(a1 + 8) + 512) == *(_DWORD *)(*(_DWORD *)(a1 + 4) + 44) )
  {
    return 0;
  }
  return !rf_object_has_respawn_inactive_flag(*(_DWORD *)(a1 + 4))
      && !rf_object_has_respawn_inactive_flag(*(_DWORD *)(a1 + 8));
}

