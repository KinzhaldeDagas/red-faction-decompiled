// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F67B0 rf_snapshot_quantize_float_times8
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Multiply float argument by double8.0 then __ftol2_sse truncation toward zero; return full integer. Common header stores low16 bits for life/armor after independently clamping live owner values. No intrinsic clamp,16-bit mask or half-unit rounding inside helper.
int __cdecl rf_snapshot_quantize_float_times8(float a1)
{
  return (int)(a1 * 8.0);
}

