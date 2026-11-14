// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EB9E0 rf_player_compose_fpgun_muzzle_world_transform
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Cdecl(player,required float3 output position,optional float9 output matrix), canonical ALbool; corrected misleading float-pointer player type. Unequal global pointer or missing own entity/modelDWORD52 returns0; no independent NULL guard for both pointersNULL. Resolve selected weapon; machine-pistol-special registry911C98 selects nodeDWORD68, every other index selects64, including-1. Only node EXACT-1 rejected. Compose model52/node with player orientation4084 and position4120 into local matrix and supplied position; ignore helper return. Copy local matrix only when optional output nonNULL; AL1. No positive handle/node/index/output-position validation, normalization or own source-model cache reset.
bool __cdecl rf_player_compose_fpgun_muzzle_world_transform(
        void *player,
        float *muzzle_position,
        float *muzzle_orientation)
{
  float v4[9]; // [esp+0h] [ebp-2Ch] BYREF
  int v5; // [esp+24h] [ebp-8h]

  if ( player != (void *)rf_local_fpgun_player )
    return 0;
  if ( !rf_entity_resolve_handle(*((_DWORD *)player + 5)) )
    return 0;
  if ( !*((_DWORD *)player + 13) )
    return 0;
  v5 = -1;
  if ( rf_player_get_selected_weapon_and_resolve_mesh(player) == unk_911C98 )
    v5 = *((_DWORD *)player + 17);
  else
    v5 = *((_DWORD *)player + 16);
  if ( v5 == -1 )
    return 0;
  rf_matrix3_construct((char *)v4);
  rf_vmesh_compose_prop_world_transform(
    *((_DWORD *)player + 13),
    v5,
    (float *)player + 1021,
    (int)player + 4120,
    (int)v4,
    muzzle_position);
  if ( muzzle_orientation )
    rf_matrix3_copy(muzzle_orientation, v4);
  return 1;
}

