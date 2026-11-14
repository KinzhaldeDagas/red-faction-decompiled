// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00482750 rf_rfl_items_section_load
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: RFL item quantity is NOT clamped/defaulted when zero/negative. Actual MPmode==1 passes definition ACTIVEcount+2C to473280; other modes pass exact authored signed RFL count. Respawn raw0 becomes-1; raw-1 with any nonzero MP reads definition+38 milliseconds; all other nonzero raw values wrap32*1000 (SP-1 becomes-1000). Spawn arg8=1 yields instanceflag10, parentowner-1. Class lookup first473770; missing-class+MP/rawrespawn-1 native unchecked negative definition access is an unsafe host domain, not fabricated fallback. Successful object receives RFL UID+20 and signedchar byte+28.
void __cdecl rf_rfl_items_section_load(_DWORD *a1)
{
  char *v1; // eax
  char *v2; // eax
  char *v3; // eax
  int v4; // [esp-1Ch] [ebp-8Ch]
  int v5; // [esp-1Ch] [ebp-8Ch]
  int v6; // [esp-Ch] [ebp-7Ch]
  int v7; // [esp-Ch] [ebp-7Ch]
  int v8; // [esp+4h] [ebp-6Ch]
  int v9; // [esp+8h] [ebp-68h]
  int i; // [esp+Ch] [ebp-64h]
  int int32_versioned; // [esp+10h] [ebp-60h]
  int v12; // [esp+14h] [ebp-5Ch]
  int v13[2]; // [esp+18h] [ebp-58h] BYREF
  int v14; // [esp+20h] [ebp-50h]
  float v15[3]; // [esp+24h] [ebp-4Ch] BYREF
  int v16; // [esp+30h] [ebp-40h]
  int v17[2]; // [esp+34h] [ebp-3Ch] BYREF
  int v18[9]; // [esp+3Ch] [ebp-34h] BYREF
  int v19; // [esp+60h] [ebp-10h]
  int v20; // [esp+6Ch] [ebp-4h]

  rf_string_construct_empty(v17);
  v20 = 0;
  rf_string_construct_empty(v13);
  LOBYTE(v20) = 1;
  rf_vector3_default_construct_noop(v15);
  rf_matrix3_construct((char *)v18);
  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  for ( i = 0; i < int32_versioned; ++i )
  {
    v12 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_string_object_versioned(a1, v17, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(a1, v15, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned((char *)v18, 0, (int)unk_1C8FC18);
    rf_binary_stream_read_string_object_versioned(a1, v13, 0, nullptr);
    if ( rf_vfile_get_slot_version(a1) < 67 )
      rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, (unsigned __int8)byte_6FCCA0[0], 1);
    v14 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    v16 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    v19 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    v1 = (char *)rf_string_object_c_str_or_empty(v17);
    v9 = rf_item_definition_find_by_name(v1);
    if ( v16 )
    {
      if ( v16 == -1 && rf_multiplayer_runtime_mode )
        v16 = unk_6F9168[20 * v9];
      else
        v16 *= 1000;
    }
    else
    {
      v16 = -1;
    }
    if ( v9 >= 0 )
    {
      if ( rf_multiplayer_runtime_mode == 1 )
      {
        v6 = v16;
        v4 = unk_6F915C[20 * v9];
        v2 = (char *)rf_string_object_c_str_or_empty(v13);
        v8 = rf_item_instance_spawn(v9, v2, v4, -1, v15, (float *)v18, v6, 1, 0);
        if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 && dword_78C248 < 200 )
          dword_78BF28[dword_78C248++] = *(_DWORD *)(v8 + 44);
      }
      else
      {
        v7 = v16;
        v5 = v14;
        v3 = (char *)rf_string_object_c_str_or_empty(v13);
        v8 = rf_item_instance_spawn(v9, v3, v5, -1, v15, (float *)v18, v7, 1, 0);
      }
      if ( v8 )
      {
        *(_BYTE *)(v8 + 40) = v19;
        *(_DWORD *)(v8 + 32) = v12;
      }
    }
  }
  LOBYTE(v20) = 0;
  rf_string_destroy_buffer(v13);
  v20 = -1;
  rf_string_destroy_buffer(v17);
}

