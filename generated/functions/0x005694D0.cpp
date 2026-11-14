// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005694D0 rf_segment_plane_intersection_point_fraction
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Cdecl output float[4],start,delta,plane(normal3,D). denominator=-dot(delta,normal);exact0 returnsfalse. Computes t=signedDistance(start)/denominator into output[3] BEFORE range check;rejects t<0 or>1,otherwise output.xyz=start+delta*t,returns1. Allows either plane side/direction;no epsilon,finite or plane-normal normalization check. Output fraction may change on miss while point remains old.
char __cdecl rf_segment_plane_intersection_point_fraction(float *destination, float *lhs, float *vector, float *a4)
{
  float *v5; // eax
  float *v6; // eax
  float copy_result[3]; // [esp+4h] [ebp-2Ch] BYREF
  float sum_result[3]; // [esp+10h] [ebp-20h] BYREF
  float scaled_result[3]; // [esp+1Ch] [ebp-14h] BYREF
  float v10; // [esp+28h] [ebp-8h]
  float v11; // [esp+2Ch] [ebp-4h]

  v11 = -rf_vector_dot(vector, a4);
  if ( v11 == 0.0 )
    return 0;
  v10 = rf_plane_point_signed_distance(a4, lhs);
  destination[3] = v10 / v11;
  if ( destination[3] < 0.0 || destination[3] > 1.0 )
    return 0;
  v5 = rf_vector_multiply_scalar(vector, scaled_result, destination[3]);
  v6 = rf_vector_add(lhs, sum_result, v5);
  rf_vector_copy(destination, copy_result, v6);
  return 1;
}

