// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0053A440 rf_procedural_bitmap_update_sine_warp
// UNREALRED VERIFIED [decal-updates-20261028]: Reads width+16,height+20 and three phase floats+44/+48/+52. Builds global per-column/per-row integer sine-offset tables using256-entry sine table0x1425ED8 and tuning globals0x663D18..38, indexing sine by low8 of truncated coordinate. Advances phases by three fixed global increments ONCE PER CALLBACK, without frame delta or phase wrapping. Locks source bitmap+36 read mode0 and generated bitmap+24 write mode2 via0x573640; does not check lock results. Computes log2-like shift by counting trailing zero bits of positive width, so source-row addressing assumes power-of-two width. Uses (width-1)/(height-1) bitmasks for sample wrap; no power-of-two/dimension<=256 guard here. Source format7 reads32-bit pixels and combines global masks shifted4/8/12/16 into16-bit output; format6 reads24-bit triplets, packs upper nibbles plus0x8000; format4 copies16-bit
// samples. Other source formats perform no pixel writes. Iterates locked destination dimensions and writes contiguous16-bit pixels without explicit row-pitch use. Unlocks both surfaces; returns destination unlock result.
int __cdecl rf_procedural_bitmap_update_sine_warp(int a1)
{
  _BYTE *v2; // [esp+28h] [ebp-88h]
  int k; // [esp+30h] [ebp-80h]
  float v4; // [esp+38h] [ebp-78h]
  float v5; // [esp+38h] [ebp-78h]
  float v6; // [esp+38h] [ebp-78h]
  float v7; // [esp+3Ch] [ebp-74h]
  float v8; // [esp+3Ch] [ebp-74h]
  float v9; // [esp+40h] [ebp-70h]
  unsigned int v10[4]; // [esp+44h] [ebp-6Ch] BYREF
  int v11; // [esp+54h] [ebp-5Ch]
  int v12; // [esp+58h] [ebp-58h]
  int v13; // [esp+64h] [ebp-4Ch]
  int v14; // [esp+68h] [ebp-48h]
  int v15; // [esp+6Ch] [ebp-44h]
  unsigned int v16[2]; // [esp+70h] [ebp-40h] BYREF
  int v17; // [esp+78h] [ebp-38h]
  int v18; // [esp+7Ch] [ebp-34h]
  float v19; // [esp+90h] [ebp-20h]
  int v20; // [esp+94h] [ebp-1Ch]
  int v21; // [esp+98h] [ebp-18h]
  float v22; // [esp+9Ch] [ebp-14h]
  _WORD *v23; // [esp+A0h] [ebp-10h]
  int i; // [esp+A4h] [ebp-Ch]
  int j; // [esp+A8h] [ebp-8h]
  float v26; // [esp+ACh] [ebp-4h]

  v19 = *(float *)(a1 + 44);
  v9 = *(float *)(a1 + 52);
  v26 = *(float *)(a1 + 48);
  v7 = flt_663D38 * 256.0 / (double)*(int *)(a1 + 16);
  for ( i = 0; i < *(_DWORD *)(a1 + 16); ++i )
  {
    v4 = flt_663D34 * unk_1425ED8[(unsigned __int8)(int)((double)i * v7 + v9)];
    unk_1426868[i] = (int)v4;
  }
  v22 = flt_663D30 * 256.0 / (double)*(int *)(a1 + 20);
  v8 = flt_663D2C * 256.0 / (double)*(int *)(a1 + 20);
  for ( j = 0; j < *(_DWORD *)(a1 + 20); ++j )
  {
    v5 = flt_663D28 * unk_1425ED8[(unsigned __int8)(int)((double)j * v22 + v19)];
    unk_1426768[j] = (int)v5;
    v6 = flt_663D24 * unk_1425ED8[(unsigned __int8)(int)((double)j * v8 + v26)];
    unk_1426668[j] = (int)((double)j + v6);
  }
  *(float *)(a1 + 44) = *(float *)(a1 + 44) + flt_663D20;
  *(float *)(a1 + 52) = *(float *)(a1 + 52) + flt_663D1C;
  *(float *)(a1 + 48) = *(float *)(a1 + 48) + flt_663D18;
  rf_bitmap_lock_pixels_backend_dispatch(*(_DWORD *)(a1 + 36), 0, (int)v16, 0);
  rf_bitmap_lock_pixels_backend_dispatch(*(_DWORD *)(a1 + 24), 0, (int)v10, 2);
  v20 = 0;
  if ( *(int *)(a1 + 16) > 0 )
  {
    for ( k = 1; (k & *(_DWORD *)(a1 + 16)) == 0; k *= 2 )
      ++v20;
  }
  v23 = (_WORD *)v10[3];
  switch ( v17 )
  {
    case 7:
      for ( j = 0; j < v12; ++j )
      {
        v14 = (unsigned __int8)unk_1426768[j];
        v15 = (unsigned __int8)unk_1426668[j];
        for ( i = 0; i < v11; ++i )
        {
          v21 = (i + v14) & (v11 - 1);
          v13 = v15 + (unsigned __int8)unk_1426868[i];
          v13 &= v12 - 1;
          *v23++ = (((unsigned int)dword_663D08 & *(_DWORD *)(v18 + 4 * (v13 << v20) + 4 * v21)) >> 4)
                 | (((unsigned int)dword_663D0C & *(_DWORD *)(v18 + 4 * (v13 << v20) + 4 * v21)) >> 8)
                 | (((unsigned int)off_663D10 & *(_DWORD *)(v18 + 4 * (v13 << v20) + 4 * v21)) >> 12)
                 | (((unsigned int)dword_663D14 & *(_DWORD *)(v18 + 4 * (v13 << v20) + 4 * v21)) >> 16);
        }
      }
      break;
    case 6:
      for ( j = 0; j < v12; ++j )
      {
        v14 = (unsigned __int8)unk_1426768[j];
        v15 = (unsigned __int8)unk_1426668[j];
        for ( i = 0; i < v11; ++i )
        {
          v21 = (i + v14) & (v11 - 1);
          v13 = v15 + (unsigned __int8)unk_1426868[i];
          v13 &= v12 - 1;
          v2 = (_BYTE *)(v18 + 3 * (v13 << v20) + 3 * v21);
          *v23++ = ((*v2 & 0xF0) >> 4) | v2[1] & 0xF0 | (16 * (v2[2] & 0xF0)) | 0x8000;
        }
      }
      break;
    case 4:
      for ( j = 0; j < v12; ++j )
      {
        v14 = (unsigned __int8)unk_1426768[j];
        v15 = (unsigned __int8)unk_1426668[j];
        for ( i = 0; i < v11; ++i )
        {
          v21 = (i + v14) & (v11 - 1);
          v13 = v15 + (unsigned __int8)unk_1426868[i];
          v13 &= v12 - 1;
          *v23++ = *(_WORD *)(v18 + 2 * (v13 << v20) + 2 * v21);
        }
      }
      break;
  }
  rf_bitmap_unlock_pixels_backend_dispatch(v16);
  return rf_bitmap_unlock_pixels_backend_dispatch(v10);
}

