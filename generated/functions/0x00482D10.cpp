// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00482D10 rf_rfl_triggers_section_load
// UNREALRED VERIFIED [mission-startup-20261020] CORRECTION [version180 serialized fields]: after shape int32 comes ButtonActiveTime float, signed activation-limit int32 (exact -1 infinite), use bool and key string. Next five bytes are weapon bool, RAW NPC policy byte, auto-Use bool(flag4), startup bool(flag8), vehicle bool(flag80). After geometry/UIDs/disabled comes clutter ResetTime float then InsideTime float. UE previously skipped NPC policy, shifted flags, swapped timers and truncated the signed limit; those mappings were incorrect. Boolean readers normalize all nonzero bytes; the NPC byte is not normalized.
// UNREALRED VERIFIED [trigger-attachment-20261020] Attachment UID is the v165 signed32 read with default-1 (descriptor+0x20); separate v166 UID is use-clutter descriptor+0x24. Retail v180 audit94maps/2367triggers found5 attached triggers, all entity-owned: L1S1 miners9839/9428, L7S2 Gryphon4952, L19S2B Hendrix12167, L19S3 Hendrix11955. Three owners start inactive, making owner-state propagation relevant to real campaign behavior.
void __cdecl rf_rfl_triggers_section_load(_DWORD *a1)
{
  char *v1; // eax
  int *v2; // eax
  int v3; // [esp+Ch] [ebp-E8h] BYREF
  int v4; // [esp+10h] [ebp-E4h]
  int v5; // [esp+14h] [ebp-E0h] BYREF
  int v6; // [esp+18h] [ebp-DCh] BYREF
  int v7; // [esp+1Ch] [ebp-D8h] BYREF
  int j; // [esp+20h] [ebp-D4h]
  char v9; // [esp+26h] [ebp-CEh] BYREF
  char v10; // [esp+27h] [ebp-CDh] BYREF
  _BYTE v11[15]; // [esp+28h] [ebp-CCh] BYREF
  char v12; // [esp+37h] [ebp-BDh] BYREF
  int int32_versioned; // [esp+38h] [ebp-BCh]
  int v14; // [esp+3Ch] [ebp-B8h] BYREF
  int v15[2]; // [esp+40h] [ebp-B4h] BYREF
  _BYTE self[12]; // [esp+48h] [ebp-ACh] BYREF
  int v17; // [esp+54h] [ebp-A0h]
  int v18; // [esp+58h] [ebp-9Ch] BYREF
  int v19; // [esp+5Ch] [ebp-98h] BYREF
  int v20; // [esp+60h] [ebp-94h]
  int v21[3]; // [esp+64h] [ebp-90h] BYREF
  int v22; // [esp+70h] [ebp-84h] BYREF
  _BYTE Buffer[12]; // [esp+74h] [ebp-80h] BYREF
  char v24[36]; // [esp+80h] [ebp-74h] BYREF
  int v25; // [esp+A4h] [ebp-50h] BYREF
  int v26; // [esp+A8h] [ebp-4Ch] BYREF
  int v27[2]; // [esp+ACh] [ebp-48h] BYREF
  _DWORD v28[3]; // [esp+B4h] [ebp-40h] BYREF
  char v29; // [esp+C0h] [ebp-34h] BYREF
  char v30[3]; // [esp+C1h] [ebp-33h] BYREF
  int v31; // [esp+C4h] [ebp-30h] BYREF
  float v32[2]; // [esp+C8h] [ebp-2Ch] BYREF
  char v33; // [esp+D3h] [ebp-21h] BYREF
  _DWORD v34[2]; // [esp+D4h] [ebp-20h] BYREF
  int v35; // [esp+DCh] [ebp-18h] BYREF
  int i; // [esp+E0h] [ebp-14h]
  unsigned __int8 v37; // [esp+E6h] [ebp-Eh] BYREF
  char v38; // [esp+E7h] [ebp-Dh] BYREF
  int v39; // [esp+F0h] [ebp-4h]

  rf_vector3_default_construct_noop(v11);
  rf_string_construct_empty(v34);
  v39 = 0;
  rf_string_construct_empty(v15);
  LOBYTE(v39) = 1;
  rf_rfl_trigger_record_construct_string_members(self);
  LOBYTE(v39) = 2;
  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  for ( i = 0; i < int32_versioned; ++i )
  {
    rf_binary_stream_serialize_int32(a1, &v35, 0, 0);
    rf_binary_stream_serialize_string_object(a1, (std::exception *)self, 0, nullptr);
    if ( rf_vfile_get_slot_version(a1) < 65 )
      rf_binary_stream_serialize_string_object(a1, (std::exception *)unk_6FCCC0, 0, nullptr);
    rf_binary_stream_serialize_bool(a1, byte_6FCCA0, 0, 1);
    rf_binary_stream_serialize_int32(a1, &v14, 0, 0);
    if ( rf_vfile_get_slot_version(a1) >= 134 )
    {
      rf_binary_stream_serialize_float32(a1, (float *)&v3, 0, 0.0);
      v18 = (int)(*(float *)&v3 * 1000.0);
    }
    else
    {
      rf_binary_stream_serialize_int32(a1, &v18, 0, 0);
    }
    rf_binary_stream_serialize_int32(a1, &v19, 0, 0);
    rf_binary_stream_serialize_bool(a1, &v9, 0, 1);
    rf_binary_stream_read_string_object_versioned(a1, v15, 103, (char *)&byte_63886B);
    rf_binary_stream_serialize_bool(a1, &v12, 0, 1);
    rf_binary_stream_serialize_uint8(a1, (char *)&v37, 44, 0);
    rf_binary_stream_serialize_bool(a1, &v33, 47, 0);
    rf_binary_stream_serialize_bool(a1, &v38, 59, 0);
    rf_binary_stream_serialize_bool(a1, &v10, 162, 0);
    if ( v14 )
    {
      if ( v14 != 1 )
        continue;
      rf_binary_stream_serialize_vector3(a1, Buffer, 0, unk_1C8FBDC);
      rf_binary_stream_serialize_matrix3_vectors_201(a1, v24, 0, (int)unk_1C8FC18);
      rf_binary_stream_serialize_float32(a1, (float *)&v26, 0, 0.0);
      rf_binary_stream_serialize_float32(a1, (float *)&v25, 0, 0.0);
      rf_binary_stream_serialize_float32(a1, (float *)v27, 0, 0.0);
      rf_binary_stream_serialize_bool(a1, &v29, 109, 0);
    }
    else
    {
      rf_binary_stream_serialize_vector3(a1, Buffer, 0, unk_1C8FBDC);
      rf_binary_stream_serialize_float32(a1, (float *)&v22, 0, 0.0);
    }
    rf_binary_stream_serialize_int32(a1, v21, 104, -1);
    v21[1] = rf_binary_stream_read_int32_versioned(a1, 165, -1);
    v21[2] = rf_binary_stream_read_int32_versioned(a1, 166, -1);
    rf_binary_stream_serialize_bool(a1, v30, 116, 0);
    rf_binary_stream_serialize_float32(a1, (float *)&v31, 119, 0.0);
    rf_binary_stream_serialize_float32(a1, v32, 126, 0.0);
    rf_binary_stream_serialize_int32(a1, &v5, 177, -1);
    self[8] = v5;
    v6 = -1;
    rf_binary_stream_serialize_int32(a1, &v7, 0, 0);
    rf_pointer_array_release_storage((void **)unk_6FCCC8);
    for ( j = 0; j < v7; ++j )
    {
      rf_binary_stream_serialize_int32(a1, &v6, 0, 0);
      rf_pointer_array_append_dword(unk_6FCCC8, v6);
    }
    v17 = v14;
    v20 = 0;
    rf_string_assign_from_object(v28, (int)v15);
    if ( v9 == 1 )
      v20 |= 1u;
    if ( v12 == 1 )
      v20 |= 2u;
    if ( v33 == 1 )
      v20 |= 4u;
    if ( v38 == 1 )
      v20 |= 8u;
    if ( v10 == 1 )
      v20 |= 0x80u;
    if ( v29 == 1 )
      v20 |= 0x20u;
    v27[1] = v37;
    v1 = (char *)rf_string_object_c_str_or_empty(v15);
    v28[2] = rf_item_definition_find_by_name(v1);
    v4 = rf_trigger_runtime_create((int)self);
    if ( v4 )
    {
      *(_DWORD *)(v4 + 32) = v35;
      for ( j = 0; j < v7; ++j )
      {
        v2 = (int *)sub_552200(unk_6FCCC8, j);
        rf_pointer_array_append_dword((_DWORD *)(v4 + 724), *v2);
      }
      if ( v30[0] )
        rf_trigger_set_reverse_disabled(v4);
    }
  }
  LOBYTE(v39) = 1;
  rf_rfl_trigger_destroy_strings((int)self);
  LOBYTE(v39) = 0;
  rf_string_destroy_buffer(v15);
  v39 = -1;
  rf_string_destroy_buffer(v34);
}

