// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055B000 rf_matrix3_has_exact_zero_row_or_column
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): Returns32-bit boolean1 if ANY of three matrix rows OR three columns consists entirely of exact floating0, else0. Tests forward row first, then right/up, then columns. Not a determinant/singularity/orthonormality test: dependent nonzero rows can returnfalse. +/-0 compare equal; no epsilon or finite guard.
int __thiscall rf_matrix3_has_exact_zero_row_or_column(const float *this)
{
  if ( *(this + 6) == 0.0 && *(this + 7) == 0.0 && *(this + 8) == 0.0 )
    return 1;
  if ( *this == 0.0 && *(this + 1) == 0.0 && *(this + 2) == 0.0 )
    return 1;
  if ( *(this + 3) == 0.0 && *(this + 4) == 0.0 && *(this + 5) == 0.0 )
    return 1;
  if ( *(this + 6) == 0.0 && *this == 0.0 && *(this + 3) == 0.0 )
    return 1;
  if ( *(this + 7) == 0.0 && *(this + 1) == 0.0 && *(this + 4) == 0.0 )
    return 1;
  return *(this + 8) == 0.0 && *(this + 2) == 0.0 && *(this + 5) == 0.0;
}

