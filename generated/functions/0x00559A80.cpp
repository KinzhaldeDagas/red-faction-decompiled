// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559A80 rf_vector_signed_angle_about_reference
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): Unchecked-normalizes all three supplied vectors into temporaries; angle=acos(dot(unitA,unitB)). Negates angle only if dot(cross(ORIGINAL A,ORIGINAL B),unitReference)<0, otherwise positive. Returns float-rounded angle through ST0 as double. Reference supplies sign only; vectors are not projected into reference plane. No zero-vector guard or explicit dot clamp in this routine; unordered sign comparison does not negate.
double __cdecl rf_vector_signed_angle_about_reference(const float *a1, const float *a2, const float *a3)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float v8; // [esp+0h] [ebp-80h]
  float v9[3]; // [esp+4h] [ebp-7Ch] BYREF
  float v10[3]; // [esp+10h] [ebp-70h] BYREF
  float v11[3]; // [esp+1Ch] [ebp-64h] BYREF
  float v12[3]; // [esp+28h] [ebp-58h] BYREF
  float v13[3]; // [esp+34h] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+40h] [ebp-40h] BYREF
  float v15[3]; // [esp+4Ch] [ebp-34h] BYREF
  float v16[3]; // [esp+58h] [ebp-28h] BYREF
  float destination[3]; // [esp+64h] [ebp-1Ch] BYREF
  float v18[3]; // [esp+70h] [ebp-10h] BYREF
  float v19; // [esp+7Ch] [ebp-4h]

  rf_vector3_default_construct_noop(v16);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v18);
  v3 = rf_vector3_normalized_copy_unchecked((float *)a1, v15);
  rf_vector_copy(destination, copy_result, v3);
  v4 = rf_vector3_normalized_copy_unchecked((float *)a2, v13);
  rf_vector_copy(v18, v12, v4);
  v5 = rf_vector3_normalized_copy_unchecked((float *)a3, v11);
  rf_vector_copy(v16, v10, v5);
  v8 = rf_vector_dot(destination, v18);
  v19 = rf_acos_float(v8);
  v6 = rf_vector_cross((float *)a1, v9, (float *)a2);
  if ( rf_vector_dot(v6, v16) < 0.0 )
    return (float)-v19;
  return v19;
}

