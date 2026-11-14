// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F67D0 rf_snapshot_dequantize_s16_div8
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Interpret signed16-bit input, divide by double8.0, round through float local and return x87 result. Common life/armor quantization resolution1/8. Does not clamp input to writer life/armor range.
double __cdecl rf_snapshot_dequantize_s16_div8(__int16 a1)
{
  return (float)((double)a1 / 8.0);
}

