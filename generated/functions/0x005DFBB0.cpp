// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DFBB0 rf_tga_encode_rle_packets
// UNREALRED VERIFIED [image-headers-20261028]: Arguments output,input,pixel comparison/output byte size,source stride,input byte length. Groups literal/repeated pixel packets, max128 pixels, high bit marks repeated payload. Repetition threshold is3 equal pixels for byte size1,2 for other sizes. Compares through0x5DFF40 and copies payload through0x5DFE10, inheriting its16-bit-to16-bit no-output bug and size mismatch behavior. Returns encoded byte count in EAX despite pointer prototype. do/while plus final flush encodes at least one source pixel even for zero/negative input byte length. No source/output capacity, stride/size validity, scanline boundary or final pixel completeness checks. Runs may cross rows.
_BYTE *__cdecl rf_tga_encode_rle_packets(_BYTE *a1, char *a2, int a3, int a4, int a5)
{
  int v6; // [esp+0h] [ebp-1Ch]
  _BYTE *v7; // [esp+4h] [ebp-18h]
  char *v8; // [esp+8h] [ebp-14h]
  char *Src; // [esp+Ch] [ebp-10h]
  int v10; // [esp+10h] [ebp-Ch]
  int v11; // [esp+10h] [ebp-Ch]
  char *v12; // [esp+14h] [ebp-8h]
  int v13; // [esp+18h] [ebp-4h]

  v12 = nullptr;
  if ( a3 == 1 )
    v13 = 2;
  else
    v13 = 1;
  v7 = a1;
  v8 = a2;
  v10 = 1;
  v6 = 0;
  Src = nullptr;
  do
  {
    if ( v10 == 129 )
    {
      *v7 = 127;
      if ( v6 >= v13 )
      {
        *v7 |= 0x80u;
        v10 = 2;
      }
      v7 += rf_tga_rle_copy_convert_payload_run(v7 + 1, Src, v10 - 1, a4, a3) + 1;
      v10 = 1;
    }
    else
    {
      if ( v10 == 1 )
      {
        v6 = 0;
        Src = v8;
        v12 = v8;
        v10 = 2;
        v8 += a4;
        continue;
      }
      if ( rf_pixel_bytes_equal_do_while(v8, v12, a3) )
      {
        if ( ++v6 == v13 && v10 > v6 + 1 )
        {
          *v7 = v10 - 2 - v13;
          v7 += rf_tga_rle_copy_convert_payload_run(v7 + 1, Src, v10 - 1 - v6, a4, a3) + 1;
          Src = v8;
          v10 = v6 + 1;
        }
      }
      else
      {
        if ( v6 >= v13 )
        {
          *v7 = v6 | 0x80;
          v7 += rf_tga_rle_copy_convert_payload_run(v7 + 1, Src, 1, a4, a3) + 1;
          v10 = 1;
          continue;
        }
        v6 = 0;
        v12 = v8;
      }
      ++v10;
      v8 += a4;
    }
  }
  while ( v8 < &a2[a5] );
  v11 = v10 - 1;
  if ( v11 >= 1 )
  {
    *v7 = v11 - 1;
    if ( v6 >= v13 )
    {
      *v7 |= 0x80u;
      v11 = 1;
    }
    v7 += rf_tga_rle_copy_convert_payload_run(v7 + 1, Src, v11, a4, a3) + 1;
  }
  return (_BYTE *)(v7 - a1);
}

