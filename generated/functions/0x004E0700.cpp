// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E0700 rf_player_view_target_is_monitor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Returns AL1 only if player exists, view-target DWORD+180!=-1 resolves as generic object, and shared use classification4B7C30 is EXACT5. Otherwise AL0. Does not test player flags+16 mask8 or represent arbitrary third-person mode.
bool __cdecl rf_player_view_target_is_monitor(int a1)
{
  _DWORD *v2; // [esp+0h] [ebp-4h]

  if ( !a1 )
    return 0;
  if ( *(_DWORD *)(a1 + 180) == -1 )
    return 0;
  v2 = (_DWORD *)rf_object_resolve_handle(*(_DWORD *)(a1 + 180));
  return v2 && rf_object_get_use_classification(v2) == 5;
}

