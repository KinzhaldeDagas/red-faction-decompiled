// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004110E0 rf_acos_scalar_round_float
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl one FLOAT argument; loads it into x87 ST0 and invokes CRT __CIacos. Stores returned ST0 to a four-byte local then reloads
// it, so the wrapper returns a FLOAT32-rounded acos through ST0 despite stored double return type. No clamp to[-1,1], finite/domain validation, degree conversion, vector access or
// caller cleanup inside this body. EAX incidental. The surrounding4110B0 wrapper is a distinct function.
double __cdecl rf_acos_scalar_round_float(float a1)
{
  return (float)acos(a1);
}

