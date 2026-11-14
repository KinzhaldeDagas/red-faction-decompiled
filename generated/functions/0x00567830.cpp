// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567830 rf_round_nonnegative_float_to_int
// UNREALRED VERIFIED [self-illumination-20260903]: Rounds a nonnegative float to the nearest integer by adding 0.5 and invoking the truncation-toward-zero helper __ftol2_sse. The self-illumination consumer supplies a clamped 0..255 value and retains the low byte.
// UNREALRED VERIFIED [material-alpha-byte-20260903]: Converts every nonnegative material-pass alpha to its retail byte by adding 0.5 and truncating toward zero. Mesh submission supplies values already bounded to the representable 0..255 interval.
int __cdecl rf_round_nonnegative_float_to_int(float a1)
{
  return (int)(a1 + 0.5);
}

