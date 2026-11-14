// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6730 rf_snapshot_quantize_float_times64
// UNREALRED VERIFIED [save-validation-20261028]: Returns integer truncation toward zero of float argument*64.0 via ftol2_sse. No clamping or saturation; callers determine stored width.
int __cdecl rf_snapshot_quantize_float_times64(float a1)
{
  return (int)(a1 * 64.0);
}

