// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581CC0 rf_frustum_reject_aabb_update_plane_mask
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): For each enabled INPUT bit(1<<planeIndex),uses support selector at record+20 (global18CD3DC;plane data starts at record+4) and returns1 if selected corner signed distance>0,leaving mask unchanged. If none reject,second pass uses opposite selector at record+24,builds output mask of still-intersecting planes with distance>0,stores mask,returns0. Planes stride28,count18CD390;touching0 accepted and bit cleared. NULL pointer skips first loop ONLY:second loop dereferences it (or final store even zero planes),so NULL is invalid despite initial test. x86 shifts wrap count modulo32;no count guard.
char __cdecl rf_frustum_reject_aabb_update_plane_mask(float *bounds_min, float *bounds_max, _DWORD *a3)
{
  float v4; // [esp+0h] [ebp-28h]
  float v5[3]; // [esp+4h] [ebp-24h] BYREF
  float v6; // [esp+10h] [ebp-18h]
  float out_vector[3]; // [esp+14h] [ebp-14h] BYREF
  int i; // [esp+20h] [ebp-8h]
  int v9; // [esp+24h] [ebp-4h]

  if ( a3 )
  {
    for ( i = 0; i < dword_18CD390; ++i )
    {
      if ( (*a3 & (1 << i)) != 0 )
      {
        rf_vector3_default_construct_noop(out_vector);
        rf_aabb_select_corner_by_index(out_vector, dword_18CD3DC[7 * i], bounds_min, bounds_max);
        v6 = rf_plane_point_signed_distance((float *)&unk_18CD3CC + 7 * i, out_vector);
        if ( v6 > 0.0 )
          return 1;
      }
    }
  }
  v9 = 0;
  for ( i = 0; i < dword_18CD390; ++i )
  {
    if ( (*a3 & (1 << i)) != 0 )
    {
      rf_vector3_default_construct_noop(v5);
      rf_aabb_select_corner_by_index(v5, dword_18CD3E0[7 * i], bounds_min, bounds_max);
      v4 = rf_plane_point_signed_distance((float *)&unk_18CD3CC + 7 * i, v5);
      if ( v4 > 0.0 )
        v9 |= 1 << i;
    }
  }
  *a3 = v9;
  return 0;
}

