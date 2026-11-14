// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005832E0 rf_quaternion_normalize_in_place_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Computes reciprocal of sum of squares of four float components, rounds to float, calls rf_sqrt_float, then multiplies each component by the rounded float factor. Returns receiver. Used after character bone quaternion import. No zero-length, finite-value or overflow guard; zero quaternion can produce NaNs. This is quaternion normalization, not conjugation/inversion.
float *__thiscall rf_quaternion_normalize_in_place_unchecked(float *this)
{
  float v2; // [esp+4h] [ebp-Ch]
  float v4; // [esp+Ch] [ebp-4h]

  v2 = 1.0 / (*this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2) + *(this + 3) * *(this + 3));
  v4 = rf_sqrt_float(v2);
  *this = *this * v4;
  *(this + 1) = *(this + 1) * v4;
  *(this + 2) = *(this + 2) * v4;
  *(this + 3) = *(this + 3) * v4;
  return this;
}

