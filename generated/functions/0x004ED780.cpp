// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ED780 rf_tan_float
// UNREALRED VERIFIED [projected-shadow-cone-20260903]: Single-precision tan wrapper. Its inherited decorated log label was false; the core calls __CItan.
double __cdecl rf_tan_float(float a1)
{
  return rf_tan_float_core(a1);
}

