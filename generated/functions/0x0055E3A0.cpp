// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E3A0 rf_matrix3_apply_transposed_basis_conjugate
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): ECX destination M plus matrices A,B, RET8. Using55EC10, forms T=transpose(B)*A, then T=transpose(A)*T; using413070 computes M=M*T, so un-repaired product is M*transpose(A)*transpose(B)*A. Then rebuilds basis55B770, whose final right/up are not normalized. Inputs read through temporaries before overwriting M; not a conventional M*A*B multiplication or guaranteed orthonormal transform. EAX follows rebuild copy helper.
float *__thiscall rf_matrix3_apply_transposed_basis_conjugate(float *this, const float *a2, const float *a3)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float v8[9]; // [esp+4h] [ebp-90h] BYREF
  float v9[9]; // [esp+28h] [ebp-6Ch] BYREF
  float v10[9]; // [esp+4Ch] [ebp-48h] BYREF
  float v11[9]; // [esp+70h] [ebp-24h] BYREF

  rf_matrix3_construct((char *)v11);
  v3 = rf_matrix3_transposed_argument_times_receiver_to_output(a2, v10, a3);
  rf_matrix3_copy(v11, v3);
  v4 = rf_matrix3_transposed_argument_times_receiver_to_output(v11, v9, a2);
  rf_matrix3_copy(v11, v4);
  v5 = rf_matrix3_argument_times_receiver_to_output(v11, v8, this);
  rf_matrix3_copy(this, v5);
  return (float *)rf_matrix3_rebuild_basis_from_forward_in_place(this);
}

