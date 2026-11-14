// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A7F0 rf_matrix3_construct_from_euler_sincos
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): ECX matrix plus six floats(sinPitch,cosPitch,sinBank,cosBank,sinHeading,cosHeading), RET24. No-op row constructors then55A8F0 component builder. Returns receiver bits; supplied pairs not normalized/validated and no trig calls here.
float *__thiscall rf_matrix3_construct_from_euler_sincos(
        float *this,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7)
{
  rf_vector3_default_construct_noop(this);
  rf_vector3_default_construct_noop(this + 3);
  rf_vector3_default_construct_noop(this + 6);
  rf_matrix3_set_euler_sincos(this, a2, a3, a4, a5, a6, a7);
  return this;
}

