// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00411DD0 sub_411DD0
// UNREALRED VERIFIED [combat-native-view-fov-20261112]: Player/camera wrapper scope: argument DWORD1 supplies player resolution, argument DWORD0 is mutated entity. Called by4119E0 camera cases0/5; reads resolved view-entity8BC deadline and8B4 scalar, mutates wrapper entity7F8 through5597C0 and rebuilds7E0 with55B770. This evidence does not identify a generic NPC damage-flinch writer.
char __cdecl sub_411DD0(int *a1)
{
  int v1; // eax
  float v3[3]; // [esp-8h] [ebp-20h] BYREF
  float v4; // [esp+4h] [ebp-14h]
  float v5; // [esp+Ch] [ebp-Ch] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v6 = rf_player_resolve_view_entity_with_monitor_fallback(a1[1]);
  v1 = *a1;
  v7 = *a1;
  if ( v7 )
  {
    if ( v6 )
    {
      LOBYTE(v1) = rf_replicator_has_elapsed((int *)(v6 + 2236));
      if ( !(_BYTE)v1 )
      {
        v5 = 1.0 - *(float *)(v6 + 2228);
        if ( rf_replicator_signed_remaining_milliseconds((int *)(v6 + 2236)) < 1000 )
          *(float *)(v6 + 2228) = *(float *)(v6 + 2228) / 1.666000008583069;
        rf_float_clamp_in_place(&v5, -1.0, 1.0);
        v4 = v5;
        rf_vector3_copy_return_destination(v3, (float *)(v7 + 2040));
        rf_random_unit_vector_in_cone((float *)(v7 + 2040), v3[0], v3[1], v3[2], v4);
        LOBYTE(v1) = rf_matrix3_rebuild_basis_from_forward_in_place((char *)(v7 + 2016));
      }
    }
  }
  return v1;
}

