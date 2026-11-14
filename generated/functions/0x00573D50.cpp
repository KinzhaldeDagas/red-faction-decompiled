// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573D50 rf_pow_float_forward
// UNREALRED VERIFIED [character-pipeline-20261029]: cdecl float base,exponent. Forwards to0x573D70 and returns float. Original _hypotf_0 label was misleading: callee loads both floats and invokes x87 __CIpow,not square-root of sum of squares. No domain checking or extra application arithmetic.
float __cdecl rf_pow_float_forward(float X, float Y)
{
  return rf_pow_float_via_x87_intrinsic(X, Y);
}

