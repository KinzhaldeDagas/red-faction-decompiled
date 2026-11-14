// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00513D70 rf_plane_update_distance_then_inverse_rotate_normal
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Thiscall plane4f,matrix3*,translation3f*,RET8. Using ORIGINAL normal n and scalar d,storeF32 temp=n*d,accumulate translation with F32 components,then storeF32 plane.d=dot(n,temp). Only afterward replace plane.normal with dot products against the three matrix ROWS via5594A0. Equivalent dnew=(n dot n)*d+n dot translation subject to F32 temporaries;not a generic normalized plane transform,does not negate translation or divide by normal length. No normalization/finite guards;arbitrary plane/matrix/translation aliasing is not snapshotted. Forwards helper EAX=MATRIX pointer,not plane,as5594A0 returns argument.
float *__thiscall rf_plane_update_distance_then_inverse_rotate_normal(float *this, float *a2, float *a3)
{
  float scaled_result[3]; // [esp+8h] [ebp-Ch] BYREF

  rf_vector_multiply_scalar(this, scaled_result, *(this + 3));
  rf_vector_accumulate(scaled_result, a3);
  *(this + 3) = rf_vector_dot(this, scaled_result);
  return rf_matrix3_inverse_rotate_vector(this, a2);
}

