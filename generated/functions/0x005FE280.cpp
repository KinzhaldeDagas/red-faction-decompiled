// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FE280 rf_jpeg_alloc_large
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemmgr.c:alloc_large matched): Cdecl(cinfo,poolID,unsignedbytes). Rejects initialbytes>999999988(OOMcase3),roundsup8,requirespoolID0/1(error14). Callsplatformget_large forroundedbytes+12;NULLfatalOOMcase4. Header12{next0,used4=roundedsize,left8=0},prependsmanagerlargepoolhead60/64,addsallocationbytecount to76,returnsheader+12. No zeroing or splittinglargechunks;size arithmetic32-bit.
_DWORD *__cdecl rf_jpeg_alloc_large(_DWORD *cinfo, unsigned int a2, unsigned int a3)
{
  int v4; // [esp+0h] [ebp-Ch]
  _DWORD *large; // [esp+4h] [ebp-8h]

  v4 = cinfo[1];
  if ( a3 > 0x3B9AC9F4 )
    rf_jpeg_out_of_memory((int)cinfo, 3);
  if ( a3 % 8 )
    a3 += 8 - a3 % 8;
  if ( a2 >= 2 )
  {
    *(_DWORD *)(*cinfo + 20) = 14;
    *(_DWORD *)(*cinfo + 24) = a2;
    (*(void (__cdecl **)(_DWORD *))*cinfo)(cinfo);
  }
  large = rf_jpeg_get_large(cinfo, a3 + 12);
  if ( !large )
    rf_jpeg_out_of_memory((int)cinfo, 4);
  *(_DWORD *)(v4 + 76) += a3 + 12;
  *large = *(_DWORD *)(v4 + 4 * a2 + 60);
  large[1] = a3;
  large[2] = 0;
  *(_DWORD *)(v4 + 4 * a2 + 60) = large;
  return large + 3;
}

