// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CC220 rf_particle_decode_bounciness
// UNREALRED VERIFIED [vfx-particle-lifecycle] Returns particle flag bits 16..19 divided by 16.0; authored value 15 therefore decodes to 0.9375.
double __cdecl rf_particle_decode_bounciness(int a1)
{
  return (float)((double)((*(_DWORD *)(a1 + 88) & 0xF0000) >> 16) / 16.0);
}

