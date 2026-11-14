// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528DD0 rf_nonworld_light_attenuation_cosine
// VERIFIED: Non-world attenuation selector 2: cos((distance/range)*pi/2). IDA's imported log name is wrong; this helper reaches the verified cosine core.
// UNREALRED VERIFIED [general-gap-20260830]: Non-world light attenuation selector 2: cos((distance/range)*pi/2).
double __cdecl rf_nonworld_light_attenuation_cosine(float a1, float a2)
{
  float v3; // [esp+4h] [ebp-4h]
  float v4; // [esp+4h] [ebp-4h]
  float v5; // [esp+4h] [ebp-4h]

  v3 = (a2 - a1) / a2;
  v4 = 1.0 - v3;
  v5 = v4 * 1.570796370506287;
  return rf_cos_float(v5);
}

