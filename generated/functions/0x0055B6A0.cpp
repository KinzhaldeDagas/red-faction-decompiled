// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055B6A0 rf_matrix3_transpose_to_output
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): ECX source matrix plus destination, RET4. Stages all three source columns as local vectors and constructs destination rows from them. Returns destination bits. Source/destination may be same; diagonal and all nine components copied, no inversion/determinant operation.
int __thiscall rf_matrix3_transpose_to_output(float *this, int a2)
{
  float v4[3]; // [esp+4h] [ebp-24h] BYREF
  float v5[3]; // [esp+10h] [ebp-18h] BYREF
  float v6[3]; // [esp+1Ch] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v4);
  rf_vector3_default_construct_noop(v6);
  rf_vector3_default_construct_noop(v5);
  v6[0] = *(this + 1);
  v6[1] = *(this + 4);
  v6[2] = *(this + 7);
  v4[0] = *this;
  v4[1] = *(this + 3);
  v4[2] = *(this + 6);
  v5[0] = *(this + 2);
  v5[1] = *(this + 5);
  v5[2] = *(this + 8);
  rf_matrix3_construct_from_three_rows(a2, v4, v6, v5);
  return a2;
}

