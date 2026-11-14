// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581EB0 rf_frustum_classify_aabb
// UNREALRED VERIFIED [room-render-20261028]: For each active plane (count0x18CD390,28-byte stride from0x18CD3CC), selects stored first corner index0x18CD3DC: positive signed distance returns1 OUTSIDE. Otherwise tests opposite stored corner0x18CD3E0; any positive marks intersection. After all planes returns0 INTERSECTING if marked,else-1 INSIDE. Strict>0 so boundaries not rejected. No bounds ordering/count validation.
int __cdecl rf_frustum_classify_aabb(float *bounds_min, float *bounds_max)
{
  float v3; // [esp+0h] [ebp-18h]
  float v4; // [esp+0h] [ebp-18h]
  float out_vector[3]; // [esp+4h] [ebp-14h] BYREF
  int i; // [esp+10h] [ebp-8h]
  char v7; // [esp+17h] [ebp-1h]

  v7 = 0;
  for ( i = 0; i < dword_18CD390; ++i )
  {
    rf_vector3_default_construct_noop(out_vector);
    rf_aabb_select_corner_by_index(out_vector, dword_18CD3DC[7 * i], bounds_min, bounds_max);
    v3 = rf_plane_point_signed_distance((float *)&unk_18CD3CC + 7 * i, out_vector);
    if ( v3 > 0.0 )
      return 1;
    rf_aabb_select_corner_by_index(out_vector, dword_18CD3E0[7 * i], bounds_min, bounds_max);
    v4 = rf_plane_point_signed_distance((float *)&unk_18CD3CC + 7 * i, out_vector);
    if ( v4 > 0.0 )
      v7 = 1;
  }
  if ( v7 )
    return 0;
  else
    return -1;
}

