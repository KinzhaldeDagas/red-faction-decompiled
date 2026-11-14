// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413010 rf_force_sample44_construct_vectors_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Constructor for44-byte sampled force records calls no-op vector defaults at0(position) and+12(direction),returns receiver. Therefore initializes no bytes;strength,falloff,noise fields+24..40 remain untouched too. Build-sample function supplies values before force integration; not a zero-vector constructor.
char *__thiscall rf_force_sample44_construct_vectors_noop(char *this)
{
  rf_vector3_default_construct_noop(this);
  rf_vector3_default_construct_noop(this + 12);
  return this;
}

