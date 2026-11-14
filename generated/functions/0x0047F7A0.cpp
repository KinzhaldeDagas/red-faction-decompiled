// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047F7A0 rf_rfl_multiplayer_respawns_section_load
// UNREALRED VERIFIED [mission-visibility-20261020] This loader writes each respawn UID into shared scratch0x6FCCA8 through0x5A0D60. Shared legacy-entry reader4826F0 later uses its VALUE as the minimum-version argument to int32 reader59F9F0. Initial on-disk scratch is-1; do not assume it stays constant across sections/levels.
void __cdecl rf_rfl_multiplayer_respawns_section_load(int *a1)
{
  char *v1; // eax
  char v2; // [esp-18h] [ebp-74h]
  char v3; // [esp-Ch] [ebp-68h]
  char v4; // [esp-8h] [ebp-64h]
  char v5; // [esp-4h] [ebp-60h]
  int i; // [esp+4h] [ebp-58h]
  _DWORD v7[2]; // [esp+8h] [ebp-54h] BYREF
  char v8[4]; // [esp+10h] [ebp-4Ch] BYREF
  char v9[38]; // [esp+14h] [ebp-48h] BYREF
  char v10; // [esp+3Ah] [ebp-22h] BYREF
  char v11; // [esp+3Bh] [ebp-21h] BYREF
  _BYTE Buffer[15]; // [esp+3Ch] [ebp-20h] BYREF
  char v13; // [esp+4Bh] [ebp-11h] BYREF
  int v14; // [esp+4Ch] [ebp-10h] BYREF
  int v15; // [esp+58h] [ebp-4h]

  rf_vector3_default_construct_noop(Buffer);
  rf_matrix3_construct(v9);
  rf_string_construct_empty(v7);
  v15 = 0;
  rf_binary_stream_serialize_int32(a1, &v14, 0, 0);
  for ( i = 0; i < v14; ++i )
  {
    rf_binary_stream_serialize_int32(a1, &dword_6FCCA8, 0, 0);
    rf_binary_stream_serialize_vector3(a1, Buffer, 0, unk_1C8FBDC);
    rf_binary_stream_serialize_matrix3_vectors_201(a1, v9, 0, (int)unk_1C8FC18);
    rf_binary_stream_serialize_string_object(a1, (std::exception *)v7, 0, nullptr);
    if ( rf_vfile_get_slot_version(a1) < 67 )
      rf_binary_stream_serialize_string_object(a1, (std::exception *)unk_6FCCC0, 0, nullptr);
    rf_binary_stream_serialize_bool(a1, byte_6FCCA0, 0, 1);
    rf_binary_stream_serialize_int32(a1, (int *)v8, 0, 0);
    rf_binary_stream_serialize_bool(a1, &v11, 172, 1);
    rf_binary_stream_serialize_bool(a1, &v13, 172, 1);
    rf_binary_stream_serialize_bool(a1, &v10, 172, 1);
    v5 = v10;
    v4 = v13;
    v3 = v11;
    v2 = v8[0];
    v1 = (char *)rf_string_object_c_str_or_empty(v7);
    rf_respawn_append_record68(v1, v2, (int)Buffer, (int)v9, v3, v4, v5);
  }
  v15 = -1;
  rf_string_destroy_buffer(v7);
}

