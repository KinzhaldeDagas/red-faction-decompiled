// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C87D0 rf_clip_polygon2_against_convex_edges
// UNREALRED VERIFIED [renderer-helpers-20261028]: Arguments clipcount,clip8-byteXYarray,subjectcount,subject8-byteXYarray,outputarray,resultpointer-out. Initializes result pointer to subject,builds global subject-pointer list0x1DB4910; generated XY records begin0x1DB4990. Walks closed clip edges,normal=(dy,-dx) normalized by abs(dx)+abs(dy); skips length<0.0001. On first edge uses next clip vertex to choose winding sign. Computes signed distances with0x5C90A0 into global0x1DB4890. If all subject vertices distance>0.0001,returns0. If any outside,clips with epsilon +/-0.0001,alternating pointer lists0x1DB4910/0x1DB4810 and interpolating crossings t=d0/(d0-d1); sets resultpointer to output when changed. Final fewerthan3 returns0. If modified,copies resulting XY pairs into calleroutput via0x51E9B0; otherwise resultpointer remains originalsubject. Returns count,not boolean. Uses fixed global
// scratch,no reentrancy or capacity guards; pointer lists/distances require spare wrap entries. Assumes suitable convex clip polygon and at least3 clip vertices for first-edge orientation test; no input validation. Result pointer can have been set to output even on rejected return0,so caller must use count.
int __cdecl rf_clip_polygon2_against_convex_edges(int a1, float *a2, int a3, int a4, int a5, _DWORD *a6)
{
  float **v7; // [esp+0h] [ebp-58h]
  float v8; // [esp+4h] [ebp-54h]
  float v9; // [esp+8h] [ebp-50h]
  float *v10; // [esp+Ch] [ebp-4Ch]
  int i; // [esp+10h] [ebp-48h]
  int k; // [esp+10h] [ebp-48h]
  int m; // [esp+10h] [ebp-48h]
  int v14; // [esp+14h] [ebp-44h]
  float v15; // [esp+18h] [ebp-40h]
  float v16; // [esp+18h] [ebp-40h]
  float **v17; // [esp+1Ch] [ebp-3Ch]
  char v18; // [esp+23h] [ebp-35h]
  int *v19; // [esp+24h] [ebp-34h]
  float **v20; // [esp+24h] [ebp-34h]
  float **v21; // [esp+24h] [ebp-34h]
  bool v22; // [esp+33h] [ebp-25h]
  float v23; // [esp+34h] [ebp-24h]
  int v24; // [esp+38h] [ebp-20h]
  float *v25; // [esp+38h] [ebp-20h]
  int v26; // [esp+3Ch] [ebp-1Ch]
  float *v27; // [esp+44h] [ebp-14h]
  int j; // [esp+48h] [ebp-10h]
  int n; // [esp+48h] [ebp-10h]
  float v30; // [esp+4Ch] [ebp-Ch] BYREF
  float v31; // [esp+50h] [ebp-8h]
  float *v32; // [esp+54h] [ebp-4h]

  v27 = (float *)&unk_1DB4990;
  v26 = a3;
  v17 = (float **)&unk_1DB4910;
  rf_vector3_default_construct_noop(&v30);
  v18 = 0;
  *a6 = a4;
  v19 = (int *)&unk_1DB4910;
  v24 = a4;
  for ( i = 0; i < a3; ++i )
  {
    *v19++ = v24;
    v24 += 8;
  }
  for ( j = 0; j < a1; ++j )
  {
    v32 = &a2[2 * j];
    if ( j + 1 >= a1 )
      v10 = a2;
    else
      v10 = v32 + 2;
    v30 = v10[1] - v32[1];
    v31 = *v32 - *v10;
    v9 = fabs(v30);
    v8 = fabs(v31);
    v15 = v9 + v8;
    if ( v15 >= 0.00009999999747378752 )
    {
      v30 = v30 / v15;
      v31 = v31 / v15;
      v23 = rf_vector2_dot(v32, &v30);
      if ( !j && rf_vector2_dot(v10 + 2, &v30) - v23 > 0.00009999999747378752 )
        v18 = 1;
      if ( v18 )
      {
        v23 = -v23;
        v30 = -v30;
        v31 = -v31;
      }
      v20 = v17;
      v14 = 0;
      for ( k = 0; k < v26; ++k )
      {
        flt_1DB4890[k] = rf_vector2_dot(*v20, &v30) - v23;
        if ( flt_1DB4890[k] > 0.00009999999747378752 )
          ++v14;
        ++v20;
      }
      if ( v14 == v26 )
        return 0;
      if ( v14 )
      {
        flt_1DB4890[v26] = flt_1DB4890[0];
        v17[v26] = *v17;
        if ( v17 == (float **)&unk_1DB4910 )
          v7 = (float **)&unk_1DB4810;
        else
          v7 = (float **)&unk_1DB4910;
        v21 = v7;
        for ( m = 0; m < v26; ++m )
        {
          v22 = 0;
          if ( flt_1DB4890[m] >= 0.00009999999747378752 )
          {
            if ( unk_1DB4894[m] >= -0.00009999999747378752 )
              *a6 = a5;
            else
              v22 = 1;
          }
          else
          {
            *v21++ = v17[m];
            if ( flt_1DB4890[m] < -0.00009999999747378752 )
              v22 = unk_1DB4894[m] > 0.00009999999747378752;
          }
          if ( v22 )
          {
            v32 = v17[m];
            v25 = v17[m + 1];
            v16 = flt_1DB4890[m] / (flt_1DB4890[m] - unk_1DB4894[m]);
            *v27 = (*v25 - *v32) * v16 + *v32;
            v27[1] = (v25[1] - v32[1]) * v16 + v32[1];
            *v21++ = v27;
            v27 += 2;
            *a6 = a5;
          }
        }
        v17 = v7;
        v26 = v21 - v7;
      }
    }
  }
  if ( v26 < 3 )
    return 0;
  if ( *a6 != a4 )
  {
    for ( n = 0; n < v26; ++n )
      rf_vector2_copy_return_source((float *)(a5 + 8 * n), v17[n]);
  }
  return v26;
}

