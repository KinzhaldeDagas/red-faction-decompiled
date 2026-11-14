// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583CB0 rf_short_quaternion_dot_scaled
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl two pointers to signed16[4]. Computes four signed16 products with32-bit integer addition before float conversion,then float-multiplies exact literal0.000000003725745045812801 (approximately1/16383^2),returns float-rounded value in ST0. No clamp or normalization;sum can wrap32bits for unrestricted components. Used both as packed dot and squared norm of temporary sum/difference vectors.
double __cdecl rf_short_quaternion_dot_scaled(__int16 *a1, __int16 *a2)
{
  float v4; // [esp+8h] [ebp-4h]

  v4 = (float)(a2[3] * a1[3] + a2[2] * a1[2] + a2[1] * a1[1] + *a2 * *a1);
  return (float)(v4 * 0.000000003725745045812801);
}

