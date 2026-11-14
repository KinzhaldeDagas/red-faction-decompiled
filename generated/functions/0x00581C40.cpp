// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581C40 rf_frustum_reject_aabb
// UNREALRED VERIFIED [room-render-20261028]: For every active plane selects stored corner0x18CD3DC and computes signed distance. Returns1 on first distance>0,else0. Uses only rejecting corner (unlike tri-state0x581EB0). No projection or AABB mutation.
char __cdecl rf_frustum_reject_aabb(float *bounds_min, float *bounds_max)
{
  int i; // [esp+0h] [ebp-10h]
  float out_vector[3]; // [esp+4h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(out_vector);
  for ( i = 0; i < dword_18CD390; ++i )
  {
    rf_aabb_select_corner_by_index(out_vector, dword_18CD3DC[7 * i], bounds_min, bounds_max);
    if ( rf_plane_point_signed_distance((float *)&unk_18CD3CC + 7 * i, out_vector) > 0.0 )
      return 1;
  }
  return 0;
}

