// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558E80 rf_vector3_components_are_not_nan
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): Returns32-bit boolean true only if _isnan returns false for all three XYZ components, short-circuiting at first NaN. Infinity is accepted; not a finite-vector test or normalization check.
BOOL __thiscall rf_vector3_components_are_not_nan(float *this)
{
  return !_isnan(*this) && !_isnan(*(this + 1)) && !_isnan(*(this + 2));
}

