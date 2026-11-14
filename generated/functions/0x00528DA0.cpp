// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528DA0 rf_nonworld_light_attenuation_squared
// VERIFIED: Non-world attenuation selector 1: x = ((range-distance)/range)^2.
// UNREALRED VERIFIED [general-gap-20260830]: Non-world light attenuation selector 1: ((range-distance)/range)^2.
double __cdecl rf_nonworld_light_attenuation_squared(float a1, float a2)
{
  float v4; // [esp+4h] [ebp-4h]

  v4 = (a2 - a1) / a2;
  return (float)(v4 * v4);
}

