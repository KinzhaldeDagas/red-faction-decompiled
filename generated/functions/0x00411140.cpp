// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00411140 rf_vector3_divide_in_place_reciprocal
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): ECX vector plus scalar float, RET4. Computes float reciprocal1/scalar then multiplies all XYZ in place, returns receiver. No zero/NaN/finite guard; this can differ in rounding from three direct divisions.
float *__thiscall rf_vector3_divide_in_place_reciprocal(float *this, float a2)
{
  float v3; // [esp+4h] [ebp-4h]

  v3 = 1.0 / a2;
  *this = *this * v3;
  *(this + 1) = *(this + 1) * v3;
  *(this + 2) = *(this + 2) * v3;
  return this;
}

