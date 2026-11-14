// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A8A0 rf_matrix3_construct_from_axis_angle
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): ECX matrix plus axisXYZ and angleRadians, RET8. No-op row constructors then55AA50 axis-angle builder. Returns receiver bits; no axis normalization before delegate.
int __thiscall rf_matrix3_construct_from_axis_angle(int this, float *a2, float a3)
{
  rf_vector3_default_construct_noop((void *)this);
  rf_vector3_default_construct_noop((void *)(this + 12));
  rf_vector3_default_construct_noop((void *)(this + 24));
  rf_matrix3_set_axis_angle_unchecked_axis((float *)this, a2, a3);
  return this;
}

