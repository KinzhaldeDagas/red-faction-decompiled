// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005593B0 rf_vector_normalize_get_length
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): Computes float sqrt(x*x+y*y+z*z). Ordered length>0 scales XYZ by reciprocal and returns ORIGINAL float length through ST0. Otherwise writes unitX and returns1.0, including zero/NaN length: return is NOT original length on fallback. Infinite length takes scaling branch without finite check.
double __thiscall rf_vector_normalize_get_length(float *this)
{
  float v2; // [esp+4h] [ebp-10h]
  float v4; // [esp+Ch] [ebp-8h]
  float v5; // [esp+10h] [ebp-4h]

  v2 = *this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2);
  v5 = rf_sqrt_float(v2);
  if ( v5 > 0.0 )
  {
    v4 = 1.0 / v5;
    *this = *this * v4;
    *(this + 1) = *(this + 1) * v4;
    *(this + 2) = *(this + 2) * v4;
    return v5;
  }
  else
  {
    *this = 1.0;
    *(this + 1) = 0.0;
    *(this + 2) = 0.0;
    return 1.0;
  }
}

