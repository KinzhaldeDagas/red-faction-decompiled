// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569660 rf_segment_triangle_intersect_front_plane
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Cdecl segment(start3,delta3),three-vertex pointer array,plane,output point,output fraction. Calls one-sided front-plane admission569600;on success writes point=start+delta*t then tests projected triangle fan containment569F30. Fraction and point may be written even when containment rejects;no best-hit comparison or output rollback. Assumes valid nondegenerate triangle/plane.
bool __cdecl rf_segment_triangle_intersect_front_plane(float *lhs, int *a2, float *a3, float *destination, float *a5)
{
  float *v6; // eax
  float *v7; // eax
  float copy_result[3]; // [esp+4h] [ebp-24h] BYREF
  float sum_result[3]; // [esp+10h] [ebp-18h] BYREF
  float scaled_result[3]; // [esp+1Ch] [ebp-Ch] BYREF

  if ( !rf_polygon_segment_intersect_front_plane(lhs, lhs + 3, a3, a5) )
    return 0;
  v6 = rf_vector_multiply_scalar(lhs + 3, scaled_result, *a5);
  v7 = rf_vector_add(lhs, sum_result, v6);
  rf_vector_copy(destination, copy_result, v7);
  return rf_polygon_point_inside_projected_triangle_fan((int)destination, 3, a2, a3);
}

