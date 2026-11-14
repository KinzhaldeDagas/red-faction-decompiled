// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047AAC0 rf_rfl_light_record_parse
// UNREALRED VERIFIED [rfl-light-decode]: Parses one version-180 light placement, raw byte, profile, packed color, and twelve typed tail slots into a 0x98-byte runtime record.
void __thiscall rf_rfl_light_record_parse(char *this, _DWORD *a2, int a3)
{
  int v4; // [esp+18h] [ebp-28h] BYREF
  int v5; // [esp+1Ch] [ebp-24h] BYREF
  int int32_versioned; // [esp+20h] [ebp-20h]
  float float_versioned; // [esp+24h] [ebp-1Ch]
  int v8; // [esp+28h] [ebp-18h] BYREF
  int v9[2]; // [esp+2Ch] [ebp-14h] BYREF
  int v10; // [esp+3Ch] [ebp-4h]

  if ( rf_vfile_get_slot_version(a2) >= 67 )
  {
    rf_string_construct_empty(v9);
    v10 = 0;
    rf_rgba8_default_construct_noop(&v8);
    *(_DWORD *)this = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    rf_binary_stream_read_string_object_versioned(a2, v9, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(a2, (float *)this + 3, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned(this + 24, 0, (int)unk_1C8FC18);
    rf_binary_stream_read_string_object_versioned(a2, (_DWORD *)this + 1, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a2, 0, 1);
    if ( rf_vfile_get_slot_version(a2) >= 98 )
    {
      int32_versioned = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      rf_rfl_light_profile_decode((int)this, int32_versioned);
      if ( rf_vfile_get_slot_version(a2) < 106 )
        *(this + 145) = 1;
      v8 = *rf_binary_stream_read_packed4bytes_versioned(a2, &v5, 0, &dword_1C8FC4C);
    }
    else
    {
      *((_DWORD *)this + 16) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      *((_DWORD *)this + 15) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    }
    *((float *)this + 20) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    if ( rf_vfile_get_slot_version(a2) < 120 )
    {
      float_versioned = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *((float *)this + 20) = *((float *)this + 20) + float_versioned;
    }
    *((float *)this + 22) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    *((float *)this + 23) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    *((float *)this + 24) = rf_binary_stream_read_float_versioned(a2, 120, 0.0);
    *((_DWORD *)this + 25) = rf_binary_stream_read_int32_versioned(a2, 121, 0);
    *((float *)this + 26) = rf_binary_stream_read_float_versioned(a2, 74, 0.0);
    if ( rf_vfile_get_slot_version(a2) >= 98 )
    {
      *((float *)this + 27) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *((float *)this + 29) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *((float *)this + 30) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *((float *)this + 28) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *((float *)this + 31) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *((float *)this + 32) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    }
    else
    {
      *((float *)this + 27) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      v8 = *rf_binary_stream_read_packed4bytes_versioned(a2, &v4, 0, &dword_1C8FC4C);
      *(this + 132) = rf_binary_stream_read_bool_versioned(a2, 0, 1);
      *(this + 134) = rf_binary_stream_read_bool_versioned(a2, 0, 1);
    }
    *((float *)this + 17) = (double)(unsigned __int8)v8 / 255.0;
    *((float *)this + 18) = (double)BYTE1(v8) / 255.0;
    *((float *)this + 19) = (double)BYTE2(v8) / 255.0;
    *((_DWORD *)this + 37) = -1;
    if ( !a3 )
    {
      *(this + 146) = 1;
      *(this + 134) = 0;
      if ( rf_renderer_world_lighting_enabled() )
        rf_rfl_light_runtime_initialize((int)this);
    }
    v10 = -1;
    rf_string_destroy_buffer(v9);
  }
  else
  {
    rf_rfl_light_record_parse_pre67((float *)this, (int)a2);
  }
}

