// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E3600 rf_d3d8_texture_cache_allocate_upload_tile
// UNREALRED VERIFIED [texture-upload-20261028]: Eightarguments bitmaphandle(unused),cacheentry,tileindex,CPUdata,palette/aux,sourcewidth,sourceheight,internalformat. Startsbits/pixelquery0x574A00 whosevalueunused. Reads logicaltilewidth/heightfromrecord+24/+28. If0x1DAEDF0,promotespowers-of-two via16iterationsearch; clampswidth[min0x1DAEDDC,max0x187CCCC],height[min0x1DAEDE4,max0x187CCD0]. If0x1DAEDEC,forcessquaremax(width,height) AFTERclampingwithoutreclamp. SavesUVscaleslogical/allocated. Creates1-leveltexture0x5E1EE0; failure-1. If CPUdatanonnull,calls0x5E1FB0 uploadlevel0; failure-1withoutreleasingnewtexture. Successstorestexture,tileestimatedbytes2*w*h,updatesglobalmemory0x1E0154C,andUVscales,returns1. No tilebounds,caps/zerodimensionorformatvalidation; nullCPUdata leavesGPUcontentsundefined.
int __cdecl rf_d3d8_texture_cache_allocate_upload_tile(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
  int v9; // [esp+0h] [ebp-24h]
  int i; // [esp+8h] [ebp-1Ch]
  int j; // [esp+8h] [ebp-1Ch]
  float v12; // [esp+Ch] [ebp-18h]
  int v13; // [esp+10h] [ebp-14h]
  int v14; // [esp+14h] [ebp-10h]
  float v15; // [esp+18h] [ebp-Ch]
  int v16; // [esp+20h] [ebp-4h] BYREF

  rf_bitmap_format_bits_per_pixel(a8);
  v14 = *(_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * a3 + 24);
  v13 = *(_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * a3 + 28);
  if ( unk_1DAEDF0 )
  {
    for ( i = 0; i < 16; ++i )
    {
      if ( v14 > 1 << i && v14 <= 1 << (i + 1) )
      {
        v14 = 1 << (i + 1);
        break;
      }
    }
    for ( j = 0; j < 16; ++j )
    {
      if ( v13 > 1 << j && v13 <= 1 << (j + 1) )
      {
        v13 = 1 << (j + 1);
        break;
      }
    }
  }
  if ( v14 >= dword_1DAEDDC )
  {
    if ( v14 > dword_187CCCC )
      v14 = dword_187CCCC;
  }
  else
  {
    v14 = dword_1DAEDDC;
  }
  if ( v13 >= dword_1DAEDE4 )
  {
    if ( v13 > dword_187CCD0 )
      v13 = dword_187CCD0;
  }
  else
  {
    v13 = dword_1DAEDE4;
  }
  if ( unk_1DAEDEC )
  {
    if ( v14 <= v13 )
      v9 = v13;
    else
      v9 = v14;
    v14 = v9;
    v13 = v9;
  }
  v15 = (double)*(int *)(*(_DWORD *)(a2 + 12) + 32 * a3 + 24) / (double)v14;
  v12 = (double)*(int *)(*(_DWORD *)(a2 + 12) + 32 * a3 + 28) / (double)v13;
  v16 = 0;
  if ( rf_d3d8_create_texture_for_bitmap_format(a8, v14, v13, 1, &v16) )
    return -1;
  if ( a4
    && rf_d3d8_upload_texture_level_convert_to_u16(
         0,
         a4,
         a5,
         a6,
         a7,
         a8,
         (_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * a3),
         v14,
         v13,
         v16) )
  {
    return -1;
  }
  *(_DWORD *)(32 * a3 + *(_DWORD *)(a2 + 12)) = v16;
  *(_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * a3 + 4) = 2 * v13 * v14;
  unk_1E0154C += *(_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * a3 + 4);
  *(float *)(*(_DWORD *)(a2 + 12) + 32 * a3 + 8) = v15;
  *(float *)(*(_DWORD *)(a2 + 12) + 32 * a3 + 12) = v12;
  return 1;
}

