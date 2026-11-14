// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055B1F0 rf_matrix3_determinant_x87
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): Expands3x3 determinant as m0*m4*m8+m1*m5*m6+m2*m3*m7-m2*m4*m6-m0*m5*m7-m1*m3*m8, with products staged as floats and final result rounded to float then ST0. Does not mutate matrix or test singularity tolerance.
double __thiscall rf_matrix3_determinant_x87(float *this)
{
  float v3; // [esp+8h] [ebp-18h]
  float v4; // [esp+Ch] [ebp-14h]
  float v5; // [esp+10h] [ebp-10h]
  float v6; // [esp+14h] [ebp-Ch]
  float v7; // [esp+18h] [ebp-8h]
  float v8; // [esp+1Ch] [ebp-4h]

  v8 = *this * *(this + 4) * *(this + 8);
  v6 = *(this + 1) * *(this + 5) * *(this + 6);
  v4 = *(this + 2) * *(this + 3) * *(this + 7);
  v5 = *(this + 2) * *(this + 4) * *(this + 6);
  v3 = *this * *(this + 5) * *(this + 7);
  v7 = *(this + 1) * *(this + 3) * *(this + 8);
  return (float)(v8 + v6 + v4 - v5 - v3 - v7);
}

