// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00513C40 sub_513C40
// UNREALRED VERIFIED [moving-shadow-receiver-20261027] Converts copied projector to current solid-local coordinates: subtract object position and inverse-rotate projector points, compose projector basis, transform all six planes with 0x513D70. 0x512C50 then clips complete LOCAL face rings, tests raw local Face+4 before transformation, computes UV in that projector frame, and transforms survivors to world using the same current position/basis. Rigid-transforming source rings to world and clipping with world projector is mathematically equivalent; do not transform raw normal-Y admission into world-up admission.
int __thiscall sub_513C40(int this, float *a2, float *a3)
{
  int result; // eax
  float v5[9]; // [esp+4h] [ebp-28h] BYREF
  int i; // [esp+28h] [ebp-4h]

  rf_vector_subtract_in_place((float *)(this + 96), a2);
  rf_matrix3_inverse_rotate_vector((float *)(this + 96), a3);
  rf_vector_subtract_in_place((float *)(this + 108), a2);
  rf_matrix3_inverse_rotate_vector((float *)(this + 108), a3);
  rf_vector_subtract_in_place((float *)(this + 120), a2);
  rf_matrix3_inverse_rotate_vector((float *)(this + 120), a3);
  for ( i = 0; i < 4; ++i )
  {
    rf_vector_subtract_in_place((float *)(this + 12 * i + 132), a2);
    rf_matrix3_inverse_rotate_vector((float *)(this + 12 * i + 132), a3);
  }
  rf_matrix3_argument_times_receiver_to_output((const float *)(this + 180), v5, a3);
  result = rf_matrix3_copy((float *)(this + 180), v5);
  for ( i = 0; i < 6; ++i )
    result = rf_plane_update_distance_then_inverse_rotate_normal((float *)(this + 16 * i), (int)a3, a2);
  *(float *)(this + 268) = 1.0;
  *(_DWORD *)(this + 272) = 0;
  return result;
}

