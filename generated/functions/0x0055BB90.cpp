// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055BB90 rf_matrix3_transpose_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): Swaps m1/m3,m2/m6,m5/m7 using scalar temporary; diagonals unchanged. Returns receiver. Does not compute determinant/inverse or normalize.
float *__thiscall rf_matrix3_transpose_in_place(float *this)
{
  float v2; // [esp+4h] [ebp-4h]
  float v3; // [esp+4h] [ebp-4h]
  float v4; // [esp+4h] [ebp-4h]

  v2 = *(this + 3);
  *(this + 3) = *(this + 1);
  *(this + 1) = v2;
  v3 = *(this + 6);
  *(this + 6) = *(this + 2);
  *(this + 2) = v3;
  v4 = *(this + 7);
  *(this + 7) = *(this + 5);
  *(this + 5) = v4;
  return this;
}

