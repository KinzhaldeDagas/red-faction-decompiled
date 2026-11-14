// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056BE00 rf_ray_intersect_plane_write_point_if_nonparallel
// UNREALRED VERIFIED [lightmap-shadows-20261028]: Arguments rayrecord(originXYZ,directionXYZ),plane(normalXYZ,D),outputXYZ. Denominator=dot(direction,normal); exactly0 returnsfalsewithoutwritingoutput. Else t=-planeSignedDistance(origin)/denominator,writes origin+t*direction,and returns t>=0. Output iswritten EVEN ift<0 andfalse. No upperboundt<=1 or normalizeddirection requirement; thisisraytest,nottightlyboundedsegmenttest.
bool __cdecl rf_ray_intersect_plane_write_point_if_nonparallel(float *lhs, float *a2, float *destination)
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
  return scalar >= 0.0;
}

