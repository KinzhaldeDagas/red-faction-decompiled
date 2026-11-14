// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605240 rf_jpeg_master_per_scan_setup
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmaster.c:per_scan_setup matched): Computes per-scan MCU geometry. Single component: MCU grid equals its block dimensions, MCU width/height/block count are one, sample width is eight, membership[0]=0, and last row height is blockHeight%v_samp or v_samp. Interleaved scans require 2..4 components; grid is ceil(width/(8*max_h)) by ceil(height/(8*max_v)). Each component contributes h_samp*v_samp blocks, sample width 8*h_samp, and last-column/row remainders (or full factors). Total blocks >10 raises error 13. Fills block membership indices. restart_in_rows >0 sets restart_interval=min(MCUs_per_row*restart_in_rows,65535).
_DWORD *__cdecl rf_jpeg_master_per_scan_setup(_DWORD *a1)
{
  _DWORD *result; // eax
  int v2; // ecx
  int v3; // [esp+4h] [ebp-18h]
  int v4; // [esp+Ch] [ebp-10h]
  int v5; // [esp+10h] [ebp-Ch]
  int v6; // [esp+10h] [ebp-Ch]
  int v7; // [esp+10h] [ebp-Ch]
  int i; // [esp+14h] [ebp-8h]
  _DWORD *v9; // [esp+18h] [ebp-4h]
  _DWORD *v10; // [esp+18h] [ebp-4h]

  if ( a1[60] == 1 )
  {
    v9 = (_DWORD *)a1[61];
    a1[65] = v9[7];
    a1[66] = v9[8];
    v9[13] = 1;
    v9[14] = 1;
    v9[15] = 1;
    v9[16] = 8;
    v9[17] = 1;
    v5 = v9[8] % v9[3];
    if ( !v5 )
      v5 = v9[3];
    v9[18] = v5;
    result = a1;
    a1[67] = 1;
    a1[68] = 0;
  }
  else
  {
    if ( (int)a1[60] <= 0 || (int)a1[60] > 4 )
    {
      *(_DWORD *)(*a1 + 20) = 26;
      *(_DWORD *)(*a1 + 24) = a1[60];
      *(_DWORD *)(*a1 + 28) = 4;
      (*(void (__cdecl **)(_DWORD *))*a1)(a1);
    }
    a1[65] = rf_jpeg_jdiv_round_up(a1[7], 8 * a1[57]);
    result = (_DWORD *)rf_jpeg_jdiv_round_up(a1[8], 8 * a1[58]);
    a1[66] = result;
    a1[67] = 0;
    for ( i = 0; i < a1[60]; ++i )
    {
      v10 = (_DWORD *)a1[i + 61];
      v10[13] = v10[2];
      v10[14] = v10[3];
      v10[15] = v10[14] * v10[13];
      v10[16] = 8 * v10[13];
      v6 = v10[7] % v10[13];
      if ( !v6 )
        v6 = v10[13];
      v10[17] = v6;
      v7 = v10[8] % v10[14];
      if ( !v7 )
        v7 = v10[14];
      v10[18] = v7;
      v4 = v10[15];
      if ( v4 + a1[67] > 10 )
      {
        *(_DWORD *)(*a1 + 20) = 13;
        (*(void (__cdecl **)(_DWORD *))*a1)(a1);
      }
      while ( 1 )
      {
        v2 = v4--;
        if ( v2 <= 0 )
          break;
        a1[a1[67]++ + 68] = i;
      }
      result = (_DWORD *)(i + 1);
    }
  }
  if ( (int)a1[50] > 0 )
  {
    if ( a1[65] * a1[50] >= 0xFFFF )
      v3 = 0xFFFF;
    else
      v3 = a1[65] * a1[50];
    a1[49] = v3;
    return a1;
  }
  return result;
}

