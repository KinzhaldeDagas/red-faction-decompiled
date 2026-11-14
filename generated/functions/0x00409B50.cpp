// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00409B50 rf_ai_set_secondary10_if_owner_resolves
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Reads owner handle+44 and resolves ENTITY; missing returns0. Any resolved entity (not separately pointer-compared with
// original) calls secondary-state helper on ORIGINAL input block with numeric10, refreshing helper-owned timestamp. Does not reset route, clear target or alter primary numeric mode.
// Return is incidental resolver/secondary helper result.
int __cdecl rf_ai_set_secondary10_if_owner_resolves(int a1)
{
  int result; // eax

  result = rf_entity_resolve_handle(*(_DWORD *)(*(_DWORD *)a1 + 44));
  if ( result )
    return rf_ai_secondary_state_write(a1, 10);
  return result;
}

