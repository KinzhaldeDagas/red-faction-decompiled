// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530740 rf_geomod_point_classify_against_face_plane
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): cdecl takes TWO stack arguments: point XYZ pointer then face/plane pointer. Old explicit one-argument declaration hid the plane at callers such as553BD2. Calls plane signed distance with second argument as ECX receiver and first as stack point; rounds result to float before comparing to PE double thresholds near +/-0.0001. Strictly below negative threshold returns3, strictly above positive threshold returns1, inclusive between returns2. Unordered NaN follows coplanar2. No normalization or pointer checks.
int __cdecl rf_geomod_point_classify_against_face_plane(const float *a1, const void *a2)
{
  float v3; // [esp+0h] [ebp-8h]

  v3 = rf_plane_point_signed_distance((float *)a2, (float *)a1);
  if ( v3 < -0.00009999999747378752 )
    return 3;
  if ( v3 <= 0.00009999999747378752 )
    return 2;
  return 1;
}

