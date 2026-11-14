// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056A420 rf_swept_sphere_front_plane_contact
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Cdecl start,delta,radius,plane,outT,outContact. Requires -dot(delta,normal)>0 and signedDistance(start)>=0. If distance>=radius,subtracts radius,requires remainingDistance<=-dot,sets t=remaining/-dot and contact=start-radius*normal+delta*t. Already overlapping front side (0<=distance<radius) returns t0 and orthogonal projection start-distance*normal. Behind-plane starts rejected even when within radius. No normal-length,radius>=0,finite,epsilon or best-hit checks;failure need not update outputs.
char __cdecl rf_swept_sphere_front_plane_contact(
        float *lhs,
        float *a2,
        float a3,
        float *vector,
        float *a5,
        float *destination)
{
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float v12[3]; // [esp+4h] [ebp-68h] BYREF
  float sum_result[3]; // [esp+10h] [ebp-5Ch] BYREF
  float v14[3]; // [esp+1Ch] [ebp-50h] BYREF
  float v15[3]; // [esp+28h] [ebp-44h] BYREF
  float copy_result[3]; // [esp+34h] [ebp-38h] BYREF
  float out_vector[3]; // [esp+40h] [ebp-2Ch] BYREF
  float scaled_result[3]; // [esp+4Ch] [ebp-20h] BYREF
  float scalar; // [esp+58h] [ebp-14h]
  float v20[3]; // [esp+5Ch] [ebp-10h] BYREF
  float v21; // [esp+68h] [ebp-4h]

  v21 = -rf_vector_dot(a2, vector);
  if ( v21 <= 0.0 )
    return 0;
  scalar = rf_plane_point_signed_distance(vector, lhs);
  if ( scalar < 0.0 )
    return 0;
  if ( a3 <= (double)scalar )
  {
    scalar = scalar - a3;
    if ( scalar <= (double)v21 )
    {
      *a5 = scalar / v21;
      v9 = rf_vector_multiply_scalar(vector, v15, a3);
      rf_vector_subtract(lhs, v20, v9);
      v10 = rf_vector_multiply_scalar(a2, v14, *a5);
      v11 = rf_vector_add(v20, sum_result, v10);
      rf_vector_copy(destination, v12, v11);
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    v7 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
    v8 = rf_vector_subtract(lhs, out_vector, v7);
    rf_vector_copy(destination, copy_result, v8);
    *a5 = 0.0;
    return 1;
  }
}

