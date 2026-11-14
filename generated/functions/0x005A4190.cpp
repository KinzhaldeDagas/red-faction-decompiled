// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4190 rf_float_to_byte_add_12582912_bits
// UNREALRED VERIFIED [face-batch-20261028]: Adds float argument to12582912.0,stores rounded float and returns least-significant BYTE of float representation as zero-extended int. This is a bit-trick conversion,not integer truncation or saturation. No range/finite/rounding-mode checks; callers supply bounded values when required.
int __cdecl rf_float_to_byte_add_12582912_bits(float a1)
{
  float v2; // [esp+0h] [ebp-4h]

  v2 = a1 + 12582912.0;
  return LOBYTE(v2);
}

