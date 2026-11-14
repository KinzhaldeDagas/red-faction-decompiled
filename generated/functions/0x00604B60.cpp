// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00604B60 rf_jpeg_master_initial_setup
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmaster.c:initial_setup matched): Validates nonzero dimensions and positive input/output component counts (error 32), signed dimensions <=65500 (error 41), 8-bit precision (error 15), <=10 components (error 26), and sampling factors 1..4 (error 18). Computes max_h/max_v. Per component: index, DCT size 8, block dimensions ceil(width*h/(8*max_h)) and ceil(height*v/(8*max_v)), downsampled dimensions ceil(width*h/max_h) and ceil(height*v/max_v), needed=TRUE. total_iMCU_rows=ceil(height/(8*max_v)). Uses native 32-bit arithmetic.
int __cdecl rf_jpeg_master_initial_setup(_DWORD *a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-18h]
  int v3; // [esp+4h] [ebp-14h]
  int v4; // [esp+Ch] [ebp-Ch]
  int v5; // [esp+Ch] [ebp-Ch]
  int v6; // [esp+10h] [ebp-8h]
  _DWORD *v7; // [esp+10h] [ebp-8h]

  if ( !a1[8] || !a1[7] || (int)a1[14] <= 0 || (int)a1[9] <= 0 )
  {
    *(_DWORD *)(*a1 + 20) = 32;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  if ( (int)a1[8] > 65500 || (int)a1[7] > 65500 )
  {
    *(_DWORD *)(*a1 + 20) = 41;
    *(_DWORD *)(*a1 + 24) = 65500;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  if ( a1[13] != 8 )
  {
    *(_DWORD *)(*a1 + 20) = 15;
    *(_DWORD *)(*a1 + 24) = a1[13];
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  if ( (int)a1[14] > 10 )
  {
    *(_DWORD *)(*a1 + 20) = 26;
    *(_DWORD *)(*a1 + 24) = a1[14];
    *(_DWORD *)(*a1 + 28) = 10;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  a1[57] = 1;
  a1[58] = 1;
  v4 = 0;
  v6 = a1[16];
  while ( v4 < a1[14] )
  {
    if ( *(int *)(v6 + 8) <= 0 || *(int *)(v6 + 8) > 4 || *(int *)(v6 + 12) <= 0 || *(int *)(v6 + 12) > 4 )
    {
      *(_DWORD *)(*a1 + 20) = 18;
      (*(void (__cdecl **)(_DWORD *))*a1)(a1);
    }
    if ( a1[57] <= *(_DWORD *)(v6 + 8) )
      v3 = *(_DWORD *)(v6 + 8);
    else
      v3 = a1[57];
    a1[57] = v3;
    if ( a1[58] <= *(_DWORD *)(v6 + 12) )
      v2 = *(_DWORD *)(v6 + 12);
    else
      v2 = a1[58];
    a1[58] = v2;
    ++v4;
    v6 += 84;
  }
  v5 = 0;
  v7 = (_DWORD *)a1[16];
  while ( v5 < a1[14] )
  {
    v7[1] = v5;
    v7[9] = 8;
    v7[7] = rf_jpeg_jdiv_round_up(v7[2] * a1[7], 8 * a1[57]);
    v7[8] = rf_jpeg_jdiv_round_up(v7[3] * a1[8], 8 * a1[58]);
    v7[10] = rf_jpeg_jdiv_round_up(v7[2] * a1[7], a1[57]);
    v7[11] = rf_jpeg_jdiv_round_up(v7[3] * a1[8], a1[58]);
    v7[12] = 1;
    ++v5;
    v7 += 21;
  }
  result = rf_jpeg_jdiv_round_up(a1[8], 8 * a1[58]);
  a1[59] = result;
  return result;
}

