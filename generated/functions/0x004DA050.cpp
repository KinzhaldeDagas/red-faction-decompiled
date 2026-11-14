// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DA050 rf_matrix3_build_pitch_heading_linear_horizontal_basis
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl output matrix,angle pointer. Uses angle[0] pitch and[1] heading, ignores later components. Builds nine-float temporary matrix at EBP-28h: right=(cos(heading),0,-sin(heading)); forward.y=sin(pitch); horizontal=float(1-abs(forward.y)). Only ORDERED horizontal>0 computes forward.x=-right.z*horizontal and forward.z=right.x*horizontal; <=0 OR unordered sets both zero. Computes up=cross(forward,right). Passes whole matrix to rf_matrix3_rebuild_basis_from_forward_to_output, then returns output address. Horizontal scale is linear1-|sin(pitch)|, not cos(pitch). Helper normalizes forward and rebuilds basis; no own finite, angle-range, NULL, zero-direction or alias guard.
int __cdecl rf_matrix3_build_pitch_heading_linear_horizontal_basis(int a1, float *a2)
{
  float *v2; // eax
  float v4; // [esp+4h] [ebp-44h]
  float copy_result[3]; // [esp+8h] [ebp-40h] BYREF
  float v6[3]; // [esp+14h] [ebp-34h] BYREF
  float v7[2]; // [esp+20h] [ebp-28h] BYREF
  float v8; // [esp+28h] [ebp-20h]
  float destination[3]; // [esp+2Ch] [ebp-1Ch] BYREF
  float v10; // [esp+38h] [ebp-10h] BYREF
  float v11; // [esp+3Ch] [ebp-Ch]
  float v12; // [esp+40h] [ebp-8h]
  float v13; // [esp+44h] [ebp-4h]

  rf_matrix3_construct((char *)v7);
  v7[0] = rf_cos_float(a2[1]);
  v7[1] = 0.0;
  v8 = -rf_sin_float(a2[1]);
  v11 = rf_sin_float(*a2);
  v4 = fabs(v11);
  v13 = 1.0 - v4;
  if ( v13 <= 0.0 )
  {
    v12 = 0.0;
    v10 = 0.0;
  }
  else
  {
    v10 = -v8 * v13;
    v12 = v7[0] * v13;
  }
  v2 = rf_vector_cross(&v10, v6, v7);
  rf_vector_copy(destination, copy_result, v2);
  rf_matrix3_rebuild_basis_from_forward_to_output((char *)v7, a1);
  return a1;
}

