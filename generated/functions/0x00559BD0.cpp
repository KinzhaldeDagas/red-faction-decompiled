// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559BD0 rf_point_rotate_about_axis_pivot
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Axis-angle helper builds an axis frame via0x55BF00, transforms offset to that frame, inverse-rotates by bank matrix from0x55A850(0,angle,0), transforms back and restores pivot. Thus physical right-handed angle is NEGATIVE the stored angle; stored mover radians already negate authored degrees. Converted UE axis comes from key runtime up row (+0x1C), serialized basis third vector.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): cdecl(output,input,storedAngle,pivot,axis). Constructs normalized-axis frame55BF00, transforms input-pivot into it, inverse-rotates by Euler bank matrix(0,storedAngle,0), rotates back and adds pivot. Physical right-handed angle is NEGATIVE storedAngle. Output staged through temporaries so may equal input. Zero/invalid axis not explicitly guarded; returns vector-copy destination bits.
float *__cdecl rf_point_rotate_about_axis_pivot(float *a1, float *lhs, float a3, float *rhs, float *a5)
{
  float *v5; // eax
  float *v6; // eax
  float v8[3]; // [esp+Ch] [ebp-9Ch] BYREF
  float sum_result[3]; // [esp+18h] [ebp-90h] BYREF
  float copy_result[3]; // [esp+24h] [ebp-84h] BYREF
  float out_vector[3]; // [esp+30h] [ebp-78h] BYREF
  float v12[9]; // [esp+3Ch] [ebp-6Ch] BYREF
  float v13[9]; // [esp+60h] [ebp-48h] BYREF
  _BYTE v14[12]; // [esp+84h] [ebp-24h] BYREF
  float v15; // [esp+90h] [ebp-18h]
  float destination[5]; // [esp+94h] [ebp-14h] BYREF

  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v14);
  rf_matrix3_construct((char *)v12);
  rf_orientation_matrix_from_normalized_direction(v12, a5);
  destination[3] = 0.0;
  destination[4] = 0.0;
  v15 = a3;
  rf_matrix3_construct_from_euler_angles((int)v13, 0.0, a3, 0.0);
  v5 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(destination, copy_result, v5);
  rf_matrix3_inverse_rotate_vector(destination, v12);
  rf_matrix3_inverse_rotate_vector(destination, v13);
  rf_vector_rotate_by_matrix3(destination, v12);
  v6 = rf_vector_add(destination, sum_result, rhs);
  return rf_vector_copy(a1, v8, v6);
}

