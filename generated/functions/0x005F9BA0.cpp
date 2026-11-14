// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F9BA0 rf_gradient_noise_3d
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl float x,y,z ->float-rounded ST0. Lazy initialization:if DWORD0x664B84 nonzero,clear it THEN call table initializer0x5F9670. Each coordinate adds4096.0 with float rounding,casts toward-zero to signedint,uses low8bits for cell and(nextInteger&255) for neighbor,fraction=shiftedCoordinate-truncatedInteger. Fractions below shifted0 are negative (not floor);no finite/range check. Interpolation uses cubic smoothstep s=f*f*(3-2*f),with float intermediates and float-rounded ST0 result. Shared tables/rand affect repeatability;no locks or final output clamp. Eight corners use gradients g3[p[p[ix]+iy]+iz],with NO extra permutation on Z-summed index;duplicates support up to510. Dot3 local displacements,lerp four X pairs,two Y results,thenZ. No octave accumulation or guaranteed [-1,1] clamp.
double __cdecl rf_gradient_noise_3d(float a1, float a2, float a3)
{
  int v5; // [esp+10h] [ebp-7Ch]
  float v6; // [esp+14h] [ebp-78h]
  float v7; // [esp+18h] [ebp-74h]
  float v8; // [esp+18h] [ebp-74h]
  float v9; // [esp+18h] [ebp-74h]
  float v10; // [esp+18h] [ebp-74h]
  int v11; // [esp+1Ch] [ebp-70h]
  int v12; // [esp+20h] [ebp-6Ch]
  int v13; // [esp+24h] [ebp-68h]
  float v14; // [esp+28h] [ebp-64h]
  float v15; // [esp+2Ch] [ebp-60h]
  float v16; // [esp+30h] [ebp-5Ch]
  int v17; // [esp+34h] [ebp-58h]
  int v18; // [esp+38h] [ebp-54h]
  float v19; // [esp+3Ch] [ebp-50h]
  float v20; // [esp+40h] [ebp-4Ch]
  int v21; // [esp+44h] [ebp-48h]
  float v22; // [esp+48h] [ebp-44h]
  float v23; // [esp+48h] [ebp-44h]
  int v24; // [esp+50h] [ebp-3Ch]
  float v25; // [esp+54h] [ebp-38h]
  float v26; // [esp+58h] [ebp-34h]
  float v27; // [esp+58h] [ebp-34h]
  float v28; // [esp+58h] [ebp-34h]
  float v29; // [esp+58h] [ebp-34h]
  int v30; // [esp+5Ch] [ebp-30h]
  int v31; // [esp+60h] [ebp-2Ch]
  float v32; // [esp+64h] [ebp-28h]
  float v33; // [esp+68h] [ebp-24h]
  float v34; // [esp+68h] [ebp-24h]
  int v35; // [esp+6Ch] [ebp-20h]
  int v36; // [esp+70h] [ebp-1Ch]
  float v37; // [esp+74h] [ebp-18h]
  float v38; // [esp+74h] [ebp-18h]
  float v39; // [esp+74h] [ebp-18h]
  float v40; // [esp+74h] [ebp-18h]
  float v41; // [esp+84h] [ebp-8h]
  float v42; // [esp+88h] [ebp-4h]

  if ( dword_664B84 )
  {
    dword_664B84 = 0;
    rf_gradient_noise_initialize_tables();
  }
  v7 = a1 + 4096.0;
  v11 = (unsigned __int8)(int)v7;
  v35 = (unsigned __int8)((int)v7 + 1);
  v14 = v7 - (double)(int)v7;
  v25 = v14 - 1.0;
  v8 = a2 + 4096.0;
  v17 = (unsigned __int8)(int)v8;
  v31 = (unsigned __int8)((int)v8 + 1);
  v41 = v8 - (double)(int)v8;
  v32 = v41 - 1.0;
  v9 = a3 + 4096.0;
  v21 = (unsigned __int8)(int)v9;
  v36 = (unsigned __int8)((int)v9 + 1);
  v19 = v9 - (double)(int)v9;
  v20 = v19 - 1.0;
  v30 = dword_1F67118[v11];
  v5 = dword_1F67118[v35];
  v18 = dword_1F67118[v17 + v30];
  v12 = dword_1F67118[v17 + v5];
  v13 = dword_1F67118[v31 + v30];
  v24 = dword_1F67118[v31 + v5];
  v10 = v14 * v14 * (3.0 - v14 * 2.0);
  v42 = v41 * v41 * (3.0 - v41 * 2.0);
  v6 = v19 * v19 * (3.0 - v19 * 2.0);
  v26 = v14 * unk_1F67920[3 * v21 + 3 * v18]
      + v41 * unk_1F67920[3 * v21 + 1 + 3 * v18]
      + v19 * unk_1F67920[3 * v21 + 2 + 3 * v18];
  v37 = v25 * unk_1F67920[3 * v21 + 3 * v12]
      + v41 * unk_1F67920[3 * v21 + 1 + 3 * v12]
      + v19 * unk_1F67920[3 * v21 + 2 + 3 * v12];
  v33 = (v37 - v26) * v10 + v26;
  v27 = v14 * unk_1F67920[3 * v21 + 3 * v13]
      + v32 * unk_1F67920[3 * v21 + 1 + 3 * v13]
      + v19 * unk_1F67920[3 * v21 + 2 + 3 * v13];
  v38 = v25 * unk_1F67920[3 * v21 + 3 * v24]
      + v32 * unk_1F67920[3 * v21 + 1 + 3 * v24]
      + v19 * unk_1F67920[3 * v21 + 2 + 3 * v24];
  v22 = (v38 - v27) * v10 + v27;
  v15 = (v22 - v33) * v42 + v33;
  v28 = v14 * unk_1F67920[3 * v36 + 3 * v18]
      + v41 * unk_1F67920[3 * v36 + 1 + 3 * v18]
      + v20 * unk_1F67920[3 * v36 + 2 + 3 * v18];
  v39 = v25 * unk_1F67920[3 * v36 + 3 * v12]
      + v41 * unk_1F67920[3 * v36 + 1 + 3 * v12]
      + v20 * unk_1F67920[3 * v36 + 2 + 3 * v12];
  v34 = (v39 - v28) * v10 + v28;
  v29 = v14 * unk_1F67920[3 * v36 + 3 * v13]
      + v32 * unk_1F67920[3 * v36 + 1 + 3 * v13]
      + v20 * unk_1F67920[3 * v36 + 2 + 3 * v13];
  v40 = v25 * unk_1F67920[3 * v36 + 3 * v24]
      + v32 * unk_1F67920[3 * v36 + 1 + 3 * v24]
      + v20 * unk_1F67920[3 * v36 + 2 + 3 * v24];
  v23 = (v40 - v29) * v10 + v29;
  v16 = (v23 - v34) * v42 + v34;
  return (float)((v16 - v15) * v6 + v15);
}

