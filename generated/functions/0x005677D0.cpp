// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005677D0 rf_random_float_range
// UNREALRED VERIFIED [combat-particle-range-20261104]: Calls567730 unconditionally BEFORE linear mapping lower+(upper-lower)*U. No endpoint sorting, comparison or equal/near-equal early return exists. Equal bounds still advance RNG once; reversed bounds retain their authored orientation. Correct prior inclusive-interval wording:567730 returns masked15bitrand/32768, so U in[0,1); the unit sampler excludes 1, while final single-precision rounding at5677E8 can still produce a range endpoint (notably narrow ranges); equal-bound result is that bound. Unreal stream identity/quantization remains a separate adaptation.
// UNREALRED VERIFIED [combat-native-pickup-runtime-20261111]: Consumes unit567730 once unconditionally, even equal/reversed bounds. Unit local isF32; evaluate lower+(upper-lower)*unit with no intermediate F32 width store, finalF32 at5677E8. Unit is exact float(masked15bitrand)/32768. Shared CRT stream; no endpoint sorting or FMath early-return.518F60 uses for native endpoint sampling.
double __cdecl rf_random_float_range(float a1, float a2)
{
  float v3; // [esp+0h] [ebp-4h]

  v3 = sub_567730();
  return (float)((a2 - a1) * v3 + a1);
}

