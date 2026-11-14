// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DEFC0 rf_player_has_no_resolved_entity
// UNREALRED VERIFIED [save-validation-20261028]: Returns true if player pointer is null or rf_entity_resolve_handle(player+20) is null; otherwise false. Does not test death flag.
bool __cdecl rf_player_has_no_resolved_entity(int a1)
{
  return !a1 || rf_entity_resolve_handle(*(_DWORD *)(a1 + 20)) == 0;
}

