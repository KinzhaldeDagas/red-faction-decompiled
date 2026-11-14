// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558EF0 rf_vector3_normalized_copy_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX sourceXYZ plus destinationXYZ, RET4. Computes float length squared, sqrt, reciprocal with NO zero/NaN/finite check; writes source components times reciprocal to output and returns output. Zero vector can yield NaNs; all three output components calculated before stores, so destination may alias source.
float *__thiscall rf_vector3_normalized_copy_unchecked(float *this, float *a2)
{
  float v3; // [esp+Ch] [ebp-18h]
  float v4; // [esp+10h] [ebp-14h]
  float v5; // [esp+14h] [ebp-10h]
  float v6; // [esp+18h] [ebp-Ch]
  float v8; // [esp+20h] [ebp-4h]

  v6 = *this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2);
  v8 = 1.0 / rf_sqrt_float(v6);
  v5 = *(this + 2) * v8;
  v4 = *(this + 1) * v8;
  v3 = *this * v8;
  rf_vector3_set_components_return_destination(a2, v3, v4, v5);
  return a2;
}

