// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047E990 rf_rfl_ambient_sounds_section_load
// UNREALRED VERIFIED [world-uid-ownership]: Loads section 0x500 ambient sounds and creates one UID-keyed runtime sound record for every admitted authored entry.
// UNREALRED VERIFIED [ambient-audio]: Loads RFL section 0x500. Each version-180 record consumes UID, position, one ignored boolean byte, uint16-length filename, minimum distance, volume, version-103+ rolloff defaulting to 1.0, and version-103+ startup delay milliseconds defaulting to zero. Dedicated mode skips persistent creation after consuming the complete record.
void __cdecl rf_rfl_ambient_sounds_section_load(_DWORD *a1)
{
  char *v1; // eax
  float v2; // [esp+4h] [ebp-54h]
  float v3; // [esp+8h] [ebp-50h]
  int v4; // [esp+Ch] [ebp-4Ch]
  int i; // [esp+14h] [ebp-44h]
  int v6; // [esp+18h] [ebp-40h]
  float float_versioned; // [esp+1Ch] [ebp-3Ch]
  int int32_versioned; // [esp+20h] [ebp-38h]
  float v9[3]; // [esp+24h] [ebp-34h] BYREF
  int v10[2]; // [esp+30h] [ebp-28h] BYREF
  float v11; // [esp+38h] [ebp-20h]
  int v12; // [esp+3Ch] [ebp-1Ch]
  _DWORD v13[2]; // [esp+40h] [ebp-18h] BYREF
  float v14; // [esp+48h] [ebp-10h]
  int v15; // [esp+54h] [ebp-4h]

  rf_string_construct_empty(v10);
  v15 = 0;
  rf_string_construct_empty(v13);
  LOBYTE(v15) = 1;
  rf_vector3_default_construct_noop(v9);
  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  for ( i = 0; i < int32_versioned; ++i )
  {
    v6 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_vector3_versioned(a1, v9, 0, unk_1C8FBDC);
    if ( rf_vfile_get_slot_version(a1) < 67 )
      rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    rf_binary_stream_read_string_object_versioned(a1, v10, 0, nullptr);
    float_versioned = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v11 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v14 = rf_binary_stream_read_float_versioned(a1, 103, 1.0);
    v12 = rf_binary_stream_read_int32_versioned(a1, 103, 0);
    if ( byte_704E83 != 1 )
    {
      v4 = v12;
      v3 = v14;
      v2 = v11;
      v1 = (char *)rf_string_object_c_str_or_empty(v10);
      rf_ambient_sound_create(v6, v1, v9, float_versioned, v2, v3, v4);
    }
  }
  LOBYTE(v15) = 0;
  rf_string_destroy_buffer(v13);
  v15 = -1;
  rf_string_destroy_buffer(v10);
}

