// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D52B0 rf_physics_body_commit_full_step
// UNREALRED VERIFIED [trigger-geometry-20261020] Full-step commit copies predicted+0xF0 into current+0xE4 before rebuilding body bounds. This establishes that the trigger query arguments at505ED0 are physics motion endpoints, rather than bounds minima/maxima.
float *__cdecl rf_physics_body_commit_full_step(int a1)
{
  float *v1; // eax
  float *v2; // eax
  float v4[3]; // [esp+4h] [ebp-3Ch] BYREF
  int v5[3]; // [esp+10h] [ebp-30h] BYREF
  float v6[3]; // [esp+1Ch] [ebp-24h] BYREF
  int v7[3]; // [esp+28h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+34h] [ebp-Ch] BYREF

  rf_vector_copy((float *)(a1 + 228), copy_result, (const float *)(a1 + 240));
  rf_matrix3_copy((float *)(a1 + 252), (const float *)(a1 + 288));
  rf_matrix3_copy((float *)(a1 + 72), (const float *)(a1 + 252));
  rf_physics_state_rebuild_rotated_tensor(a1 + 136);
  *(float *)(a1 + 460) = 1.0;
  v1 = rf_vector3_subtract_scalar_from_components((float *)(a1 + 228), (float *)v7, *(float *)(a1 + 384));
  rf_vector_copy((float *)(a1 + 400), v6, v1);
  v2 = rf_vector3_add_scalar_to_components((float *)(a1 + 228), (float *)v5, *(float *)(a1 + 384));
  return rf_vector_copy((float *)(a1 + 412), v4, v2);
}

