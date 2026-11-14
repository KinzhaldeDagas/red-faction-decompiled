// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569580 rf_segment_triangle_intersect_two_sided_plane
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl(segment6,triangleVertexPointers3,plane4,outputPoint,outFraction). Calls56BDB0 two-sided infinite-line/plane query; denominator exactly0 fails without writing fraction. Otherwise writes fraction,computes output=segment.start+segment.delta*fraction,then tests point inside supplied three-vertex projected triangle fan. No fraction[0,1] check here: accepts line hits beyond segment ends if projected point is inside. Output point/fraction may be written even on outside-triangle failure; plane and vertices must agree.
bool __cdecl rf_segment_triangle_intersect_two_sided_plane(
        float *lhs,
        int *a2,
        float *a3,
        float *destination,
        float *a5)
{
  float *v6; // eax
  float *v7; // eax
  float copy_result[3]; // [esp+4h] [ebp-24h] BYREF
  float sum_result[3]; // [esp+10h] [ebp-18h] BYREF
  float scaled_result[3]; // [esp+1Ch] [ebp-Ch] BYREF

  if ( !sub_56BDB0((int)lhs, a3, a5) )
    return 0;
  v6 = rf_vector_multiply_scalar(lhs + 3, scaled_result, *a5);
  v7 = rf_vector_add(lhs, sum_result, v6);
  rf_vector_copy(destination, copy_result, v7);
  return rf_polygon_point_inside_projected_triangle_fan((int)destination, 3, a2, a3);
}

