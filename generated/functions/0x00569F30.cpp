// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569F30 rf_polygon_point_inside_projected_triangle_fan
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Projects onto two axes by dominant absolute normal component (ties favor later tested axis),uses normal sign to select axis order from tables663EAC/663EB0. Tests fan triangles(vertex0,vertex[i-1],vertex[i]),starting i2,using projected barycentric ratios inclusive0..1 and sum<=1. Special branch when first edge projected component lies strictly between +/-1e-4. Returns true on first containing fan triangle. Do-while accesses vertex2 even count<3;no plane-distance,degenerate denominator,concavity/triangulation,finite or pointer checks. Read-only inputs;not a winding-count test for arbitrary polygons.
bool __cdecl rf_polygon_point_inside_projected_triangle_fan(int a1, int a2, int *a3, float *a4)
{
  bool v5; // [esp+0h] [ebp-68h]
  bool v6; // [esp+4h] [ebp-64h]
  float v7; // [esp+8h] [ebp-60h]
  float v8; // [esp+Ch] [ebp-5Ch]
  float v9; // [esp+10h] [ebp-58h]
  int v10; // [esp+14h] [ebp-54h]
  int v11; // [esp+18h] [ebp-50h]
  int v12; // [esp+1Ch] [ebp-4Ch]
  float v13; // [esp+20h] [ebp-48h]
  float v14; // [esp+24h] [ebp-44h]
  float v15; // [esp+24h] [ebp-44h]
  float v16; // [esp+28h] [ebp-40h] BYREF
  float v17; // [esp+2Ch] [ebp-3Ch]
  float v18; // [esp+30h] [ebp-38h]
  float v19; // [esp+34h] [ebp-34h]
  float v20; // [esp+38h] [ebp-30h]
  float *v21; // [esp+3Ch] [ebp-2Ch]
  float v22; // [esp+40h] [ebp-28h]
  int v23; // [esp+44h] [ebp-24h]
  bool v24; // [esp+4Bh] [ebp-1Dh]
  int v25; // [esp+4Ch] [ebp-1Ch]
  float v26; // [esp+50h] [ebp-18h]
  float v27; // [esp+54h] [ebp-14h]
  int v28; // [esp+58h] [ebp-10h]
  int v29; // [esp+5Ch] [ebp-Ch]
  float v30; // [esp+60h] [ebp-8h]
  int v31; // [esp+64h] [ebp-4h]

  rf_vector3_default_construct_noop(&v16);
  v9 = fabs(*a4);
  v16 = v9;
  v8 = fabs(a4[1]);
  v17 = v8;
  v7 = fabs(a4[2]);
  v18 = v7;
  if ( v8 >= (double)v9 )
  {
    if ( v18 >= (double)v17 )
      v23 = 2;
    else
      v23 = 1;
  }
  else if ( v18 >= (double)v16 )
  {
    v23 = 2;
  }
  else
  {
    v23 = 0;
  }
  v21 = a4;
  if ( a4[v23] <= 0.0 )
  {
    v25 = dword_663EB0[2 * v23];
    v12 = dword_663EAC[2 * v23];
  }
  else
  {
    v25 = dword_663EAC[2 * v23];
    v12 = dword_663EB0[2 * v23];
  }
  v30 = -1234567.8;
  v24 = 0;
  v29 = 2;
  v31 = a1;
  v28 = *a3;
  v26 = *(float *)(a1 + 4 * v25) - *(float *)(v28 + 4 * v25);
  v19 = *(float *)(a1 + 4 * v12) - *(float *)(v28 + 4 * v12);
  do
  {
    v11 = a3[v29 - 1];
    v13 = *(float *)(v11 + 4 * v25) - *(float *)(v28 + 4 * v25);
    v27 = *(float *)(v11 + 4 * v12) - *(float *)(v28 + 4 * v12);
    v10 = a3[v29];
    v20 = *(float *)(v10 + 4 * v25) - *(float *)(v28 + 4 * v25);
    v22 = *(float *)(v10 + 4 * v12) - *(float *)(v28 + 4 * v12);
    if ( v13 <= -0.00009999999747378752 || v13 >= 0.00009999999747378752 )
    {
      v15 = (v19 * v13 - v26 * v27) / (v22 * v13 - v20 * v27);
      if ( v15 >= 0.0 && v15 <= 1.0 )
      {
        v30 = (v26 - v15 * v20) / v13;
        v5 = v30 >= 0.0 && v30 + v15 <= 1.0;
        v24 = v5;
      }
    }
    else
    {
      v14 = v26 / v20;
      if ( v14 >= 0.0 && v14 <= 1.0 )
      {
        v30 = (v19 - v14 * v22) / v27;
        v6 = v30 >= 0.0 && v30 + v14 <= 1.0;
        v24 = v6;
      }
    }
    if ( v24 )
      break;
    ++v29;
  }
  while ( v29 < a2 );
  return v24;
}

