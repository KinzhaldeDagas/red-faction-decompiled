// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00582250 rf_plane4_transform_rows_offset_legacy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Thiscall source plane(n.xyz,d),output4f,matrix9f,translation3f. Builds temporary p=n*d+translation;temporary scalar=dot(SOURCE n,p). Temporary normal=row-dot transform(matrix,n),then copies4floats to output. Thus output=(M*n,dot(n,n*d+t));offset uses source normal,not transformed normal,and positive n*d point. Preserve actual formula rather than substituting standard inverse-transpose plane transform. No normal normalization,unit-length,invertibility or finite check. Temporaries precede output copy;returns output.
float *__thiscall rf_plane4_transform_rows_offset_legacy(float *this, float *a2, float *a3, float *a4)
{
  float *v4; // eax
  float copy_result[3]; // [esp+8h] [ebp-34h] BYREF
  float v8[3]; // [esp+14h] [ebp-28h] BYREF
  float scaled_result[3]; // [esp+20h] [ebp-1Ch] BYREF
  float destination[4]; // [esp+2Ch] [ebp-10h] BYREF

  rf_vector_prefix_construct_noop(destination);
  rf_vector_multiply_scalar(this, scaled_result, *(this + 3));
  rf_vector_accumulate(scaled_result, a4);
  destination[3] = rf_vector_dot(this, scaled_result);
  v4 = rf_vector3_transform_by_matrix_rows(this, v8, a3);
  rf_vector_copy(destination, copy_result, v4);
  rf_plane4_copy_normal_scalar(a2, destination);
  return a2;
}

