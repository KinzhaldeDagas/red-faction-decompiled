// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581E10 rf_frustum_reject_transformed_aabb_legacy_plane
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): For each current28-byte clip record,transforms source plane through verified legacy582250 into local plane using supplied matrix/translation;selects support corner from local AABB min/max,returns1 on signed distance>0,else0 after all planes. Boundary accepted. Inherits legacy plane transform formula dot(sourceN,sourceN*d+translation),not a mathematically corrected inverse-transpose. Uses temporary plane/corner;no determinant/normalization/bounds/finite guard. Used by volume-box visible-list preparation.
char __cdecl rf_frustum_reject_transformed_aabb_legacy_plane(int a1, float *a2, float *bounds_min, float *bounds_max)
{
  float v5[4]; // [esp+0h] [ebp-28h] BYREF
  int v6; // [esp+10h] [ebp-18h] BYREF
  unsigned int corner_index; // [esp+14h] [ebp-14h] BYREF
  int i; // [esp+18h] [ebp-10h]
  float out_vector[3]; // [esp+1Ch] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(out_vector);
  for ( i = 0; i < dword_18CD390; ++i )
  {
    rf_plane4_transform_rows_offset_legacy((float *)&unk_18CD3CC + 7 * i, (int)v5, a1, a2);
    rf_plane_select_aabb_support_corners(v5, &corner_index, &v6);
    rf_aabb_select_corner_by_index(out_vector, corner_index, bounds_min, bounds_max);
    if ( rf_plane_point_signed_distance(v5, out_vector) > 0.0 )
      return 1;
  }
  return 0;
}

