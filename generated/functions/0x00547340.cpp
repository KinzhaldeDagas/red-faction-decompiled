// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00547340 rf_level_geometry_serialize
// Serializes level geometry, including each face's lightmap id at Face+0x36 separately from its signed portal marker at Face+0x34 and masked flags at Face+0x28.
// UNREALRED VERIFIED [sky-face-render-contract] Serializes each face's signed portal marker, full Face+0x28 flags masked by 0x2BFF, then the separate Face+0x3C smoothing-groups dword.
void __cdecl rf_level_geometry_serialize(_DWORD *stream, const char *a2, char a3)
{
  unsigned int *v3; // eax
  char *v4; // eax
  const char *v5; // eax
  unsigned int *v6; // eax
  char *source_record_name_pointer; // eax
  const char *v8; // eax
  int *v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  char is_authored_sky; // al
  char v14; // al
  const char *v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  float **v26; // eax
  int v27; // eax
  int v28; // eax
  int index; // eax
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // [esp+8h] [ebp-ACh]
  int v35; // [esp+1Ch] [ebp-98h]
  int n; // [esp+20h] [ebp-94h]
  int v37; // [esp+24h] [ebp-90h]
  int k; // [esp+2Ch] [ebp-88h]
  int v39; // [esp+30h] [ebp-84h]
  int v40; // [esp+34h] [ebp-80h]
  _BYTE v41[12]; // [esp+38h] [ebp-7Ch] BYREF
  _BYTE v42[12]; // [esp+44h] [ebp-70h] BYREF
  int v43; // [esp+50h] [ebp-64h]
  int v44; // [esp+54h] [ebp-60h]
  unsigned int v45[2]; // [esp+58h] [ebp-5Ch] BYREF
  int v46; // [esp+60h] [ebp-54h]
  void *Buffer; // [esp+64h] [ebp-50h]
  int v48; // [esp+68h] [ebp-4Ch]
  int v49; // [esp+6Ch] [ebp-48h]
  _DWORD v50[2]; // [esp+78h] [ebp-3Ch] BYREF
  _DWORD v51[2]; // [esp+80h] [ebp-34h] BYREF
  void *v52[3]; // [esp+88h] [ebp-2Ch] BYREF
  int m; // [esp+94h] [ebp-20h]
  int first_dword; // [esp+98h] [ebp-1Ch]
  float *i; // [esp+9Ch] [ebp-18h]
  int j; // [esp+A0h] [ebp-14h]
  int v57; // [esp+A4h] [ebp-10h]
  int v58; // [esp+B0h] [ebp-4h]

  rf_dword_array_construct_capacity(v52, 0);
  v58 = 0;
  for ( i = (float *)rf_receiver_get_first_dword((void *)(a2 + 112)); i; i = (float *)rf_solid_face_next_link((int)i) )
  {
    if ( *((int *)i + 12) > 0 )
      rf_pointer_array_append_unique(v52, *((_DWORD *)i + 12));
  }
  first_dword = rf_receiver_get_first_dword(v52);
  rf_binary_stream_write_uint32_host_order(0);
  rf_binary_stream_write_uint32_host_order(*((_DWORD *)a2 + 17));
  rf_binary_stream_write_u16_length_string(stream, a2 + 4, -1);
  if ( unk_1426C68 )
  {
    rf_binary_stream_write_int32_host_order(stream, -1);
    rf_binary_stream_write_int32_host_order(stream, first_dword);
    for ( j = 0; j < first_dword; ++j )
    {
      v6 = (unsigned int *)sub_552200(v52, j);
      source_record_name_pointer = (char *)rf_bitmap_get_source_record_name_pointer(*v6);
      rf_string_construct_from_cstr(v50, source_record_name_pointer);
      LOBYTE(v58) = 2;
      v8 = rf_string_object_c_str_or_empty(v50);
      rf_binary_stream_write_u16_length_string(stream, v8, -1);
      v9 = (int *)sub_552200(v52, j);
      if ( rf_bitmap_lock_pixels_backend_dispatch(*v9, 0, (int)v45, 1) )
      {
        v44 = rf_bitmap_format_bytes_per_pixel(v46);
        rf_binary_stream_write_int16_host_order(stream, v48);
        rf_binary_stream_write_int16_host_order(stream, v49);
        rf_binary_stream_write_int16_host_order(stream, v46);
        rf_vfile_write_bytes_with_optional_feedback(stream, Buffer, v44 * v49 * v48);
        rf_bitmap_unlock_pixels_backend_dispatch(v45);
      }
      else
      {
        rf_binary_stream_write_int16_host_order(stream, 0);
        rf_binary_stream_write_int16_host_order(stream, 0);
        rf_binary_stream_write_int16_host_order(stream, 0);
      }
      LOBYTE(v58) = 0;
      rf_string_destroy_buffer(v50);
    }
  }
  else
  {
    rf_binary_stream_write_int32_host_order(stream, first_dword);
    for ( j = 0; j < first_dword; ++j )
    {
      v3 = (unsigned int *)sub_552200(v52, j);
      v4 = (char *)rf_bitmap_get_source_record_name_pointer(*v3);
      rf_string_construct_from_cstr(v51, v4);
      LOBYTE(v58) = 1;
      v5 = rf_string_object_c_str_or_empty(v51);
      rf_binary_stream_write_u16_length_string(stream, v5, -1);
      LOBYTE(v58) = 0;
      rf_string_destroy_buffer(v51);
    }
  }
  v57 = rf_receiver_get_first_dword((void *)(a2 + 756));
  rf_binary_stream_write_int32_host_order(stream, v57);
  for ( j = 0; j < v57; ++j )
  {
    v43 = *(_DWORD *)sub_552200((_DWORD *)a2 + 189, j);
    rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)v43);
    rf_binary_stream_write_float32_host_order(*(float *)(v43 + 4));
    rf_binary_stream_write_float32_host_order(*(float *)(v43 + 8));
  }
  v10 = rf_receiver_get_first_dword((void *)(a2 + 144));
  rf_binary_stream_write_int32_host_order(stream, v10);
  for ( j = 0; ; ++j )
  {
    v11 = rf_receiver_get_first_dword((void *)(a2 + 144));
    if ( j >= v11 )
      break;
    rf_vector3_default_construct_noop(v42);
    rf_vector3_default_construct_noop(v41);
    v12 = sub_552200((_DWORD *)a2 + 36, j);
    v40 = *(_DWORD *)v12;
    rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(*(_DWORD *)v12 + 36));
    rf_binary_stream_write_vector3(stream, (float *)(v40 + 8));
    rf_binary_stream_write_vector3(stream, (float *)(v40 + 20));
    is_authored_sky = rf_room_is_authored_sky((_BYTE *)v40);
    rf_binary_stream_write_bool_equal_one(is_authored_sky);
    rf_binary_stream_write_bool_equal_one(*(_BYTE *)(v40 + 65));
    rf_binary_stream_write_bool_equal_one(*(_BYTE *)(v40 + 66));
    rf_binary_stream_write_bool_equal_one(*(_BYTE *)(v40 + 67));
    rf_binary_stream_write_bool_equal_one(*(_BYTE *)(v40 + 388));
    rf_binary_stream_write_bool_equal_one(*(_BYTE *)(v40 + 69));
    v14 = unknown_libname_11((void *)v40);
    rf_binary_stream_write_bool_equal_one(v14);
    rf_binary_stream_write_bool_equal_one(*(_BYTE *)(v40 + 106));
    rf_binary_stream_write_float32_host_order(*(float *)(v40 + 148));
    rf_binary_stream_write_u16_length_string(stream, (const char *)(v40 + 74), strlen((const char *)(v40 + 74)));
    if ( *(_BYTE *)(v40 + 388) )
    {
      rf_binary_stream_write_float32_host_order(*(float *)(v40 + 392));
      rf_binary_stream_write_packed4bytes((char *)(v40 + 396));
      v15 = (const char *)rf_bitmap_get_source_record_name_pointer(*(_DWORD *)(v40 + 404));
      rf_binary_stream_write_u16_length_string(stream, v15, -1);
      rf_binary_stream_write_float32_host_order(*(float *)(v40 + 400));
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(v40 + 384));
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(v40 + 424));
      rf_binary_stream_write_bool_equal_one(*(_BYTE *)(v40 + 428));
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(v40 + 412));
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(v40 + 416));
      rf_binary_stream_write_float32_host_order(*(float *)(v40 + 420));
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(v40 + 432));
      rf_binary_stream_write_float32_host_order(*(float *)(v40 + 436));
      rf_binary_stream_write_float32_host_order(*(float *)(v40 + 440));
    }
    if ( *(_BYTE *)(v40 + 69) )
      rf_binary_stream_write_packed4bytes((char *)(v40 + 70));
  }
  v16 = rf_receiver_get_first_dword((void *)(a2 + 144));
  rf_binary_stream_write_int32_host_order(stream, v16);
  for ( j = 0; ; ++j )
  {
    v17 = rf_receiver_get_first_dword((void *)(a2 + 144));
    if ( j >= v17 )
      break;
    v18 = sub_552200((_DWORD *)a2 + 36, j);
    v39 = *(_DWORD *)v18;
    rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(*(_DWORD *)v18 + 32));
    v19 = rf_receiver_get_first_dword((void *)(v39 + 108));
    rf_binary_stream_write_int32_host_order(stream, v19);
    for ( k = 0; k < rf_receiver_get_first_dword((void *)(v39 + 108)); ++k )
    {
      v20 = sub_552200((_DWORD *)(v39 + 108), k);
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(*(_DWORD *)v20 + 32));
    }
  }
  v21 = rf_receiver_get_first_dword((void *)(a2 + 180));
  rf_binary_stream_write_int32_host_order(stream, v21);
  for ( m = 0; ; ++m )
  {
    v22 = rf_receiver_get_first_dword((void *)(a2 + 180));
    if ( m >= v22 )
      break;
    v23 = sub_552200((_DWORD *)a2 + 45, m);
    v37 = *(_DWORD *)v23;
    rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(**(_DWORD **)v23 + 32));
    rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(*(_DWORD *)(v37 + 4) + 32));
    rf_binary_stream_write_vector3(stream, (float *)(v37 + 8));
    rf_binary_stream_write_vector3(stream, (float *)(v37 + 20));
  }
  v24 = rf_receiver_get_first_dword((void *)(a2 + 120));
  rf_binary_stream_write_int32_host_order(stream, v24);
  for ( j = 0; ; ++j )
  {
    v25 = rf_receiver_get_first_dword((void *)(a2 + 120));
    if ( j >= v25 )
      break;
    v26 = (float **)sub_552200((_DWORD *)a2 + 30, j);
    rf_binary_stream_write_vector3(stream, *v26);
    v27 = sub_552200((_DWORD *)a2 + 30, j);
    *(_DWORD *)(*(_DWORD *)v27 + 28) = j;
  }
  v28 = rf_shared_second_dword_getter_518050((_DWORD *)a2 + 28);
  rf_binary_stream_write_int32_host_order(stream, v28);
  for ( i = (float *)rf_receiver_get_first_dword((void *)(a2 + 112)); i; i = (float *)rf_solid_face_next_link((int)i) )
  {
    rf_binary_stream_write_vector3(stream, i);
    rf_binary_stream_write_float32_host_order(i[3]);
    if ( *((int *)i + 12) <= 0 )
    {
      rf_binary_stream_write_int32_host_order(stream, -1);
    }
    else
    {
      index = rf_pointer_array_find_index(v52, *((_DWORD *)i + 12));
      rf_binary_stream_write_int32_host_order(stream, index);
    }
    if ( a3 == 1 )
      rf_binary_stream_write_int32_host_order(stream, -1);
    else
      rf_binary_stream_write_int32_host_order(stream, *((__int16 *)i + 27));
    rf_binary_stream_write_int32_host_order(stream, *((_DWORD *)i + 14));
    rf_binary_stream_write_int32_host_order(stream, -1);
    rf_binary_stream_write_int32_host_order(stream, -1);
    rf_binary_stream_write_int32_host_order(stream, *((__int16 *)i + 26));
    rf_binary_stream_write_uint32_host_order((_DWORD)i[10] & 0x2BFF);
    rf_binary_stream_write_int32_host_order(stream, *((_DWORD *)i + 15));
    if ( *((_DWORD *)i + 17) )
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(*((_DWORD *)i + 17) + 32));
    else
      rf_binary_stream_write_int32_host_order(stream, -1);
    v30 = rf_geomod_face_corner_count(i);
    rf_binary_stream_write_int32_host_order(stream, v30);
    for ( n = *((_DWORD *)i + 16); n; n = v34 )
    {
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(*(_DWORD *)n + 28));
      rf_binary_stream_write_float32_host_order(*(float *)(n + 4));
      rf_binary_stream_write_float32_host_order(*(float *)(n + 8));
      if ( *((__int16 *)i + 27) > -1 && !a3 )
      {
        rf_binary_stream_write_float32_host_order(*(float *)(n + 12));
        rf_binary_stream_write_float32_host_order(*(float *)(n + 16));
      }
      if ( *(_DWORD *)(n + 20) == *((_DWORD *)i + 16) )
        v34 = 0;
      else
        v34 = *(_DWORD *)(n + 20);
    }
  }
  if ( a3 )
  {
    rf_binary_stream_write_int32_host_order(stream, 0);
  }
  else
  {
    v31 = rf_receiver_get_first_dword((void *)(a2 + 192));
    rf_binary_stream_write_int32_host_order(stream, v31);
    for ( j = 0; ; ++j )
    {
      v32 = rf_receiver_get_first_dword((void *)(a2 + 192));
      if ( j >= v32 )
        break;
      v33 = sub_552200((_DWORD *)a2 + 48, j);
      v35 = *(_DWORD *)v33;
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v33 + 12) + 20));
      rf_binary_stream_write_byte_host_order(*(_BYTE *)(v35 + 16));
      rf_binary_stream_write_byte_host_order(*(_BYTE *)(v35 + 20));
      rf_binary_stream_write_byte_host_order(*(_BYTE *)(v35 + 24));
      rf_binary_stream_write_byte_host_order(*(_BYTE *)(v35 + 28));
      rf_binary_stream_write_float32_host_order(*(float *)(v35 + 44));
      rf_binary_stream_write_float32_host_order(*(float *)(v35 + 48));
      rf_binary_stream_write_vector3(stream, (float *)(v35 + 52));
      rf_binary_stream_write_vector3(stream, (float *)(v35 + 64));
      rf_binary_stream_write_vector3(stream, (float *)(v35 + 108));
      rf_binary_stream_write_float32_host_order(*(float *)(v35 + 120));
      rf_binary_stream_write_int32_host_order(stream, *(unsigned __int8 *)(v35 + 9));
      rf_binary_stream_write_int32_host_order(stream, *(unsigned __int8 *)(v35 + 10));
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(v35 + 92));
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(v35 + 96));
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(v35 + 100));
      rf_binary_stream_write_float32_host_order(*(float *)(v35 + 84));
      rf_binary_stream_write_float32_host_order(*(float *)(v35 + 88));
      rf_binary_stream_write_float32_host_order(*(float *)(v35 + 76));
      rf_binary_stream_write_float32_host_order(*(float *)(v35 + 80));
      rf_binary_stream_write_int32_host_order(stream, *(_DWORD *)(v35 + 104));
    }
  }
  v58 = -1;
  rf_pointer_array_destroy_backing_storage(v52);
}

