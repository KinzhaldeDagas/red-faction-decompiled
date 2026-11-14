// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C9850 rf_material_deserialize
// UNREALRED VERIFIED [material-animation-20260903]: Deserializes one runtime material and its pooled curves. Types 0/1 load texture slot 0; type 1 also loads slot 1 and the clamped crossfade curve at +0x7C/+0x80; all supported types load self-illumination +0xB8/+0xBC and, for stream version >=0x40005, alpha +0xC0/+0xC4. Shared rate +0x78 defaults to 15 from version 0x40003 onward.
// UNREALRED VERIFIED [v3d-specular-fields-20260903]: Reads specular strength directly into material +0x84 and reflection-alignment cutoff directly into +0x88, immediately before ReflectionAmount at +0x8C.
char *__thiscall rf_material_deserialize(char *this, int *a2, int a3)
{
  char *result; // eax
  int v4; // [esp+78h] [ebp-10h]
  int i; // [esp+84h] [ebp-4h]

  *(_DWORD *)this = rf_binary_stream_read_int32_versioned(a2, 0, 0);
  *((_DWORD *)this + 30) = rf_binary_stream_read_int32_versioned(a2, 262147, 15);
  result = this;
  v4 = *(_DWORD *)this;
  if ( *(int *)this >= 0 )
  {
    if ( v4 <= 1 )
    {
      *(this + 8) = rf_binary_stream_read_bool_versioned(a2, 0, 1);
      rf_binary_stream_read_nul_string_to_buffer(a2, this + 20, 32, 0, nullptr);
      if ( !strcmp(this + 20, "$original_map") )
      {
        *((_DWORD *)this + 4) = -1;
      }
      else if ( !strcmp(this + 20, "$original_map_rgb") )
      {
        *((_DWORD *)this + 4) = -1;
        *((_DWORD *)this + 1) |= 2u;
      }
      else
      {
        *((_DWORD *)this + 4) = rf_bitmap_load_with_optional_mipmap_generation(this + 20, (void *)0xFFFFFFFF, 1);
      }
      *((_DWORD *)this + 14) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      *((float *)this + 15) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *((_DWORD *)this + 16) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      if ( *(_DWORD *)this == 1 )
      {
        rf_binary_stream_read_nul_string_to_buffer(a2, this + 72, 32, 0, nullptr);
        if ( this + strlen(this + 72) + 73 == this + 73 )
        {
          *((_DWORD *)this + 17) = -1;
        }
        else if ( !strcmp(this + 72, "$original_map") )
        {
          *((_DWORD *)this + 17) = -1;
        }
        else if ( !strcmp(this + 72, "$original_map_rgb") )
        {
          *((_DWORD *)this + 17) = -1;
          *((_DWORD *)this + 1) |= 4u;
        }
        else
        {
          *((_DWORD *)this + 17) = rf_bitmap_load_with_optional_mipmap_generation(this + 72, (void *)0xFFFFFFFF, 1);
        }
        *((_DWORD *)this + 27) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
        *((float *)this + 28) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
        *((_DWORD *)this + 29) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
        *((_DWORD *)this + 31) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
        if ( !rf_binary_stream_version_at_least(a2, 262147) )
          *((_DWORD *)this + 30) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
        if ( *((int *)this + 31) <= 0 )
        {
          *((_DWORD *)this + 32) = 0;
        }
        else
        {
          *((_DWORD *)this + 32) = *(_DWORD *)(a3 + 4) + 4 * **(_DWORD **)a3;
          **(_DWORD **)a3 += *((_DWORD *)this + 31);
          for ( i = 0; i < *((_DWORD *)this + 31); ++i )
          {
            *(float *)(*((_DWORD *)this + 32) + 4 * i) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
            *(float *)(*((_DWORD *)this + 32) + 4 * i) = rf_float_maximum_two_values(
                                                           *(float *)(*((_DWORD *)this + 32) + 4 * i),
                                                           0.0);
            *(float *)(*((_DWORD *)this + 32) + 4 * i) = rf_float_minimum_two_values(
                                                           *(float *)(*((_DWORD *)this + 32) + 4 * i),
                                                           1.0);
          }
        }
      }
      else
      {
        *(this + 72) = 0;
        *((_DWORD *)this + 17) = -1;
        *((_DWORD *)this + 27) = 0;
        *((float *)this + 28) = 1.0;
        *((_DWORD *)this + 29) = 0;
        *((_DWORD *)this + 31) = 0;
        *((_DWORD *)this + 32) = 0;
      }
      *((float *)this + 33) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *((float *)this + 34) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *((float *)this + 35) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      rf_binary_stream_read_nul_string_to_buffer(a2, this + 144, 32, 0, nullptr);
      if ( this + strlen(this + 144) + 145 == this + 145 )
        *((_DWORD *)this + 45) = -1;
      else
        *((_DWORD *)this + 45) = rf_bitmap_load_with_optional_mipmap_generation(this + 144, (void *)0xFFFFFFFF, 1);
      *((_DWORD *)this + 46) = rf_binary_stream_read_int32_versioned(a2, 262147, 1);
      *((_DWORD *)this + 47) = *(_DWORD *)(a3 + 12) + 4 * **(_DWORD **)(a3 + 8);
      **(_DWORD **)(a3 + 8) += *((_DWORD *)this + 46);
      rf_vfile_read_buffered_bytes_versioned(a2, *((char **)this + 47), 4 * *((_DWORD *)this + 46), 0, 0);
      result = (char *)rf_binary_stream_version_at_least(a2, 262149);
      if ( (_BYTE)result )
      {
        *((_DWORD *)this + 48) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
        *((_DWORD *)this + 49) = *(_DWORD *)(a3 + 20) + 4 * **(_DWORD **)(a3 + 16);
        **(_DWORD **)(a3 + 16) += *((_DWORD *)this + 48);
        return (char *)rf_vfile_read_buffered_bytes_versioned(
                         a2,
                         *((char **)this + 49),
                         4 * *((_DWORD *)this + 48),
                         0,
                         0);
      }
    }
    else if ( v4 == 2 )
    {
      *(this + 8) = rf_binary_stream_read_bool_versioned(a2, 262150, 1);
      *(this + 9) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      *(this + 10) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      *(this + 11) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      *((_DWORD *)this + 46) = rf_binary_stream_read_int32_versioned(a2, 262147, 1);
      *((_DWORD *)this + 47) = *(_DWORD *)(a3 + 12) + 4 * **(_DWORD **)(a3 + 8);
      **(_DWORD **)(a3 + 8) += *((_DWORD *)this + 46);
      rf_vfile_read_buffered_bytes_versioned(a2, *((char **)this + 47), 4 * *((_DWORD *)this + 46), 0, 0);
      result = (char *)rf_binary_stream_version_at_least(a2, 262149);
      if ( (_BYTE)result )
      {
        *((_DWORD *)this + 48) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
        *((_DWORD *)this + 49) = *(_DWORD *)(a3 + 20) + 4 * **(_DWORD **)(a3 + 16);
        **(_DWORD **)(a3 + 16) += *((_DWORD *)this + 48);
        return (char *)rf_vfile_read_buffered_bytes_versioned(
                         a2,
                         *((char **)this + 49),
                         4 * *((_DWORD *)this + 48),
                         0,
                         0);
      }
    }
  }
  return result;
}

