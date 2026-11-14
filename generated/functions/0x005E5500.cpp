// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E5500 rf_bitmap_convert_pixel_run_selected_formats
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Actual arguments destination pixels,destination format,source pixels,source format,pixel count; current void-pointer format types are misleading. Same format memcpy(count*bytes_per_pixel). Supported source->destination conversions:4->7,6->3,7->3,3->4,6->5,7->4,7->5,7->6. Internal3 RGB565,4 ARGB4444,5 ARGB1555,6 three-byte pixels,7 four-byte pixels. 4->7 expands each nibble by float15.9375 then integer/byte conversion, so maximum channel239, not255. 7->5 alpha threshold is source byte3>127. 6->5 forces alpha1; 3->4 forces alpha nibble15. 7->6 copies source bytes1,2,3, dropping byte0; preserves this observed unusual channel selection. Unsupported pair silently performs no writes. Return varies by branch between destination end, source end, loop count or input format; not a consistent pointer/status contract. No capacity, overlap, count or
// multiplication checks.
void *__cdecl rf_bitmap_convert_pixel_run_selected_formats(void *a1, void *a2, unsigned __int8 *Src, void *a4, int a5)
{
  void *result; // eax
  unsigned __int8 *v6; // [esp+40h] [ebp-C0h]
  int kk; // [esp+44h] [ebp-BCh]
  _BYTE *v8; // [esp+48h] [ebp-B8h]
  unsigned __int8 *v9; // [esp+60h] [ebp-A0h]
  int jj; // [esp+64h] [ebp-9Ch]
  _WORD *v11; // [esp+68h] [ebp-98h]
  unsigned __int8 *v12; // [esp+7Ch] [ebp-84h]
  int ii; // [esp+80h] [ebp-80h]
  _WORD *v14; // [esp+84h] [ebp-7Ch]
  unsigned __int8 *v15; // [esp+94h] [ebp-6Ch]
  int n; // [esp+98h] [ebp-68h]
  _WORD *v17; // [esp+9Ch] [ebp-64h]
  unsigned __int8 *v18; // [esp+B0h] [ebp-50h]
  int m; // [esp+B4h] [ebp-4Ch]
  _WORD *v20; // [esp+B8h] [ebp-48h]
  unsigned __int8 *v21; // [esp+C8h] [ebp-38h]
  int k; // [esp+CCh] [ebp-34h]
  _WORD *v23; // [esp+D0h] [ebp-30h]
  unsigned __int8 *v24; // [esp+E0h] [ebp-20h]
  int j; // [esp+E4h] [ebp-1Ch]
  _WORD *v26; // [esp+E8h] [ebp-18h]
  unsigned __int8 *v27; // [esp+F0h] [ebp-10h]
  int i; // [esp+F4h] [ebp-Ch]
  int *v29; // [esp+F8h] [ebp-8h]
  int v30; // [esp+FCh] [ebp-4h]

  result = a4;
  if ( a4 == a2 )
  {
    v30 = rf_bitmap_format_bytes_per_pixel((int)a4);
    return memcpy(a1, Src, v30 * a5);
  }
  else if ( a4 == (void *)4 && a2 == (void *)7 )
  {
    v27 = Src;
    result = a1;
    v29 = (int *)a1;
    for ( i = 0; i < a5; ++i )
    {
      *v29 = (unsigned __int8)(int)((double)(*(_WORD *)v27 & 0xF) * 15.9375)
           | ((unsigned __int8)(int)((double)(((int)*(unsigned __int16 *)v27 >> 4) & 0xF) * 15.9375) << 8)
           | ((unsigned __int8)(int)((double)(((int)*(unsigned __int16 *)v27 >> 8) & 0xF) * 15.9375) << 16)
           | ((unsigned __int8)(int)((double)(((int)*(unsigned __int16 *)v27 >> 12) & 0xF) * 15.9375) << 24);
      result = ++v29;
      v27 += 2;
    }
  }
  else if ( a4 == (void *)6 && a2 == (void *)3 )
  {
    v24 = Src;
    result = a1;
    v26 = a1;
    for ( j = 0; j < a5; ++j )
    {
      *v26 = ((int)*v24 >> 3) | (32 * ((int)v24[1] >> 2)) | ((int)v24[2] >> 3 << 11);
      result = ++v26;
      v24 += 3;
    }
  }
  else if ( a4 == (void *)7 && a2 == (void *)3 )
  {
    v21 = Src;
    result = a1;
    v23 = a1;
    for ( k = 0; k < a5; ++k )
    {
      *v23 = ((int)*v21 >> 3) | (32 * ((int)v21[1] >> 2)) | ((int)v21[2] >> 3 << 11);
      result = ++v23;
      v21 += 4;
    }
  }
  else if ( a4 == (void *)3 && a2 == (void *)4 )
  {
    v18 = Src;
    result = a1;
    v20 = a1;
    for ( m = 0; m < a5; ++m )
    {
      *v20++ = ((int)*(unsigned __int16 *)v18 >> 1) & 0xF
             | (16 * (((int)*(unsigned __int16 *)v18 >> 7) & 0xF))
             | ((((int)*(unsigned __int16 *)v18 >> 12) & 0xF) << 8)
             | 0xF000;
      result = v18 + 2;
      v18 += 2;
    }
  }
  else if ( a4 == (void *)6 && a2 == (void *)5 )
  {
    v15 = Src;
    v17 = a1;
    for ( n = 0; n < a5; ++n )
    {
      *v17++ = ((int)*v15 >> 3) | (32 * ((int)v15[1] >> 3)) | ((int)v15[2] >> 3 << 10) | 0x8000;
      v15 += 3;
      result = (void *)(n + 1);
    }
  }
  else if ( a4 == (void *)7 && a2 == (void *)4 )
  {
    v12 = Src;
    v14 = a1;
    for ( ii = 0; ii < a5; ++ii )
    {
      *v14++ = ((int)*v12 >> 4) | (16 * ((int)v12[1] >> 4)) | ((int)v12[2] >> 4 << 8) | ((int)v12[3] >> 4 << 12);
      v12 += 4;
      result = (void *)(ii + 1);
    }
  }
  else if ( a4 == (void *)7 && a2 == (void *)5 )
  {
    v9 = Src;
    result = a1;
    v11 = a1;
    for ( jj = 0; jj < a5; ++jj )
    {
      *v11 = ((int)*v9 >> 3) | (32 * ((int)v9[1] >> 3)) | ((int)v9[2] >> 3 << 10) | (v9[3] > 0x7Fu ? 0x8000 : 0);
      result = ++v11;
      v9 += 4;
    }
  }
  else if ( a4 == (void *)7 && a2 == (void *)6 )
  {
    v6 = Src;
    result = a1;
    v8 = a1;
    for ( kk = 0; kk < a5; ++kk )
    {
      *v8 = v6[1];
      v8[1] = v6[2];
      v8[2] = v6[3];
      result = v8 + 3;
      v8 += 3;
      v6 += 4;
    }
  }
  return result;
}

