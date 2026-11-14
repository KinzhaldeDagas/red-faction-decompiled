// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EC10 rf_matrix3_transposed_argument_times_receiver_to_output
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): ECX receiver R plus destination and argument A, RET8. Output=transpose(A)*R; each output row is source ARGUMENT COLUMN multiplied by receiver columns. All9results staged in local row vectors before output constructor, so exact output alias with either input safe. Distinct from413070 which computes A*R without transpose. EAX destination bits.
float *__thiscall rf_matrix3_transposed_argument_times_receiver_to_output(
        const float *this,
        float *a2,
        const float *a3)
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

  v15 = a3[2] * *(this + 2) + a3[5] * *(this + 5) + a3[8] * *(this + 8);
  v14 = a3[2] * *(this + 1) + a3[5] * *(this + 4) + a3[8] * *(this + 7);
  v13 = a3[2] * *this + a3[5] * *(this + 3) + a3[8] * *(this + 6);
  v6 = rf_vector3_set_components_return_destination(v19, v13, v14, v15);
  v12 = a3[1] * *(this + 2) + a3[4] * *(this + 5) + a3[7] * *(this + 8);
  v11 = a3[1] * *(this + 1) + a3[4] * *(this + 4) + a3[7] * *(this + 7);
  v10 = a3[1] * *this + a3[4] * *(this + 3) + a3[7] * *(this + 6);
  v5 = rf_vector3_set_components_return_destination(v18, v10, v11, v12);
  v9 = *a3 * *(this + 2) + a3[3] * *(this + 5) + a3[6] * *(this + 8);
  v8 = *a3 * *(this + 1) + a3[3] * *(this + 4) + a3[6] * *(this + 7);
  v7 = *a3 * *this + a3[3] * *(this + 3) + a3[6] * *(this + 6);
  v3 = rf_vector3_set_components_return_destination(v17, v7, v8, v9);
  rf_matrix3_construct_from_three_rows((int)a2, v3, v5, v6);
  return a2;
}

