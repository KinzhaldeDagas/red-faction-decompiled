// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055BEA0 rf_identity_orientation_matrix
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): Writes all nine row-major float components exactly diag1/offdiag0 and returns receiver. No allocation, existing value dependence, or translation fields touched.
float *__thiscall rf_identity_orientation_matrix(float *this)
{
  *this = 1.0;
  *(this + 1) = 0.0;
  *(this + 2) = 0.0;
  *(this + 3) = 0.0;
  *(this + 4) = 1.0;
  *(this + 5) = 0.0;
  *(this + 6) = 0.0;
  *(this + 7) = 0.0;
  *(this + 8) = 1.0;
  return this;
}

