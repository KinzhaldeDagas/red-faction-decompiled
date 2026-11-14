// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00584860 rf_float4_subtract_to_destination
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Thiscall left float4,stack destination/right. Computes all four left-minus-right components into float locals before writing destination. Returns destination; exact aliasing supported by read-before-write temporaries. No normalization, rotation composition or clamping.
float *__thiscall rf_float4_subtract_to_destination(float *this, float *a2, float *a3)
{
  float v4; // [esp+10h] [ebp-14h]
  float v5; // [esp+14h] [ebp-10h]
  float v6; // [esp+18h] [ebp-Ch]
  float v7; // [esp+1Ch] [ebp-8h]

  v7 = *(this + 3) - a3[3];
  v6 = *(this + 2) - a3[2];
  v5 = *(this + 1) - a3[1];
  v4 = *this - *a3;
  rf_float4_construct_components(a2, v4, v5, v6, v7);
  return a2;
}

