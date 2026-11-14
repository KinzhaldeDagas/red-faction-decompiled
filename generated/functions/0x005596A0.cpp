// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005596A0 rf_random_unit_vector
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): Writes z=random_float_range(-1,1), azimuth=randomUnit567730*float2pi, radial=sqrt(1-z*z), x=cos(azimuth)*radial,y=sin(azimuth)*radial. Underlying randomUnit is float(CRT rand)/32768; no post-normalization, rejection sampling or explicit sqrt-domain clamp.
void __thiscall rf_random_unit_vector(float *this)
{
  float v1; // [esp+8h] [ebp-10h]
  float v3; // [esp+10h] [ebp-8h]
  float v4; // [esp+14h] [ebp-4h]

  *(this + 2) = rf_random_float_range(-1.0, 1.0);
  v3 = sub_567730() * 6.283185482025146;
  v1 = 1.0 - *(this + 2) * *(this + 2);
  v4 = rf_sqrt_float(v1);
  *this = rf_cos_float(v3) * v4;
  *(this + 1) = rf_sin_float(v3) * v4;
}

