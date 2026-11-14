// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00410900 sub_410900
// UNREALRED VERIFIED [combat-particle-planes-20261104]: Takes a float argument, calls __CIsin at 0x410907, stores its result to a 32-bit float local at 0x41090C, and reloads that local into x87 ST0 at 0x41090F before returning. Outer wrapper 0x4108E0 preserves this float-rounded sine. In 0x531CD0 the sine is already rounded before multiplication by the stored float cone radius; that product is then stored as the local Y component at 0x531E06.
double __cdecl sub_410900(float a1)
{
  return (float)sin(a1);
}

