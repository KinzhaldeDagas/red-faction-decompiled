// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413070 rf_matrix3_argument_times_receiver_to_output
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): ECX matrixR plus output and matrixL, RET8. Computes output=L*R:each output row is argument row multiplied by receiver columns. Receiver is RIGHT factor, contrary to conventional member multiply naming. Stages all9results before constructing output, so exact output alias with either input is safe. Returns output pointer bits; corrected saved destination/return pointer typing, unchanged machine ABI.
float *__thiscall rf_matrix3_argument_times_receiver_to_output(const float *this, float *a2, const float *a3)
{
  float *v3; // eax
  float *v5; // [esp+Ch] [ebp-54h]
  float *v6; // [esp+10h] [ebp-50h]
  float v7; // [esp+14h] [ebp-4Ch]
  float v8; // [esp+18h] [ebp-48h]
  float v9; // [esp+1Ch] [ebp-44h]
  float v10; // [esp+20h] [ebp-40h]
  float v11; // [esp+24h] [ebp-3Ch]
  float v12; // [esp+28h] [ebp-38h]
  float v13; // [esp+2Ch] [ebp-34h]
  float v14; // [esp+30h] [ebp-30h]
  float v15; // [esp+34h] [ebp-2Ch]
  float v17[3]; // [esp+3Ch] [ebp-24h] BYREF
  float v18[3]; // [esp+48h] [ebp-18h] BYREF
  float v19[3]; // [esp+54h] [ebp-Ch] BYREF

  v15 = a3[6] * *(this + 2) + a3[7] * *(this + 5) + a3[8] * *(this + 8);
  v14 = a3[6] * *(this + 1) + a3[7] * *(this + 4) + a3[8] * *(this + 7);
  v13 = a3[6] * *this + a3[7] * *(this + 3) + a3[8] * *(this + 6);
  v6 = rf_vector3_set_components_return_destination(v19, v13, v14, v15);
  v12 = a3[3] * *(this + 2) + a3[4] * *(this + 5) + a3[5] * *(this + 8);
  v11 = a3[3] * *(this + 1) + a3[4] * *(this + 4) + a3[5] * *(this + 7);
  v10 = a3[3] * *this + a3[4] * *(this + 3) + a3[5] * *(this + 6);
  v5 = rf_vector3_set_components_return_destination(v18, v10, v11, v12);
  v9 = *a3 * *(this + 2) + a3[1] * *(this + 5) + a3[2] * *(this + 8);
  v8 = *a3 * *(this + 1) + a3[1] * *(this + 4) + a3[2] * *(this + 7);
  v7 = *a3 * *this + a3[1] * *(this + 3) + a3[2] * *(this + 6);
  v3 = rf_vector3_set_components_return_destination(v17, v7, v8, v9);
  rf_matrix3_construct_from_three_rows((int)a2, v3, v5, v6);
  return a2;
}

