// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FBE80 rf_scene_material_binding_read_index_or_legacy
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args vfile,pool-cursors descriptor{materialCountPtr0,materialsBase4,valueCountPtr8,valuesBase12,extraCountPtr16,extraBase20}. NULL file no-op. Version>=0x40000 reads int32 materialindex136 and returns,withoutlegacy payload. Older:materialindex=*materialCount,record=base+200*index,incrementcount;NO capacity guard. Reads record120 int(version>=0x30009,default15),124frameCount int0,0type int>=0x1000B(default0),BYTE8bool>=0x30012(default0). Base-map name20,max32:literal $original_map ->handle16=-1,else bitmapload evenempty. Base fields56int>=0x30012 default0,60floatdefault1,64intdefault0. If type1,secondary name72 max32 threshold0x1000B:empty/$original_map ->handle68=-1,else load. Version>=0x30012 reads secondary108int0,112float1,116int0,then allocates record128 into shared float pool and reads
// frameCount values threshold0x1000B,clamps each max(value,0) thenmin(value,1). Older versions instead read shared56int>=0x10005 default1,copyto108,force60/112=1,read64int>=0x10006 default0,copyto116. Type!=1 clearssecondaryname/handle,108=0,112=1,116=0. Reads threefloats132/136/140 threshold0x30007 default0;overlayname144 max32 sameversion defaultempty,handle180=-1 ifempty elseload. Sets184count=1,188ptr=extraBase+4*(*extraCount)++,readsonefloat>=0x30012 default0. Forversion<0x30012 ANDtype1,reads/clamps record128 per-frame float array HERE after overlay/extra rather than earlier. Does not initialize all200bytes,free assets,validate counts/indices/streamstatus or rollback pools. No globalmaterialtable write onnew-index path.
void __thiscall rf_scene_material_binding_read_index_or_legacy(_DWORD *this, int *a2, int a3)
{
  int v4; // [esp+54h] [ebp-Ch]
  int i; // [esp+5Ch] [ebp-4h]
  int j; // [esp+5Ch] [ebp-4h]

  if ( a2 )
  {
    if ( rf_binary_stream_version_at_least(a2, 0x40000) )
    {
      *(this + 34) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    }
    else
    {
      *(this + 34) = **(_DWORD **)a3;
      v4 = *(_DWORD *)(a3 + 4) + 200 * *(this + 34);
      ++**(_DWORD **)a3;
      *(_DWORD *)(v4 + 120) = rf_binary_stream_read_int32_versioned(a2, 196617, 15);
      *(_DWORD *)(v4 + 124) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      *(_DWORD *)v4 = rf_binary_stream_read_int32_versioned(a2, 65547, 0);
      *(_BYTE *)(v4 + 8) = rf_binary_stream_read_bool_versioned(a2, 196626, 0);
      rf_binary_stream_read_nul_string_to_buffer(a2, (char *)(v4 + 20), 32, 0, nullptr);
      if ( !strcmp((const char *)(v4 + 20), "$original_map") )
        *(_DWORD *)(v4 + 16) = -1;
      else
        *(_DWORD *)(v4 + 16) = rf_bitmap_load_with_optional_mipmap_generation((char *)(v4 + 20), (void *)0xFFFFFFFF, 1);
      *(_DWORD *)(v4 + 56) = rf_binary_stream_read_int32_versioned(a2, 196626, 0);
      *(float *)(v4 + 60) = rf_binary_stream_read_float_versioned(a2, 196626, 1.0);
      *(_DWORD *)(v4 + 64) = rf_binary_stream_read_int32_versioned(a2, 196626, 0);
      if ( *(_DWORD *)v4 == 1 )
      {
        rf_binary_stream_read_nul_string_to_buffer(a2, (char *)(v4 + 72), 32, 65547, nullptr);
        if ( v4 + 72 + strlen((const char *)(v4 + 72)) + 1 == v4 + 73 )
        {
          *(_DWORD *)(v4 + 68) = -1;
        }
        else if ( !strcmp((const char *)(v4 + 72), "$original_map") )
        {
          *(_DWORD *)(v4 + 68) = -1;
        }
        else
        {
          *(_DWORD *)(v4 + 68) = rf_bitmap_load_with_optional_mipmap_generation(
                                   (char *)(v4 + 72),
                                   (void *)0xFFFFFFFF,
                                   1);
        }
        if ( rf_binary_stream_version_at_least(a2, 196626) )
        {
          *(_DWORD *)(v4 + 108) = rf_binary_stream_read_int32_versioned(a2, 196626, 0);
          *(float *)(v4 + 112) = rf_binary_stream_read_float_versioned(a2, 196626, 1.0);
          *(_DWORD *)(v4 + 116) = rf_binary_stream_read_int32_versioned(a2, 196626, 0);
          if ( *(_DWORD *)v4 == 1 )
          {
            *(_DWORD *)(v4 + 128) = *(_DWORD *)(a3 + 12) + 4 * **(_DWORD **)(a3 + 8);
            **(_DWORD **)(a3 + 8) += *(_DWORD *)(v4 + 124);
            for ( i = 0; i < *(_DWORD *)(v4 + 124); ++i )
            {
              *(float *)(*(_DWORD *)(v4 + 128) + 4 * i) = rf_binary_stream_read_float_versioned(a2, 65547, 0.0);
              *(float *)(*(_DWORD *)(v4 + 128) + 4 * i) = rf_float_maximum_two_values(
                                                            *(float *)(*(_DWORD *)(v4 + 128) + 4 * i),
                                                            0.0);
              *(float *)(*(_DWORD *)(v4 + 128) + 4 * i) = rf_float_minimum_two_values(
                                                            *(float *)(*(_DWORD *)(v4 + 128) + 4 * i),
                                                            1.0);
            }
          }
        }
        else
        {
          *(_DWORD *)(v4 + 56) = rf_binary_stream_read_int32_versioned(a2, 65541, 1);
          *(_DWORD *)(v4 + 108) = *(_DWORD *)(v4 + 56);
          *(float *)(v4 + 60) = 1.0;
          *(float *)(v4 + 112) = 1.0;
          *(_DWORD *)(v4 + 64) = rf_binary_stream_read_int32_versioned(a2, 65542, 0);
          *(_DWORD *)(v4 + 116) = *(_DWORD *)(v4 + 64);
        }
      }
      else
      {
        *(_BYTE *)(v4 + 72) = 0;
        *(_DWORD *)(v4 + 68) = -1;
        *(_DWORD *)(v4 + 108) = 0;
        *(float *)(v4 + 112) = 1.0;
        *(_DWORD *)(v4 + 116) = 0;
      }
      *(float *)(v4 + 132) = rf_binary_stream_read_float_versioned(a2, 196615, 0.0);
      *(float *)(v4 + 136) = rf_binary_stream_read_float_versioned(a2, 196615, 0.0);
      *(float *)(v4 + 140) = rf_binary_stream_read_float_versioned(a2, 196615, 0.0);
      rf_binary_stream_read_nul_string_to_buffer(a2, (char *)(v4 + 144), 32, 196615, byte_64732A);
      if ( v4 + 144 + strlen((const char *)(v4 + 144)) + 1 == v4 + 145 )
        *(_DWORD *)(v4 + 180) = -1;
      else
        *(_DWORD *)(v4 + 180) = rf_bitmap_load_with_optional_mipmap_generation(
                                  (char *)(v4 + 144),
                                  (void *)0xFFFFFFFF,
                                  1);
      *(_DWORD *)(v4 + 184) = 1;
      *(_DWORD *)(v4 + 188) = *(_DWORD *)(a3 + 20) + 4 * (**(_DWORD **)(a3 + 16))++;
      **(float **)(v4 + 188) = rf_binary_stream_read_float_versioned(a2, 196626, 0.0);
      if ( !rf_binary_stream_version_at_least(a2, 196626) && *(_DWORD *)v4 == 1 )
      {
        *(_DWORD *)(v4 + 128) = *(_DWORD *)(a3 + 12) + 4 * **(_DWORD **)(a3 + 8);
        **(_DWORD **)(a3 + 8) += *(_DWORD *)(v4 + 124);
        for ( j = 0; j < *(_DWORD *)(v4 + 124); ++j )
        {
          *(float *)(*(_DWORD *)(v4 + 128) + 4 * j) = rf_binary_stream_read_float_versioned(a2, 65547, 0.0);
          *(float *)(*(_DWORD *)(v4 + 128) + 4 * j) = rf_float_maximum_two_values(
                                                        *(float *)(*(_DWORD *)(v4 + 128) + 4 * j),
                                                        0.0);
          *(float *)(*(_DWORD *)(v4 + 128) + 4 * j) = rf_float_minimum_two_values(
                                                        *(float *)(*(_DWORD *)(v4 + 128) + 4 * j),
                                                        1.0);
        }
      }
    }
  }
}

