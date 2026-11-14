// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D7D20 rf_physics_state_point_velocity_from_rotated_tensor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl(outVector,physics-state P,leverArm). Copies P212 vector,rotates it by row-major tensorP56,then out=P188+cross(rotatedP212,leverArm);returns outVector EAX. P is object136;thus P188=object324 andP212=object348. Does not simply use object336 angular vector. No mutation of P or leverArm,normalization,extra2208 addition or inverse/scalar check. Intermediate staging supports output alias with input vector/state fields used before final copy.
float *__cdecl rf_physics_state_point_velocity_from_rotated_tensor(float *sum_result, int a2, float *a3)
{
  float *v3; // eax
  float v5[3]; // [esp+0h] [ebp-18h] BYREF
  float v6[3]; // [esp+Ch] [ebp-Ch] BYREF

  rf_vector3_copy_return_destination(v6, (float *)(a2 + 212));
  rf_vector_rotate_by_matrix3(v6, (float *)(a2 + 56));
  v3 = rf_vector_cross(v6, v5, a3);
  rf_vector_add((const float *)(a2 + 188), sum_result, v3);
  return sum_result;
}

