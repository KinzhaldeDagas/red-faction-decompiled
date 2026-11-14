// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528D80 rf_nonworld_light_attenuation_linear
// VERIFIED: Non-world attenuation selector 0: x = (range-distance)/range.
// UNREALRED VERIFIED [general-gap-20260830]: Non-world light attenuation selector 0: (range-distance)/range.
double __cdecl rf_nonworld_light_attenuation_linear(float a1, float a2)
{
  return (float)((a2 - a1) / a2);
}

