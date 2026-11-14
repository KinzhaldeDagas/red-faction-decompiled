// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E1B90 rf_d3d8_texture_cache_upload_mip_chain
// UNREALRED VERIFIED [texture-upload-20261028]: Arguments bitmaphandle,cacheentry. Getswidth,height,mipcount; rejectsdimensionsnot0x5E1DE0,sprintfdiagnostic Not drawing bitmap,returns0 withoutupload. LocksCPUbitmap0x576610,getsformatbytes/pixel,createsGPUtexturewithreportedmipcount0x5E1EE0; createfailure returns-1withoutCPUunlock. For eachmipcalls0x5E1FB0 withcurrentpointer/dimensions,source advancesbytesperpixel*width*height,width/heightintegerhalvedwithoutmin1. Uploadfailure releasesGPUtexture,returns-1withoutCPUunlock. SuccessunlocksCPUhandle0x577F30,storesGPUtextureintile0,estimatedbytes=sum2*w*h irrespectiveactualformat,adds toglobal0x1E0154C,setsUVscales1/1,returns1. Doesnotinitializeadditionaltiles orforcetilecount1; callercomputedtilecountisretained. Inneruploadalgorithmnotinferredhere.
int __cdecl rf_d3d8_texture_cache_upload_mip_chain(unsigned int a1, int a2)
{
  const char *source_record_name_pointer; // eax
  _DWORD v4[8]; // [esp+4h] [ebp-70h] BYREF
  int i; // [esp+24h] [ebp-50h]
  int v6; // [esp+28h] [ebp-4Ch] BYREF
  int v7; // [esp+2Ch] [ebp-48h]
  int v8; // [esp+30h] [ebp-44h] BYREF
  int v9; // [esp+34h] [ebp-40h] BYREF
  int v10; // [esp+38h] [ebp-3Ch] BYREF
  int v11; // [esp+3Ch] [ebp-38h]
  int v12; // [esp+40h] [ebp-34h]
  int v13; // [esp+44h] [ebp-30h]
  int v14; // [esp+48h] [ebp-2Ch] BYREF
  int v15; // [esp+4Ch] [ebp-28h] BYREF
  int v16; // [esp+50h] [ebp-24h]
  int v17; // [esp+54h] [ebp-20h] BYREF
  int v18; // [esp+58h] [ebp-1Ch]
  char (__cdecl *v19)(int, float *); // [esp+5Ch] [ebp-18h]
  int v20; // [esp+60h] [ebp-14h]
  int v21; // [esp+64h] [ebp-10h]
  int v22; // [esp+68h] [ebp-Ch]
  int v23; // [esp+6Ch] [ebp-8h]
  int v24; // [esp+70h] [ebp-4h]

  rf_bitmap_get_resolved_upload_metadata(a1, &v9, &v14, &v10, &v6);
  if ( rf_d3d8_mipmap_dimensions_supported_4_to_256(v9, v14) )
  {
    v11 = rf_bitmap_lock_cpu_pixels_resolved(a1, &v15, &v8);
    v12 = rf_bitmap_format_bytes_per_pixel(v11);
    v17 = 0;
    v23 = 0;
    v18 = v9;
    v13 = v14;
    v16 = v15;
    v7 = 0;
    if ( rf_d3d8_create_texture_for_bitmap_format(v11, v9, v14, v6, &v17) )
    {
      return -1;
    }
    else
    {
      v23 = v17;
      v19 = rf_ai_copy_route_target_position;
      v22 = 0;
      v21 = 0;
      v20 = 0;
      for ( i = 0; i < v6; ++i )
      {
        v4[4] = 0;
        v4[5] = 0;
        v4[6] = v18;
        v4[7] = v13;
        if ( rf_d3d8_upload_texture_level_convert_to_u16(i, v16, v8, v18, v13, v11, v4, v18, v13, v23) )
        {
          (*(void (__thiscall **)(int, int))(*(_DWORD *)v23 + 8))(v23, v23);
          return -1;
        }
        v7 += 2 * v13 * v18;
        v16 += v12 * v13 * v18;
        v18 /= 2;
        v13 /= 2;
      }
      rf_bitmap_unlock_cpu_handle_wrapper(a1);
      v24 = 0;
      **(_DWORD **)(a2 + 12) = v17;
      *(_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * v24 + 4) = v7;
      unk_1E0154C += *(_DWORD *)(*(_DWORD *)(a2 + 12) + 32 * v24 + 4);
      *(float *)(*(_DWORD *)(a2 + 12) + 32 * v24 + 8) = 1.0;
      *(float *)(*(_DWORD *)(a2 + 12) + 32 * v24 + 12) = 1.0;
      return 1;
    }
  }
  else
  {
    source_record_name_pointer = (const char *)rf_bitmap_get_source_record_name_pointer(a1);
    sprintf(&unk_18CD828, "D3D: Not drawing %dx%d bitmap '%s'\n", v9, v14, source_record_name_pointer);
    return 0;
  }
}

