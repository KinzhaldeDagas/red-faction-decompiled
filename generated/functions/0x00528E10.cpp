// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528E10 rf_nonworld_light_attenuation_sqrt
// VERIFIED: Non-world attenuation selector 3: sqrt((range-distance)/range). IDA's imported log name is wrong; this helper reaches the verified square-root core.
// UNREALRED VERIFIED [general-gap-20260830]: Non-world light attenuation selector 3: sqrt((range-distance)/range).
double __cdecl rf_nonworld_light_attenuation_sqrt(float a1, float a2)
{
  float v3; // [esp+4h] [ebp-4h]

  v3 = (a2 - a1) / a2;
  return rf_sqrt_float(v3);
}

