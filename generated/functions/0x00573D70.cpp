// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573D70 rf_pow_float_via_x87_intrinsic
// UNREALRED VERIFIED [character-pipeline-20261029]: cdecl float base,exponent. FLD base then exponent,calls __CIpow,stores result to FLOAT local and reloads into st0. Thus returns float-rounded power,not full double precision. No explicit domain or error handling; does not implement hypot.
double __cdecl rf_pow_float_via_x87_intrinsic(float a1, float a2)
{
  return (float)pow(a1, a2);
}

