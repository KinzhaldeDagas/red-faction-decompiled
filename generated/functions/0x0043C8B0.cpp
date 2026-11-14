// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C8B0 rf_atan_float_wrapper
// UNREALRED VERIFIED [renderer-mesh-20261028]: Direct floatargument wrapper around0x43C8D0,whose body calls __CIatan. Existing ?log@@YAMM@Z_4 library name was false: this computes arctangent,not natural logarithm. Leaves x87 result for caller; no additional range handling.
double __cdecl rf_atan_float_wrapper(float a1)
{
  return rf_atan_float_via_x87_intrinsic(a1);
}

