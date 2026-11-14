// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DEFF0 rf_player_resolved_entity_is_dead
// UNREALRED VERIFIED [save-validation-20261028]: Null player returns false. Resolves handle at player+20; true only for nonnull resolved entity with bit1 (mask0x1) at entity+2064. Missing entity returns false.
bool __cdecl rf_player_resolved_entity_is_dead(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  if ( !a1 )
    return 0;
  v2 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  return v2 && (*(_DWORD *)(v2 + 2064) & 1) != 0;
}

