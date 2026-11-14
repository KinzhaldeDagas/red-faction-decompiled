// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F95A0 rf_gradient_noise_1d
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Recovered original function0x5F95A0..0x5F966C(cdecl float x ->float). Lazy initialization:if DWORD0x664B84 nonzero,clear it THEN call table initializer0x5F9670. Each coordinate adds4096.0 with float rounding,casts toward-zero to signedint,uses low8bits for cell and(nextInteger&255) for neighbor,fraction=shiftedCoordinate-truncatedInteger. Fractions below shifted0 are negative (not floor);no finite/range check. Interpolation uses cubic smoothstep s=f*f*(3-2*f),with float intermediates and float-rounded ST0 result. Shared tables/rand affect repeatability;no locks or final output clamp. Endpoint dot terms are fraction*g1[p[cell]] and(fraction-1)*g1[p[next]],lerped bys. No amplitude normalization or octave accumulation.
float __cdecl rf_gradient_noise_1d(float x)
{
  float v4; // [esp+8h] [ebp-24h]
  float v5; // [esp+10h] [ebp-1Ch]
  float v6; // [esp+14h] [ebp-18h]
  float v7; // [esp+18h] [ebp-14h]
  float v8; // [esp+1Ch] [ebp-10h]
  float v9; // [esp+24h] [ebp-8h]

  if ( dword_664B84 )
  {
    dword_664B84 = 0;
    rf_gradient_noise_initialize_tables();
  }
  v4 = x + 4096.0;
  v5 = v4 - (double)(int)v4;
  v6 = v5 - 1.0;
  v8 = v5 * v5 * (3.0 - v5 * 2.0);
  v7 = v5 * flt_1F6A148[dword_1F67118[(unsigned __int8)(int)v4]];
  v9 = v6 * flt_1F6A148[dword_1F67118[(unsigned __int8)((int)v4 + 1)]];
  return (v9 - v7) * v8 + v7;
}

