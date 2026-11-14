// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E3AB0 rf_d3d8_texture_cache_rebuild_from_bitmap
// UNREALRED VERIFIED [texture-upload-20261028]: Arguments bitmaphandle,16-bytecacheentry. Releasesoldtiles0x5E1A30,queriesuploadmetadata. Computesceil(bitmapW/maxW0x187CCCC)*ceil(bitmapH/maxH0x187CCD0),storesSIGNED16tilecount+4,allocates32*countbytes,initializesONLYGPUtexturepointers0. Sets handle+0,dirtybyte+11=0,lockcount+8=0,leavesrefcountbyte+10. If mipcount<=1,locksCPUbitmap,splitsrectanglerowmajorwithlogicalx/y/w/h ineach32-bytetile+16/+20/+24/+28,calls0x5E3600 per tile. IGNORESper-tilefailure,unlocksCPU,andreturns1. If mipcount>1,initializestile0rectanglewholebitmap anddelegates0x5E1B90; tilecountmayremain>1. No zero-maxdimensions,allocationfailure,16-bitcountoverflow or uninitializedmetadataoutputscheck. Metadata type0leavesmipcountoutputunchanged.
int __cdecl rf_d3d8_texture_cache_rebuild_from_bitmap(unsigned int a1, int a2)
{
  int v3; // [esp+4h] [ebp-40h]
  int v4; // [esp+Ch] [ebp-38h]
  int j; // [esp+10h] [ebp-34h]
  int v6; // [esp+14h] [ebp-30h] BYREF
  int v7; // [esp+18h] [ebp-2Ch] BYREF
  int v8; // [esp+1Ch] [ebp-28h] BYREF
  int v9; // [esp+20h] [ebp-24h] BYREF
  int v10; // [esp+24h] [ebp-20h] BYREF
  int v11; // [esp+28h] [ebp-1Ch] BYREF
  int i; // [esp+2Ch] [ebp-18h]
  int v13; // [esp+30h] [ebp-14h]
  int v14; // [esp+34h] [ebp-10h]
  int v15; // [esp+38h] [ebp-Ch]
  int v16; // [esp+3Ch] [ebp-8h]
  int v17; // [esp+40h] [ebp-4h]

  rf_d3d8_texture_cache_release_tiles(a2);
  rf_bitmap_get_resolved_upload_metadata(a1, &v8, &v10, &v9, &v6);
  v13 = (v8 + dword_187CCCC - 1) / dword_187CCCC;
  v17 = (v10 + dword_187CCD0 - 1) / dword_187CCD0;
  *(_BYTE *)(a2 + 11) = 0;
  *(_DWORD *)a2 = a1;
  *(_WORD *)(a2 + 4) = v17 * v13;
  *(_DWORD *)(a2 + 12) = operator new(32 * *(__int16 *)(a2 + 4));
  *(_WORD *)(a2 + 8) = 0;
  for ( i = 0; i < *(__int16 *)(a2 + 4); ++i )
    *(_DWORD *)(32 * i + *(_DWORD *)(a2 + 12)) = 0;
  if ( v6 <= 1 )
  {
    v4 = rf_bitmap_lock_cpu_pixels_resolved(a1, &v11, &v7);
    v14 = 0;
    v16 = 0;
    for ( j = 0; j < v17; ++j )
    {
      v15 = 0;
      if ( v10 - v16 <= dword_187CCD0 )
        v3 = v10 - v16;
      else
        v3 = dword_187CCD0;
      for ( i = 0; i < v13; ++i )
      {
        *(_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * v14 + 16) = v15;
        *(_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * v14 + 20) = v16;
        if ( v8 - v15 <= dword_187CCCC )
          *(_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * v14 + 24) = v8 - v15;
        else
          *(_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * v14 + 24) = dword_187CCCC;
        v15 += *(_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * v14 + 24);
        *(_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * v14 + 28) = v3;
        rf_d3d8_texture_cache_allocate_upload_tile(a1, a2, v14++, v11, v7, v8, v10, v4);
      }
      v16 += v3;
    }
    rf_bitmap_unlock_cpu_handle_wrapper(a1);
    return 1;
  }
  else
  {
    *(_DWORD *)(*(_DWORD *)(a2 + 12) + 16) = 0;
    *(_DWORD *)(*(_DWORD *)(a2 + 12) + 20) = 0;
    *(_DWORD *)(*(_DWORD *)(a2 + 12) + 24) = v8;
    *(_DWORD *)(*(_DWORD *)(a2 + 12) + 28) = v10;
    return rf_d3d8_texture_cache_upload_mip_chain(a1, a2);
  }
}

