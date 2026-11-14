// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573A80 rf_bitmap_copy_subrectangle_to_horizontal_tiles
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Copies source bitmap tile0 into destination bitmap horizontal tiles. Iterates tile indices floor(dstX/tileSpan187CCCC) through floor((dstX+width)/tileSpan) INCLUSIVE, locks destination mode1 and source mode0, and copies only when formats match. Clips destination-local X/Y by shifting source origin and shrinking width/height; source coordinates are not independently bounds checked. Uses format bytes-per-pixel and each lock pitch; memcpy rows, then unlocks source/destination. Negative clipped size exits the whole routine; zero size is allowed. Exact tile-boundary end can visit one extra tile. No pixel conversion, NULL/overflow/tileSpan-zero validation; EAX incidental.
int __cdecl rf_bitmap_copy_subrectangle_to_horizontal_tiles(
        int a1,
        int a2,
        unsigned int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        unsigned int a8)
{
  int result; // eax
  int j; // [esp+0h] [ebp-7Ch]
  int v10; // [esp+4h] [ebp-78h]
  int v11; // [esp+8h] [ebp-74h]
  int v12; // [esp+Ch] [ebp-70h]
  int v13; // [esp+10h] [ebp-6Ch]
  int v14; // [esp+14h] [ebp-68h]
  int v15; // [esp+1Ch] [ebp-60h]
  int v16; // [esp+20h] [ebp-5Ch]
  int v17; // [esp+2Ch] [ebp-50h]
  signed int i; // [esp+30h] [ebp-4Ch]
  unsigned int v19[6]; // [esp+38h] [ebp-44h] BYREF
  int v20; // [esp+50h] [ebp-2Ch]
  int v21; // [esp+58h] [ebp-24h]
  unsigned int v22[2]; // [esp+5Ch] [ebp-20h] BYREF
  int v23; // [esp+64h] [ebp-18h]
  int v24; // [esp+68h] [ebp-14h]
  int v25; // [esp+6Ch] [ebp-10h]
  int v26; // [esp+70h] [ebp-Ch]
  int v27; // [esp+74h] [ebp-8h]

  v21 = (a6 + a1) / unk_187CCCC;
  result = a1 / unk_187CCCC;
  for ( i = a1 / unk_187CCCC; i <= v21; ++i )
  {
    v17 = a1 - unk_187CCCC * i;
    result = (unsigned __int8)rf_bitmap_lock_pixels_backend_dispatch(a3, i, v22, 1u);
    if ( (_BYTE)result )
    {
      if ( rf_bitmap_lock_pixels_backend_dispatch(a8, 0, v19, 0) )
      {
        if ( v23 == v19[2] )
        {
          v13 = 0;
          v11 = 0;
          if ( v17 < 0 )
          {
            v13 = -v17;
            v11 = v17;
          }
          if ( a6 + v17 > v25 )
            v11 -= a6 + v17 - v25;
          if ( v11 + a6 < 0 )
            goto LABEL_11;
          v16 = 0;
          v14 = 0;
          if ( a2 < 0 )
          {
            v16 = -a2;
            v14 = a2;
          }
          if ( a7 + a2 > v26 )
            v14 -= a7 + a2 - v26;
          if ( v14 + a7 < 0 )
          {
LABEL_11:
            rf_bitmap_unlock_pixels_backend_dispatch(v19);
            return rf_bitmap_unlock_pixels_backend_dispatch(v22);
          }
          v15 = rf_bitmap_format_bytes_per_pixel(v23);
          v12 = v15 * (v13 + v17) + v27 * (v16 + a2);
          v10 = v15 * (v13 + a4) + v20 * (v16 + a5);
          for ( j = 0; j < v14 + a7; ++j )
          {
            memcpy((void *)(v12 + v24), (const void *)(v10 + v19[3]), v15 * (v11 + a6));
            v12 += v27;
            v10 += v20;
          }
        }
        rf_bitmap_unlock_pixels_backend_dispatch(v19);
      }
      result = rf_bitmap_unlock_pixels_backend_dispatch(v22);
    }
  }
  return result;
}

