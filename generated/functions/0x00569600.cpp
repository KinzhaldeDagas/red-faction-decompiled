// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569600 rf_polygon_segment_intersect_front_plane
// UNREALRED VERIFIED [mission-unhide-20261020] One-sided segment-plane admission: signed distance of start must be >=0; negative dot(delta,normal) must be >= distance; output fraction is distance / negative dot. Source does not explicitly guard a coplanar zero denominator. UnrealRed retained-triangle adapter rejects degenerate/parallel segments before barycentric containment and uses decoded source normals, because importer reverses UE triangle winding.
char __cdecl rf_polygon_segment_intersect_front_plane(float *a1, float *a2, float *a3, float *a4)
{
  float v5; // [esp+0h] [ebp-8h]
  float v6; // [esp+4h] [ebp-4h]

  v5 = rf_plane_point_signed_distance(a3, a1);
  if ( v5 < 0.0 )
    return 0;
  v6 = -rf_vector_dot(a2, a3);
  if ( v5 > (double)v6 )
    return 0;
  *a4 = v5 / v6;
  return 1;
}

