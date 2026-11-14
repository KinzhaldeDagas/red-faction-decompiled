// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559730 rf_random_unit_vector_in_local_cone
// UNREALRED VERIFIED [combat-particle-emission-20261104]: Samples local z using random_float_range(minimumDot,1), then azimuth randomUnit*2pi; local x=cos(azimuth)*sqrt(1-z*z), y=sin(azimuth)*sqrt(1-z*z). No clamp inside this helper.5597C0 rotates by55C050 raw-forward basis without normalizing output. Dedicated4CD520 clamps minimumDot before calling; inline506E20 calls even when minimumDot>=1.
void __thiscall rf_random_unit_vector_in_local_cone(float *this, float a2)
{
  float v2; // [esp+8h] [ebp-10h]
  float v4; // [esp+10h] [ebp-8h]
  float v5; // [esp+14h] [ebp-4h]

  *(this + 2) = rf_random_float_range(a2, 1.0);
  v4 = sub_567730() * 6.283185482025146;
  v2 = 1.0 - *(this + 2) * *(this + 2);
  v5 = rf_sqrt_float(v2);
  *this = rf_cos_float(v4) * v5;
  *(this + 1) = rf_sin_float(v4) * v5;
}

