// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6750 rf_snapshot_dequantize_u16_div64
// UNREALRED VERIFIED [save-validation-20261028]: Zero-extends input16, divides by64.0, rounds through float storage and returns float value in x87. Input is UNSIGNED unlike signed divide32 helper0x4F6790.
double __cdecl rf_snapshot_dequantize_u16_div64(unsigned __int16 a1)
{
  return (float)((double)a1 / 64.0);
}

