// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00403030 rf_ai_queue_close_target_route_request
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): Corrected ABI: one cdecl entity pointer, explicit AL0/1 result, NO incoming ST0. Reject player-associated entity; then accesses embedded
// AI=entity+672, target full handle AI+704 (entity+1376). Handle-1 or failed ENTITY resolution returns0. Fast distance between COMMON positions+60 is rounded float32; ordered
// strictly<DOUBLE3 ORs embedded AI DWORD+1328 mask0x08000000 (entity+2000) and returns1. Equal/greater/NaN returns0 without clearing prior flag. Does not build route or reset
// timers;403350 consumes request. Native x87 operations consume only locally produced distance.
char __cdecl rf_ai_queue_close_target_route_request(int a1)
{
  float v2; // [esp+0h] [ebp-Ch]
  int v3; // [esp+4h] [ebp-8h]

  if ( rf_object_is_player_associated(a1) )
    return 0;
  if ( *(_DWORD *)(a1 + 1376) == -1 )
    return 0;
  v3 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 1376));
  if ( !v3 )
    return 0;
  v2 = rf_vector_fast_distance((const float *)(a1 + 60), (const float *)(v3 + 60));
  if ( v2 >= 3.0 )
    return 0;
  *(_DWORD *)(a1 + 2000) |= 0x8000000u;
  return 1;
}

