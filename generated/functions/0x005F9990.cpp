// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F9990 rf_gradient_noise_2d
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Recovered original function0x5F9990..0x5F9B9D(cdecl float x,y ->float). Lazy initialization:if DWORD0x664B84 nonzero,clear it THEN call table initializer0x5F9670. Each coordinate adds4096.0 with float rounding,casts toward-zero to signedint,uses low8bits for cell and(nextInteger&255) for neighbor,fraction=shiftedCoordinate-truncatedInteger. Fractions below shifted0 are negative (not floor);no finite/range check. Interpolation uses cubic smoothstep s=f*f*(3-2*f),with float intermediates and float-rounded ST0 result. Shared tables/rand affect repeatability;no locks or final output clamp. Four corner gradients g2[p[p[ix]+iy]],dot with corresponding local displacement(xFrac orxFrac-1,yFrac oryFrac-1);lerp alongX thenY. Uses duplicated permutation table for summed indices;no octave accumulation.
float __cdecl rf_gradient_noise_2d(float x, float y)
{
  int v5; // [esp+Ch] [ebp-60h]
  float v6; // [esp+10h] [ebp-5Ch]
  float v7; // [esp+10h] [ebp-5Ch]
  int v8; // [esp+14h] [ebp-58h]
  float v9; // [esp+20h] [ebp-4Ch]
  int v10; // [esp+24h] [ebp-48h]
  float v11; // [esp+2Ch] [ebp-40h]
  float v12; // [esp+38h] [ebp-34h]
  float v13; // [esp+3Ch] [ebp-30h]
  float v14; // [esp+3Ch] [ebp-30h]
  int v15; // [esp+40h] [ebp-2Ch]
  int v16; // [esp+44h] [ebp-28h]
  float v17; // [esp+48h] [ebp-24h]
  float v18; // [esp+4Ch] [ebp-20h]
  float v19; // [esp+50h] [ebp-1Ch]
  int v20; // [esp+54h] [ebp-18h]
  float v21; // [esp+58h] [ebp-14h]
  float v22; // [esp+58h] [ebp-14h]
  float v23; // [esp+64h] [ebp-8h]
  float v24; // [esp+68h] [ebp-4h]

  if ( dword_664B84 )
  {
    dword_664B84 = 0;
    rf_gradient_noise_initialize_tables();
  }
  v6 = x + 4096.0;
  v8 = (unsigned __int8)(int)v6;
  v20 = (unsigned __int8)((int)v6 + 1);
  v9 = v6 - (double)(int)v6;
  v12 = v9 - 1.0;
  v7 = y + 4096.0;
  v10 = (unsigned __int8)(int)v7;
  v16 = (unsigned __int8)((int)v7 + 1);
  v23 = v7 - (double)(int)v7;
  v17 = v23 - 1.0;
  v15 = dword_1F67118[v8];
  v5 = dword_1F67118[v20];
  v18 = v9 * v9 * (3.0 - v9 * 2.0);
  v24 = v23 * v23 * (3.0 - v23 * 2.0);
  v13 = v9 * flt_1F69138[2 * dword_1F67118[v10 + v15]] + v23 * flt_1F69138[2 * dword_1F67118[v10 + v15] + 1];
  v21 = v12 * flt_1F69138[2 * dword_1F67118[v10 + v5]] + v23 * flt_1F69138[2 * dword_1F67118[v10 + v5] + 1];
  v19 = (v21 - v13) * v18 + v13;
  v14 = v9 * flt_1F69138[2 * dword_1F67118[v16 + v15]] + v17 * flt_1F69138[2 * dword_1F67118[v16 + v15] + 1];
  v22 = v12 * flt_1F69138[2 * dword_1F67118[v16 + v5]] + v17 * flt_1F69138[2 * dword_1F67118[v16 + v5] + 1];
  v11 = (v22 - v14) * v18 + v14;
  return (v11 - v19) * v24 + v19;
}

