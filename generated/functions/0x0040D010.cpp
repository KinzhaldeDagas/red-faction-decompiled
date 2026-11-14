// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D010 sub_40D010
// UNREALRED VERIFIED [combat-particle-planes-20261104]: Takes a float argument, calls __CIsqrt at 0x40D017, stores its result to a 32-bit float local at 0x40D01C, and reloads that local into x87 ST0 at 0x40D01F before returning. Thus the returned value is float-rounded despite the decompiler's double return type. Outer wrapper 0x40CFF0 preserves this value. Callers such as 0x559200 consume the already-float-rounded square root before computing and storing their reciprocal; do not retain an unrounded sqrt across that caller division.
double __cdecl sub_40D010(float a1)
{
  return (float)sqrt(a1);
}

