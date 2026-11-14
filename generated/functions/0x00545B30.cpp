// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00545B30 rf_level_geometry_deserialize
// UNREALRED VERIFIED [mission-mover-geometry-20261013] Also deserializes each roomless moving solid called from 0x480D60, not just static world geometry. Version180 header is u16-length name, u32 flags, signed texture count and texture strings. Captured live solids have zero legacy texture-animation, room, room-link and room-pair counts. Vertices/faces/lightmap descriptors are real runtime solid data; face room index -1 is valid and keeps it outside world room-face registration. Face flags and smoothing groups are distinct full dwords. Preserve the per-corner lightmap-UV condition and version180 tail.
// UNREALRED VERIFIED [trigger-airlock-20261022] After serialized room visibility links, reads a count of 32-byte portal records: uint32 roomA index, uint32 roomB index, boundsMin float3, boundsMax float3. Constructs557C80 records in source order. These records are not padding and are distinct from visibility-room links. UnrealRed now retains them for room pressure and airlock adjacency.
// UNREALRED VERIFIED [combat-native-planes-20261104]: Geometry face wire layout is versioned. Version>=167 reads serialized normal XYZ plus float d before texture fields (546877..5468A1); finalization receives that four-float plane at546B30. Version<167 reads no plane fields and passes null at546B47 to derive one from ordered corners. Retaining just normal and recomputing d from first vertex loses authored plane data for modern RFL and misreads legacy face alignment.
// UNREALRED VERIFIED [combat-native-query-20261104]: Face corner input is a serialized global vertex index, resolved through the allocated vertex table before533A20 corner append. Coincident coordinates do not imply equal native vertex identity. Retained query/Boolean data must preserve source vertex indices, not weld source polygon Positions by coordinate. Global face order follows wire face order, while room attachment creates a separate per-room order.
char *__cdecl rf_level_geometry_deserialize(_DWORD *a1, char *a2)
{
  char v2; // al
  char v3; // al
  char v4; // al
  char v5; // al
  char v6; // al
  char v7; // al
  double float_versioned; // st7
  double v9; // st7
  _DWORD *packed4bytes_versioned; // eax
  int v11; // eax
  double v12; // st7
  int v13; // eax
  int v14; // eax
  char v15; // al
  int v16; // eax
  int v17; // eax
  double v18; // st7
  int v19; // eax
  double v20; // st7
  double v21; // st7
  _DWORD *v22; // eax
  float *v23; // eax
  char v24; // al
  int first_dword; // eax
  int v26; // eax
  int v27; // eax
  double v28; // st7
  double v29; // st7
  float *v31; // [esp+14h] [ebp-122Ch]
  int v32; // [esp+1Ch] [ebp-1224h]
  float *v33; // [esp+20h] [ebp-1220h]
  _BYTE *v34; // [esp+24h] [ebp-121Ch]
  float *v35; // [esp+28h] [ebp-1218h]
  void **v36; // [esp+2Ch] [ebp-1214h]
  void *v37; // [esp+30h] [ebp-1210h]
  void *v38; // [esp+34h] [ebp-120Ch]
  float copy_result[3]; // [esp+48h] [ebp-11F8h] BYREF
  _DWORD *v40; // [esp+54h] [ebp-11ECh]
  void *v41; // [esp+58h] [ebp-11E8h]
  float *v42; // [esp+5Ch] [ebp-11E4h]
  char v43[4]; // [esp+60h] [ebp-11E0h] BYREF
  char v44[4]; // [esp+64h] [ebp-11DCh] BYREF
  void *room; // [esp+68h] [ebp-11D8h]
  _BYTE *v46; // [esp+6Ch] [ebp-11D4h]
  void *v47; // [esp+70h] [ebp-11D0h]
  float *v48; // [esp+74h] [ebp-11CCh]
  void *v49; // [esp+78h] [ebp-11C8h]
  void **v50; // [esp+7Ch] [ebp-11C4h]
  float *v51; // [esp+80h] [ebp-11C0h]
  int v52; // [esp+84h] [ebp-11BCh]
  int *v53; // [esp+88h] [ebp-11B8h]
  float v54; // [esp+8Ch] [ebp-11B4h]
  float v55; // [esp+90h] [ebp-11B0h]
  float *m; // [esp+94h] [ebp-11ACh]
  float *source; // [esp+98h] [ebp-11A8h]
  float *v58; // [esp+9Ch] [ebp-11A4h]
  float v59; // [esp+A0h] [ebp-11A0h]
  int v60; // [esp+A4h] [ebp-119Ch]
  float v61; // [esp+A8h] [ebp-1198h]
  float v62; // [esp+ACh] [ebp-1194h]
  float v63; // [esp+B0h] [ebp-1190h]
  int k; // [esp+B4h] [ebp-118Ch]
  float *v65; // [esp+B8h] [ebp-1188h]
  float *link; // [esp+BCh] [ebp-1184h]
  int v67; // [esp+C0h] [ebp-1180h]
  int v68; // [esp+C4h] [ebp-117Ch]
  char v69; // [esp+CBh] [ebp-1175h]
  int v70; // [esp+CCh] [ebp-1174h]
  int v71; // [esp+D0h] [ebp-1170h]
  int v72; // [esp+D4h] [ebp-116Ch]
  int v73; // [esp+D8h] [ebp-1168h]
  float v74[3]; // [esp+DCh] [ebp-1164h] BYREF
  int v75; // [esp+E8h] [ebp-1158h]
  int v76; // [esp+ECh] [ebp-1154h]
  int v77; // [esp+F0h] [ebp-1150h]
  int v78; // [esp+F4h] [ebp-114Ch]
  float *v79; // [esp+F8h] [ebp-1148h]
  int v80; // [esp+FCh] [ebp-1144h]
  int v81; // [esp+100h] [ebp-1140h]
  int j; // [esp+104h] [ebp-113Ch]
  int v83; // [esp+108h] [ebp-1138h]
  int v84; // [esp+10Ch] [ebp-1134h]
  int v85; // [esp+110h] [ebp-1130h]
  char v86[1024]; // [esp+114h] [ebp-112Ch] BYREF
  char v87[4]; // [esp+514h] [ebp-D2Ch] BYREF
  _BYTE *v88; // [esp+518h] [ebp-D28h]
  char bool_versioned; // [esp+51Fh] [ebp-D21h]
  int v90; // [esp+520h] [ebp-D20h]
  char v91; // [esp+527h] [ebp-D19h]
  float bounds_max[3]; // [esp+528h] [ebp-D18h] BYREF
  float bounds_min[3]; // [esp+534h] [ebp-D0Ch] BYREF
  float v94[2]; // [esp+540h] [ebp-D00h] BYREF
  int v95; // [esp+548h] [ebp-CF8h]
  float v96[2]; // [esp+54Ch] [ebp-CF4h] BYREF
  int v97; // [esp+554h] [ebp-CECh]
  float v98[2]; // [esp+558h] [ebp-CE8h] BYREF
  float v99[2]; // [esp+560h] [ebp-CE0h] BYREF
  char v100[12]; // [esp+568h] [ebp-CD8h] BYREF
  int v101; // [esp+574h] [ebp-CCCh]
  float *v102; // [esp+578h] [ebp-CC8h]
  int int32_versioned; // [esp+57Ch] [ebp-CC4h]
  int v104; // [esp+580h] [ebp-CC0h]
  char v105[1028]; // [esp+584h] [ebp-CBCh] BYREF
  int v106; // [esp+988h] [ebp-8B8h]
  int v107; // [esp+98Ch] [ebp-8B4h]
  int v108; // [esp+990h] [ebp-8B0h]
  int v109; // [esp+994h] [ebp-8ACh]
  unsigned int v110[8]; // [esp+998h] [ebp-8A8h] BYREF
  int v111; // [esp+9B8h] [ebp-888h]
  char v112[1024]; // [esp+9BCh] [ebp-884h] BYREF
  int v113; // [esp+DBCh] [ebp-484h]
  int v114; // [esp+DC0h] [ebp-480h]
  int int16; // [esp+DC4h] [ebp-47Ch]
  int user_bitmap; // [esp+DC8h] [ebp-478h]
  char Destination[1028]; // [esp+DCCh] [ebp-474h] BYREF
  int v118; // [esp+11D4h] [ebp-6Ch]
  char v119[12]; // [esp+11D8h] [ebp-68h] BYREF
  int v120; // [esp+11E4h] [ebp-5Ch]
  int v121; // [esp+11E8h] [ebp-58h]
  float v122[4]; // [esp+11ECh] [ebp-54h] BYREF
  int int32; // [esp+11FCh] [ebp-44h]
  int v124; // [esp+1200h] [ebp-40h]
  int v125; // [esp+1204h] [ebp-3Ch]
  int v126; // [esp+1208h] [ebp-38h]
  int v127; // [esp+120Ch] [ebp-34h]
  void *solid; // [esp+1210h] [ebp-30h]
  int i; // [esp+1214h] [ebp-2Ch]
  _DWORD *v130; // [esp+1218h] [ebp-28h]
  unsigned int metadata[3]; // [esp+121Ch] [ebp-24h] BYREF
  __int16 v132; // [esp+1228h] [ebp-18h]
  __int16 v133; // [esp+122Ah] [ebp-16h]
  int v134; // [esp+122Ch] [ebp-14h]
  int v135; // [esp+1230h] [ebp-10h]
  int v136; // [esp+123Ch] [ebp-4h]

  v49 = operator new(0x378u);
  v136 = 0;
  if ( v49 )
    v36 = rf_solid888_construct((void **)v49);
  else
    v36 = nullptr;
  v50 = v36;
  v136 = -1;
  solid = v36;
  if ( rf_stream_adapter_get_cached_or_vfile_version(a1) < 200 )
  {
    rf_stream_adapter_read_u16_string_to_buffer(a1, (char *)solid + 4, 63, 0, nullptr);
    *((_DWORD *)solid + 17) = rf_stream_adapter_read_uint32_versioned(a1, 0, 0);
  }
  else
  {
    rf_stream_adapter_read_uint32_versioned(a1, 0, 0);
    *((_DWORD *)solid + 17) = rf_stream_adapter_read_uint32_versioned(a1, 0, 0);
    rf_stream_adapter_read_u16_string_to_buffer(a1, (char *)solid + 4, 63, 0, nullptr);
  }
  rf_dword_array_construct_capacity(v119, 0);
  v136 = 1;
  int32 = rf_stream_adapter_read_int32((void **)a1);
  if ( int32 <= -1 )
  {
    int32 = rf_stream_adapter_read_int32((void **)a1);
    if ( unk_1426C69 )
    {
      for ( i = 0; i < int32; ++i )
      {
        rf_stream_adapter_read_u16_string_to_buffer(a1, v112, -1, 0, nullptr);
        int16 = rf_stream_adapter_read_int16(a1);
        v114 = rf_stream_adapter_read_int16(a1);
        v111 = rf_stream_adapter_read_int16(a1);
        user_bitmap = rf_bitmap_create_user_bitmap(v111, int16, v114);
        rf_pointer_array_append_dword(v119, user_bitmap);
        v113 = rf_bitmap_format_bytes_per_pixel(v111);
        if ( rf_bitmap_lock_pixels_backend_dispatch(user_bitmap, 0, (int)v110, 1) )
        {
          rf_stream_adapter_read_bytes((int **)a1, (char *)v110[3], v113 * v114 * int16);
          rf_bitmap_unlock_pixels_backend_dispatch(v110);
        }
        else
        {
          rf_stream_adapter_seek(a1, v113 * v114 * int16, 1);
        }
      }
    }
    else
    {
      for ( i = 0; i < int32; ++i )
      {
        rf_stream_adapter_read_u16_string_to_buffer(a1, v105, -1, 0, nullptr);
        v108 = rf_bitmap_load_with_optional_mipmap_generation(v105, (void *)0xFFFFFFFF, 1);
        rf_pointer_array_append_dword(v119, v108);
        v109 = rf_stream_adapter_read_int16(a1);
        v107 = rf_stream_adapter_read_int16(a1);
        v104 = rf_stream_adapter_read_int16(a1);
        v106 = rf_bitmap_format_bytes_per_pixel(v104);
        rf_stream_adapter_seek(a1, v106 * v107 * v109, 1);
      }
    }
  }
  else
  {
    for ( i = 0; i < int32; ++i )
    {
      rf_stream_adapter_read_u16_string_to_buffer(a1, Destination, -1, 0, nullptr);
      v118 = rf_bitmap_load_with_optional_mipmap_generation(Destination, (void *)0xFFFFFFFF, 1);
      rf_pointer_array_append_dword(v119, v118);
    }
  }
  rf_progress_update_poll_network_and_callback(0, 0);
  if ( rf_stream_adapter_get_cached_or_vfile_version(a1) > 180 )
  {
    int32_versioned = rf_stream_adapter_read_int32_versioned(a1, 94, 0);
    for ( i = 0; i < int32_versioned; ++i )
    {
      v47 = operator new(0x18u);
      LOBYTE(v136) = 2;
      if ( v47 )
        v35 = (float *)rf_uv_scroll_descriptor_construct_invalid(v47);
      else
        v35 = nullptr;
      v48 = v35;
      LOBYTE(v136) = 1;
      v102 = v35;
      rf_pointer_array_append_dword((_DWORD *)solid + 189, (int)v35);
      *(_DWORD *)v35 = rf_stream_adapter_read_int32((void **)a1);
      v102[1] = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      v102[2] = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      rf_uv_scroll_descriptor_rebuild_face_cache(v102, (int)solid);
    }
  }
  if ( rf_stream_adapter_get_cached_or_vfile_version(a1) <= 180 )
  {
    rf_dword_array_construct_capacity(v100, 0);
    LOBYTE(v136) = 3;
    v101 = rf_stream_adapter_read_int32_versioned(a1, 66, 0);
    for ( i = 0; i < v101; ++i )
    {
      rf_vector3_default_construct_noop(v96);
      rf_vector3_default_construct_noop(v98);
      rf_vector3_default_construct_noop(v94);
      rf_vector3_default_construct_noop(v99);
      v95 = rf_stream_adapter_read_int32((void **)a1);
      v97 = rf_stream_adapter_read_int32((void **)a1);
      v96[0] = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      v96[1] = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      v98[0] = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      v98[1] = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      v94[0] = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      v94[1] = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      v99[0] = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      v99[1] = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      rf_stream_adapter_read_bool_versioned(a1, 0, 1);
      if ( v95 <= -1 || v97 <= -1 )
        rf_pointer_array_append_dword(v100, -1);
    }
    LOBYTE(v136) = 1;
    rf_pointer_array_destroy_backing_storage((void **)v100);
  }
  v126 = rf_stream_adapter_read_int32((void **)a1);
  for ( i = 0; i < v126; ++i )
  {
    rf_vector3_default_construct_noop(bounds_min);
    rf_vector3_default_construct_noop(bounds_max);
    v90 = rf_stream_adapter_read_int32_versioned(a1, 86, -1);
    rf_stream_adapter_read_vector3_versioned(a1, bounds_min, 0, unk_1C8FBDC);
    rf_stream_adapter_read_vector3_versioned(a1, bounds_max, 0, unk_1C8FBDC);
    room = operator new(0x1CCu);
    LOBYTE(v136) = 4;
    if ( room )
      v34 = rf_room460_construct_register(room, solid, bounds_min, bounds_max);
    else
      v34 = nullptr;
    v46 = v34;
    LOBYTE(v136) = 1;
    v88 = v34;
    if ( v90 != -1 )
      *((_DWORD *)v88 + 9) = v90;
    bool_versioned = rf_stream_adapter_read_bool_versioned(a1, 75, 0);
    rf_byte1_assign_ignoring_middle_argument(v88, (int)solid, bool_versioned);
    v2 = rf_stream_adapter_read_bool_versioned(a1, 101, 0);
    v88[65] = v2;
    v3 = rf_stream_adapter_read_bool_versioned(a1, 104, 0);
    v88[66] = v3;
    v4 = rf_stream_adapter_read_bool_versioned(a1, 104, 0);
    v88[67] = v4;
    v5 = rf_stream_adapter_read_bool_versioned(a1, 83, 0);
    v88[388] = v5;
    v6 = rf_stream_adapter_read_bool_versioned(a1, 120, 0);
    v88[69] = v6;
    v91 = rf_stream_adapter_read_bool_versioned(a1, 113, 0);
    sub_517BE0(v88, (int)solid, v91);
    v7 = rf_stream_adapter_read_bool_versioned(a1, 117, 0);
    v88[106] = v7;
    float_versioned = rf_stream_adapter_read_float_versioned(a1, 122, -1.0);
    *((float *)v88 + 37) = float_versioned;
    if ( *((float *)v88 + 37) > 0.0 )
      v88[152] = 0;
    rf_stream_adapter_read_u16_string_to_buffer(a1, v88 + 74, 32, 180, (char *)&byte_63FD07);
    if ( v88[388] )
    {
      v9 = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      *((float *)v88 + 98) = v9;
      packed4bytes_versioned = rf_stream_adapter_read_packed4bytes_versioned(a1, v44, 0, &dword_1C8FC4C);
      *((_DWORD *)v88 + 99) = *packed4bytes_versioned;
      rf_stream_adapter_read_u16_string_to_buffer(a1, v86, -1, 0, nullptr);
      v11 = rf_bitmap_load_with_optional_mipmap_generation(v86, (void *)0xFFFFFFFF, 1);
      *((_DWORD *)v88 + 101) = v11;
      v12 = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      *((float *)v88 + 100) = v12;
      v13 = rf_stream_adapter_read_int32_versioned(a1, 89, 1);
      *((_DWORD *)v88 + 96) = v13;
      v14 = rf_stream_adapter_read_int32_versioned(a1, 109, 60);
      *((_DWORD *)v88 + 106) = v14;
      v15 = rf_stream_adapter_read_bool_versioned(a1, 116, 1);
      v88[428] = v15;
      v16 = rf_stream_adapter_read_int32_versioned(a1, 116, 64);
      *((_DWORD *)v88 + 103) = v16;
      v17 = rf_stream_adapter_read_int32_versioned(a1, 116, 64);
      *((_DWORD *)v88 + 104) = v17;
      v18 = rf_stream_adapter_read_float_versioned(a1, 116, 180.0);
      *((float *)v88 + 105) = v18;
      v19 = rf_stream_adapter_read_int32_versioned(a1, 116, 0);
      *((_DWORD *)v88 + 108) = v19;
      v20 = rf_stream_adapter_read_float_versioned(a1, 129, 0.0);
      *((float *)v88 + 109) = v20;
      v21 = rf_stream_adapter_read_float_versioned(a1, 129, 0.0);
      *((float *)v88 + 110) = v21;
    }
    rf_rgba8_construct_components_return_self(v87, 100, 100, 100, 255);
    if ( v88[69] )
    {
      v22 = rf_stream_adapter_read_packed4bytes_versioned(a1, v43, 120, v87);
      *(_DWORD *)(v88 + 70) = *v22;
    }
  }
  rf_progress_update_poll_network_and_callback(0, 0);
  v124 = rf_stream_adapter_read_int32_versioned(a1, 113, 0);
  for ( i = 0; i < v124; ++i )
  {
    v85 = rf_stream_adapter_read_int32((void **)a1);
    v84 = *(_DWORD *)sub_552200((_DWORD *)solid + 36, v85);
    v83 = rf_stream_adapter_read_int32((void **)a1);
    for ( j = 0; j < v83; ++j )
    {
      v81 = rf_stream_adapter_read_int32((void **)a1);
      v80 = *(_DWORD *)sub_552200((_DWORD *)solid + 36, v81);
      rf_pointer_array_append_dword((_DWORD *)(v84 + 108), v80);
    }
  }
  v125 = rf_stream_adapter_read_int32((void **)a1);
  for ( i = 0; i < v125; ++i )
  {
    v75 = rf_stream_adapter_read_int32((void **)a1);
    v77 = rf_stream_adapter_read_int32((void **)a1);
    v78 = *(_DWORD *)sub_552200((_DWORD *)solid + 36, v75);
    v76 = *(_DWORD *)sub_552200((_DWORD *)solid + 36, v77);
    v41 = operator new(0x38u);
    LOBYTE(v136) = 5;
    if ( v41 )
      v33 = (float *)rf_runtime_portal_construct_register(v41, (int)solid, v78, v76);
    else
      v33 = nullptr;
    v42 = v33;
    LOBYTE(v136) = 1;
    v79 = v33;
    rf_stream_adapter_read_vector3_versioned(a1, v33 + 2, 0, unk_1C8FBDC);
    rf_stream_adapter_read_vector3_versioned(a1, v79 + 5, 0, unk_1C8FBDC);
  }
  v120 = rf_stream_adapter_read_int32((void **)a1);
  v40 = operator new(4 * v120);
  v130 = v40;
  rf_pointer_array_resize_count_unchecked((void **)solid + 30, (void *)v120);
  rf_pointer_array_clear_count_keep_storage((_DWORD *)solid + 30);
  for ( i = 0; i < v120; ++i )
  {
    rf_vector3_default_construct_noop(v74);
    rf_stream_adapter_read_vector3_versioned(a1, v74, 0, unk_1C8FBDC);
    v23 = rf_solid_vertex_copy_append(solid, v74);
    v130[i] = v23;
  }
  rf_progress_update_poll_network_and_callback(0, 0);
  v121 = rf_stream_adapter_read_int32((void **)a1);
  v127 = 0;
  rf_geomod_face_metadata_init(metadata);
  rf_float4_construct_components_after_vector_noop(v122, 0.0, 0.0, 0.0, 0.0);
  for ( i = 0; i < v121; ++i )
  {
    if ( rf_stream_adapter_get_cached_or_vfile_version(a1) >= 167 )
    {
      rf_stream_adapter_read_vector3_versioned(a1, v122, 0, unk_1C8FBDC);
      v122[3] = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
    }
    v71 = rf_stream_adapter_read_int32((void **)a1);
    if ( v71 <= -1 )
      v32 = rf_bitmap_load_with_optional_mipmap_generation("misc-static.tga", (void *)0xFFFFFFFF, 1);
    else
      v32 = *(_DWORD *)sub_552200(v119, v71);
    metadata[2] = v32;
    v70 = rf_stream_adapter_read_int32((void **)a1);
    v133 = v70;
    v67 = rf_stream_adapter_read_int32_versioned(a1, 49, -1);
    v134 = v67;
    v71 = rf_stream_adapter_read_int32_versioned(a1, 66, -1);
    v71 = rf_stream_adapter_read_int32_versioned(a1, 66, -1);
    v73 = rf_stream_adapter_read_int32_versioned(a1, 63, 0);
    v132 = v73;
    if ( rf_stream_adapter_get_cached_or_vfile_version(a1) >= 77 )
    {
      metadata[0] = rf_stream_adapter_read_uint32_versioned(a1, 0, 0);
    }
    else
    {
      metadata[0] = 0;
      v24 = rf_stream_adapter_read_bool_versioned(a1, 75, 0);
      rf_dword_flag_bit0_assign(metadata, v24);
    }
    v135 = rf_stream_adapter_read_int32_versioned(a1, 79, 0);
    v72 = rf_stream_adapter_read_int32((void **)a1);
    v65 = nullptr;
    if ( v72 <= -1 )
      ++v127;
    else
      v65 = *(float **)sub_552200((_DWORD *)solid + 36, v72);
    v68 = rf_stream_adapter_read_int32((void **)a1);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    for ( k = 0; k < v68; ++k )
    {
      v60 = rf_stream_adapter_read_int32((void **)a1);
      v61 = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      v63 = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      v59 = 0.0;
      v62 = 0.0;
      if ( *((__int16 *)link + 27) > -1 )
      {
        v59 = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
        v62 = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      }
      rf_geomod_face_corner_append(link, v130[v60], v61, v63, v59, v62);
    }
    if ( rf_stream_adapter_get_cached_or_vfile_version(a1) < 167 )
      v69 = rf_geomod_face_finalize_geometry((int)link, nullptr, 0);
    else
      v69 = rf_geomod_face_finalize_geometry((int)link, v122, 0);
    if ( v69 )
    {
      if ( v65 )
        rf_geomod_room_face_attach(v65, (int)link);
    }
    else
    {
      rf_solid_face_list_remove((int *)solid + 28, (int)link);
      rf_geomod_face_destroy(link);
      link = nullptr;
    }
  }
  rf_progress_update_poll_network_and_callback(0, 0);
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((char *)solid + 168);
    if ( i >= first_dword )
      break;
    v58 = *(float **)sub_552200((_DWORD *)solid + 42, i);
    if ( *((_BYTE *)v58 + 106) )
    {
      v55 = 0.0;
      source = nullptr;
      for ( m = (float *)rf_receiver_get_first_dword(v58 + 10); m; m = (float *)rf_face_next_room_link((int)m) )
      {
        v54 = rf_geomod_face_area(m);
        if ( v55 < (double)v54 )
        {
          v55 = v54;
          source = m;
        }
      }
      rf_vector_copy(v58 + 31, copy_result, source);
      v58[34] = source[3];
    }
    sub_517C60(v58, (int)solid);
  }
  operator delete(v130);
  if ( a2 )
  {
    if ( solid )
      rf_solid_destroy((char *)solid, 1);
    solid = a2;
  }
  rf_level_read_lightmap_descriptors((int)a1, (int)solid);
  rf_progress_update_poll_network_and_callback(0, 0);
  rf_solid_finalize_bounds((float *)solid);
  for ( i = 0; ; ++i )
  {
    v26 = rf_receiver_get_first_dword((char *)solid + 144);
    if ( i >= v26 )
      break;
    v53 = *(int **)sub_552200((_DWORD *)solid + 36, i);
    rf_room_face_spatial_tree_rebuild(v53);
  }
  if ( rf_stream_adapter_get_cached_or_vfile_version(a1) <= 180 )
  {
    v52 = rf_stream_adapter_read_int32_versioned(a1, 94, 0);
    for ( i = 0; i < v52; ++i )
    {
      v38 = operator new(0x18u);
      LOBYTE(v136) = 6;
      if ( v38 )
        v31 = (float *)rf_uv_scroll_descriptor_construct_invalid(v38);
      else
        v31 = nullptr;
      LOBYTE(v136) = 1;
      v51 = v31;
      rf_pointer_array_append_dword((_DWORD *)solid + 189, (int)v31);
      v27 = rf_stream_adapter_read_int32((void **)a1);
      *(_DWORD *)v51 = v27;
      v28 = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      v51[1] = v28;
      v29 = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
      v51[2] = v29;
      rf_uv_scroll_descriptor_rebuild_face_cache(v51, (int)solid);
    }
  }
  v37 = solid;
  v136 = -1;
  rf_pointer_array_destroy_backing_storage((void **)v119);
  return (char *)v37;
}

