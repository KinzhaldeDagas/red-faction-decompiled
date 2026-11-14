// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C2690 rf_explosion_sample_direct_particle_prototype
// UNREALRED VERIFIED [combat-particle-emission-20261104]: Direct explosion prototype helper samples particle lifetime(+0x38..0x3C), an initial velocity magnitude(+0x20..0x24), then radius(+0x40..0x44).4C2790 sparks reuse one such prototype for whole group, overwrite position with graph origin and velocity per spark, scale prototype radius by effect size but leave life unscaled. Shared radius/life are not independently redrawn per spark.
// UNREALRED VERIFIED (2026-11-11; native producer/consumer offsets): class56..60 sample goes to descriptor40 -> live lifetime52 (4CD24E/4CD251); class64..68 sample goes to descriptor24 -> live radius56 (4CD242/4CD245). Direct graph sparks/head/update scale descriptor24 radius; descriptor40 lifetime remains unscaled. Existing producer-label reversal corrected from original instructions, code unchanged.
int __cdecl rf_explosion_sample_direct_particle_prototype(int a1, int a2)
{
  float *v2; // eax
  double v3; // st7
  float scalar; // [esp+4h] [ebp-1Ch]
  float copy_result[3]; // [esp+8h] [ebp-18h] BYREF
  float scaled_result[3]; // [esp+14h] [ebp-Ch] BYREF

  *(float *)(a2 + 32) = *(float *)(a1 + 76);
  *(_DWORD *)(a2 + 44) = *(_DWORD *)(a1 + 100);
  *(_DWORD *)(a2 + 52) = *(_DWORD *)(a1 + 108);
  *(_DWORD *)(a2 + 56) = *(_DWORD *)(a1 + 112);
  *(_DWORD *)(a2 + 60) = *(_DWORD *)(a1 + 116);
  *(_DWORD *)(a2 + 64) = *(_DWORD *)(a1 + 120);
  *(float *)(a2 + 36) = *(float *)(a1 + 80);
  *(float *)(a2 + 28) = *(float *)(a1 + 72);
  *(float *)(a2 + 40) = rf_random_float_range(*(float *)(a1 + 56), *(float *)(a1 + 60));
  *(_DWORD *)(a2 + 48) = *(_DWORD *)(a1 + 104);
  scalar = rf_random_float_range(*(float *)(a1 + 32), *(float *)(a1 + 36));
  v2 = rf_vector_multiply_scalar((const float *)(a1 + 16), scaled_result, scalar);
  rf_vector_copy((float *)(a2 + 12), copy_result, v2);
  v3 = rf_random_float_range(*(float *)(a1 + 64), *(float *)(a1 + 68));
  *(float *)(a2 + 24) = v3;
  return a2;
}

