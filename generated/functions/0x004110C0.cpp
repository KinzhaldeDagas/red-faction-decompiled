// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004110C0 rf_acos_float
// UNREALRED VERIFIED [projected-shadow-cone-20260903]: Single-precision acos wrapper. Its inherited decorated log label was false; the core calls __CIacos.
double __cdecl rf_acos_float(float a1)
{
  return rf_acos_scalar_round_float(a1);
}

