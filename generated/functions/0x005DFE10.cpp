// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DFE10 rf_tga_rle_copy_convert_payload_run
// UNREALRED VERIFIED [image-headers-20261028]: Five arguments output,input,pixel count,source stride,output pixel bytes. Source stride2/output bytes2 branch sets BOTH local read/write pointers to INPUT and copies each word back to itself; OUTPUT UNTOUCHED, returns2*count. Source stride2/output bytes3 expands RGB565 into BGR bytes using B5*8,G6*4,R5*8, returns3*count. All other pairs memcpy sourceStride*count bytes but return outputBytes*count, which can disagree if sizes differ. No capacity/overlap/count validation. Do not infer correct16-bit encoder output from reported byte count.
int __cdecl rf_tga_rle_copy_convert_payload_run(char *a1, _WORD *Src, int a3, int a4, int a5)
{
  unsigned __int16 v6; // [esp+0h] [ebp-18h]
  int j; // [esp+4h] [ebp-14h]
  unsigned __int16 *v8; // [esp+8h] [ebp-10h]
  int i; // [esp+Ch] [ebp-Ch]
  _WORD *v10; // [esp+10h] [ebp-8h]
  _WORD *v11; // [esp+14h] [ebp-4h]
  char *v12; // [esp+20h] [ebp+8h]

  if ( a4 == 2 && a5 == 2 )
  {
    v10 = Src;
    v11 = Src;
    for ( i = 0; i < a3; ++i )
      *v11++ = *v10++;
    return 2 * a3;
  }
  else if ( a4 == 2 && a5 == 3 )
  {
    v8 = Src;
    for ( j = 0; j < a3; ++j )
    {
      v6 = *v8++;
      *a1 = 8 * (v6 & 0x1F);
      v12 = a1 + 1;
      *v12 = 4 * (((int)v6 >> 5) & 0x3F);
      v12[1] = 8 * (((int)v6 >> 11) & 0x1F);
      a1 = v12 + 2;
    }
    return 3 * a3;
  }
  else
  {
    memcpy(a1, Src, a4 * a3);
    return a3 * a5;
  }
}

