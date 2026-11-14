// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005847A0 rf_float4_negate_to_destination
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Thiscall source float[4],stack destination. Reads/negates all four components into float locals before constructing destination, then returns destination. Safe for exact aliasing due temporary reads; this is full quaternion sign negation, not conjugation (w is negated too). No normalization.
float *__thiscall rf_float4_negate_to_destination(float *this, float *a2)
{
  float v3; // [esp+0h] [ebp-14h]
  float v4; // [esp+4h] [ebp-10h]
  float v5; // [esp+8h] [ebp-Ch]
  float v6; // [esp+Ch] [ebp-8h]

  v6 = -*(this + 3);
  v5 = -*(this + 2);
  v4 = -*(this + 1);
  v3 = -*this;
  rf_float4_construct_components(a2, v3, v4, v5, v6);
  return a2;
}

