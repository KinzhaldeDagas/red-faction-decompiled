// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E0440 rf_player_get_selected_weapon_and_resolve_mesh
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Assumes player nonNULL; resolve own entity UID player+20, missing returns -1. If attached-use vehicle AL==1 or attached-use turret AL==1, resolve linked UID entity+512 and take its selected weapon DWORD+676; missing linked entity leaves -1 without fallback. Otherwise use own entity+676. For any index other than -1 call first-person selected-mesh resolver(player,index), discard result, return chosen index unchanged. No weapon-index range check.
unsigned int __cdecl rf_player_get_selected_weapon_and_resolve_mesh(_DWORD *a1)
{
  int v2; // [esp+0h] [ebp-Ch]
  unsigned int v3; // [esp+4h] [ebp-8h]
  int v4; // [esp+8h] [ebp-4h]

  v4 = rf_entity_resolve_handle(a1[5]);
  if ( !v4 )
    return -1;
  v3 = -1;
  if ( rf_entity_has_attached_use_vehicle(v4) || rf_entity_has_attached_use_turret(v4) )
  {
    v2 = rf_entity_resolve_handle(*(_DWORD *)(v4 + 512));
    if ( v2 )
      v3 = *(_DWORD *)(v2 + 676);
  }
  else
  {
    v3 = *(_DWORD *)(v4 + 676);
  }
  if ( v3 != -1 )
    rf_fpgun_selected_mesh_resolve(a1, v3);
  return v3;
}

