// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004108C0 sub_4108C0
// UNREALRED VERIFIED [combat-particle-planes-20261104]: Takes a float argument, calls __CIcos at 0x4108C7, stores its result to a 32-bit float local at 0x4108CC, and reloads that local into x87 ST0 at 0x4108CF before returning. Outer wrapper 0x4108A0 preserves this float-rounded cosine. In 0x531CD0 the cosine is already rounded before multiplication by the stored float cone radius; that product is then stored as the local X component at 0x531DEF.
double __cdecl sub_4108C0(float a1)
{
  return (float)cos(a1);
}

