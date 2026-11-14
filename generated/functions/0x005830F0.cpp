// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005830F0 rf_quaternion_conjugate_to_destination
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Copies(-x,-y,-z,w) to output through component constructor,returns output. No normalization or divide by squared norm,so not a general non-unit inverse. Reads component values before destination stores,permitting exact alias. Distinct from full four-component sign negation.
float *__thiscall rf_quaternion_conjugate_to_destination(float *this, float *a2)
{
  float v3; // [esp+0h] [ebp-14h]
  float v4; // [esp+4h] [ebp-10h]
  float v5; // [esp+8h] [ebp-Ch]

  v5 = -*(this + 2);
  v4 = -*(this + 1);
  v3 = -*this;
  rf_float4_construct_components(a2, v3, v4, v5, *(this + 3));
  return a2;
}

