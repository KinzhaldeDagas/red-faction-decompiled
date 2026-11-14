// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E05B0 rf_player_direction_to_local_quadrant_mask
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Copies input float3 BEFORE testing playerNULL. NULL player or missing own entity returns0. Ordered world X==0 AND Z==0 returns15 regardless Y before inverse rotation. Otherwise inverse-rotate by entity matrix+72; store F32 absX,absZ. absX>=absZ OR unordered selects X branch: ordered X>0 gives2, otherwise8. Z branch: ordered Z>0 gives4, otherwise1. Ties choose X. No normalization, finite checks or input writes.
int __cdecl rf_player_direction_to_local_quadrant_mask(int a1, float *a2)
{
  float v3; // [esp+0h] [ebp-1Ch]
  float v4; // [esp+4h] [ebp-18h]
  float v5[2]; // [esp+8h] [ebp-14h] BYREF
  float v6; // [esp+10h] [ebp-Ch]
  int v7; // [esp+14h] [ebp-8h]
  int v8; // [esp+18h] [ebp-4h]

  v7 = 0;
  rf_vector3_copy_return_destination(v5, a2);
  if ( !a1 )
    return 0;
  v8 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !v8 )
    return 0;
  if ( v5[0] == 0.0 && v6 == 0.0 )
    return 15;
  rf_matrix3_inverse_rotate_vector(v5, (float *)(v8 + 72));
  v4 = fabs(v6);
  v3 = fabs(v5[0]);
  if ( v3 >= (double)v4 )
  {
    if ( v5[0] <= 0.0 )
      return 8;
    else
      return 2;
  }
  else if ( v6 <= 0.0 )
  {
    return 1;
  }
  else
  {
    return 4;
  }
}

