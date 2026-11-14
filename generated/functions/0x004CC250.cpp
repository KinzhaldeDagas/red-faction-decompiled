// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CC250 rf_particle_decode_stickiness
// UNREALRED VERIFIED [vfx-particle-lifecycle] Returns the square of particle flag bits 20..23 divided by 16.0.
double __cdecl rf_particle_decode_stickiness(int a1)
{
  float v3; // [esp+4h] [ebp-8h]

  v3 = (double)((int)((unsigned int)&unk_F00000 & *(_DWORD *)(a1 + 88)) >> 20) / 16.0;
  return (float)(v3 * v3);
}

