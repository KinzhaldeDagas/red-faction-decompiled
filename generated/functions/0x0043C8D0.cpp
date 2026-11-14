// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C8D0 rf_atan_float_via_x87_intrinsic
// UNREALRED VERIFIED [renderer-mesh-20261028]: Loads callerfloat toST0,calls __CIatan0x606B30,stores result to32-bitfloat and reloads for return. Returns float-rounded arctangent in x87; no degree conversion or quadrant adjustment.
double __cdecl rf_atan_float_via_x87_intrinsic(float a1)
{
  return (float)atan(a1);
}

