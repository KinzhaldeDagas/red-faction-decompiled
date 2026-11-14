// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005331C0 rf_face_interpolate_primary_uv_projected_fan
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Chooses two projected axes from plane normal; tests triangles anchored to first corner and each successive edge using inclusive barycentric checks. On first hit returns byte1; on exhausted fan0. No plane-distance, convexity, empty-ring, or count>=3 validation; do-loop dereferences next corner even for short rings and final iteration includes degenerate closing triangle. Optional outputs use if(outU OR outV) then writes BOTH pointers, so either both valid or bothnull is required. Miss leaves outputs unchanged. Uses primary corner U4/V8 only.
char __thiscall rf_face_interpolate_primary_uv_projected_fan(float **this, int a2, float *a3, float *a4)
{
  float *v5; // [esp+0h] [ebp-64h]
  bool v6; // [esp+4h] [ebp-60h]
  bool v7; // [esp+8h] [ebp-5Ch]
  float *v8; // [esp+Ch] [ebp-58h]
  float v10; // [esp+14h] [ebp-50h]
  int v11; // [esp+18h] [ebp-4Ch]
  float v12; // [esp+1Ch] [ebp-48h]
  float v13; // [esp+20h] [ebp-44h]
  int v14; // [esp+24h] [ebp-40h]
  bool v15; // [esp+2Bh] [ebp-39h]
  float v16; // [esp+2Ch] [ebp-38h]
  float v17; // [esp+30h] [ebp-34h]
  float v18; // [esp+34h] [ebp-30h]
  float v19; // [esp+38h] [ebp-2Ch]
  int v20; // [esp+3Ch] [ebp-28h] BYREF
  float v21; // [esp+40h] [ebp-24h]
  float *v22; // [esp+44h] [ebp-20h]
  int v23; // [esp+48h] [ebp-1Ch] BYREF
  int v24; // [esp+4Ch] [ebp-18h] BYREF
  float v25; // [esp+50h] [ebp-14h]
  float v26; // [esp+54h] [ebp-10h]
  float v27; // [esp+58h] [ebp-Ch]
  float v28; // [esp+5Ch] [ebp-8h]
  float v29; // [esp+60h] [ebp-4h]

  rf_face_projection_axes_select((float *)this, &v24, &v20, &v23);
  v28 = 0.0;
  v18 = 0.0;
  v22 = *(this + 16);
  v29 = *v22;
  v26 = *(float *)(a2 + 4 * v20) - *(float *)(LODWORD(v29) + 4 * v20);
  v19 = *(float *)(a2 + 4 * v23) - *(float *)(LODWORD(v29) + 4 * v23);
  if ( *((float **)v22 + 5) == *(this + 16) )
    v8 = nullptr;
  else
    v8 = *((float **)v22 + 5);
  v22 = v8;
  while ( 1 )
  {
    v15 = 0;
    v16 = *v22;
    v14 = **((_DWORD **)v22 + 5);
    v17 = *(float *)(*(_DWORD *)v22 + 4 * v20) - *(float *)(LODWORD(v29) + 4 * v20);
    v21 = *(float *)(v14 + 4 * v20) - *(float *)(LODWORD(v29) + 4 * v20);
    v27 = *(float *)(LODWORD(v16) + 4 * v23) - *(float *)(LODWORD(v29) + 4 * v23);
    v25 = *(float *)(v14 + 4 * v23) - *(float *)(LODWORD(v29) + 4 * v23);
    if ( v17 <= -0.00009999999747378752 || v17 >= 0.00009999999747378752 )
    {
      v12 = v25 * v17 - v21 * v27;
      if ( v12 != 0.0 )
      {
        v13 = v19 * v17 - v26 * v27;
        v18 = v13 / v12;
        if ( v18 >= 0.0 && v18 <= 1.0 )
        {
          v28 = (v26 - v18 * v21) / v17;
          v6 = v28 >= 0.0 && v28 + v18 <= 1.0;
          v15 = v6;
        }
      }
    }
    else if ( v21 != 0.0 )
    {
      v18 = v26 / v21;
      if ( v27 != 0.0 && v18 >= 0.0 && v18 <= 1.0 )
      {
        v28 = (v19 - v18 * v25) / v27;
        v7 = v28 >= 0.0 && v28 + v18 <= 1.0;
        v15 = v7;
      }
    }
    if ( v15 )
      break;
    if ( *((float **)v22 + 5) == *(this + 16) )
      v5 = nullptr;
    else
      v5 = *((float **)v22 + 5);
    v22 = v5;
    if ( !v5 )
      return 0;
  }
  if ( a3 || a4 )
  {
    v11 = (int)*(this + 16);
    v10 = 1.0 - (v28 + v18);
    *a3 = v10 * *(float *)(v11 + 4) + v28 * v22[1] + v18 * *(float *)(*((_DWORD *)v22 + 5) + 4);
    *a4 = v10 * *(float *)(v11 + 8) + v28 * v22[2] + v18 * *(float *)(*((_DWORD *)v22 + 5) + 8);
  }
  return 1;
}

