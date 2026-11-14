// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055B1A0 rf_matrix3_components_are_not_nan
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): Short-circuits vector not-NaN checks in row order forward24,up12,right0. Returns32-bit boolean false on first NaN component. Infinities are accepted; not a finite or orthonormal matrix check.
int __thiscall rf_matrix3_components_are_not_nan(const float *this)
{
  return rf_vector3_components_are_not_nan((float *)this + 6)
      && rf_vector3_components_are_not_nan((float *)this + 3)
      && rf_vector3_components_are_not_nan((float *)this);
}

