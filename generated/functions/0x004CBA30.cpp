// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CBA30 sub_4CBA30
// UNREALRED VERIFIED [burn-motion-20261029]: Particle swirl minimum-dot is1-(nibble/64)^2, where nibble=(particle.flags+0x58>>24)&15. Particle update applies this cone to CURRENT velocity, preserving its scalar speed before optional acceleration.
double __cdecl sub_4CBA30(int a1)
{
  float v3; // [esp+4h] [ebp-8h]

  v3 = (double)((*(_DWORD *)(a1 + 88) & 0xF000000) >> 24) / 64.0;
  return (float)(1.0 - v3 * v3);
}

