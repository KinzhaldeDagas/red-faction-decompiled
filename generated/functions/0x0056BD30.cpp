// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056BD30 rf_line_plane_intersection_unbounded
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, unowned renderer entry recovery, camera-plane beam geometry and original PE bytes): Cdecl six-float line(origin3,direction3),plane(normal3,D),output point. denominator=dot(direction,normal);EXACT0 returnsfalse,leaves output unchanged. Otherwise t=-signedDistance(plane,origin)/denominator and output=origin+t*direction,returns1. NO t>=0 or t<=1 restriction:negative/backward intersections accepted,unlike segment helper5694D0. Beam renderer relies on this to project far endpoint backward to near camera plane. No epsilon,finite,normalization or parallel-near tolerance checks.
char __cdecl rf_line_plane_intersection_unbounded(float *lhs, float *a2, float *destination)
{
  float *v4; // eax
  float *v5; // eax
  float copy_result[3]; // [esp+4h] [ebp-30h] BYREF
  float sum_result[3]; // [esp+10h] [ebp-24h] BYREF
  float scaled_result[3]; // [esp+1Ch] [ebp-18h] BYREF
  float scalar; // [esp+28h] [ebp-Ch]
  float v10; // [esp+2Ch] [ebp-8h]
  float v11; // [esp+30h] [ebp-4h]

  v11 = rf_vector_dot(lhs + 3, a2);
  if ( v11 == 0.0 )
    return 0;
  v10 = rf_plane_point_signed_distance(a2, lhs);
  scalar = -v10 / v11;
  v4 = rf_vector_multiply_scalar(lhs + 3, scaled_result, scalar);
  v5 = rf_vector_add(lhs, sum_result, v4);
  rf_vector_copy(destination, copy_result, v5);
  return 1;
}

