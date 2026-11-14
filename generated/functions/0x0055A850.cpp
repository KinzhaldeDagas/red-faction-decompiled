// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A850 rf_matrix3_construct_from_euler_angles
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): ECX matrix plus(pitch,bank,heading) floats, RET12. No-op row constructors then55A9A0 with SAME destination receiver. Returns matrix bits; old callee stdcall signature hid receiver in pseudocode, now corrected. No identity prefill or angle-unit conversion; angles passed to native sin/cos.
int __thiscall rf_matrix3_construct_from_euler_angles(int this, float a2, float a3, float a4)
{
  rf_vector3_default_construct_noop((void *)this);
  rf_vector3_default_construct_noop((void *)(this + 12));
  rf_vector3_default_construct_noop((void *)(this + 24));
  rf_matrix3_set_euler_angles((float *)this, a2, a3, a4);
  return this;
}

