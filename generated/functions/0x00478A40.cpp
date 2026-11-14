// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00478A40 rf_solid_report_texture_usage_statistics
// UNREALRED VERIFIED [level-lifecycle-20261028]: Traverses solid face list+112, records unique nonnegative bitmap handles, counts untextured faces. For textured polygons fans triangles from first corner and computes texel-space area using dimensions from0x576450, scaled UV edge lengths0x479780 and Heron formula; negative radicand clamped0. Accumulates texel area/1000 and physical face area/1000. For each unique texture sums width*height/1000; warns for either dimension>256 and for either dimension failing one-set-bit predicate0x4789F0, counting faces using each warned handle. Prints unique texture count, million texels, thousand square meters, mean texels/square-meter, its square root, and tiling factor used texels/unique texture texels. Zero denominators yield0. No world data edits; scratch pointer array and RF strings are destroyed. Decompiler x87 return artifacts around edge helper
// obscure the true floating results.
void __cdecl rf_solid_report_texture_usage_statistics(int a1)
{
  double v1; // st7
  double v2; // st7
  double v3; // st7
  double v4; // st7
  double v5; // st7
  const char *v6; // eax
  int first_dword; // eax
  unsigned int *v8; // eax
  _DWORD *v9; // eax
  unsigned int *v10; // eax
  const char *v11; // eax
  _DWORD *v12; // eax
  unsigned int *v13; // eax
  const char *v14; // eax
  int v15; // eax
  const char *v16; // eax
  const char *v17; // eax
  const char *v18; // eax
  const char *v19; // eax
  const char *v20; // eax
  const char *v21; // eax
  const char *v22; // [esp-4h] [ebp-2ACh]
  const char *v23; // [esp-4h] [ebp-2ACh]
  float v24; // [esp+0h] [ebp-2A8h]
  std::exception *v25; // [esp+14h] [ebp-294h]
  _DWORD *v26; // [esp+1Ch] [ebp-28Ch]
  const void **v27; // [esp+24h] [ebp-284h]
  std::exception *v28; // [esp+2Ch] [ebp-27Ch]
  _DWORD *v29; // [esp+34h] [ebp-274h]
  const void **v30; // [esp+3Ch] [ebp-26Ch]
  std::exception *v31; // [esp+44h] [ebp-264h]
  _DWORD *v32; // [esp+4Ch] [ebp-25Ch]
  const void **v33; // [esp+54h] [ebp-254h]
  std::exception *v34; // [esp+5Ch] [ebp-24Ch]
  _DWORD *v35; // [esp+64h] [ebp-244h]
  const void **v36; // [esp+6Ch] [ebp-23Ch]
  std::exception *v37; // [esp+74h] [ebp-234h]
  _DWORD *v38; // [esp+7Ch] [ebp-22Ch]
  const void **v39; // [esp+84h] [ebp-224h]
  float v40; // [esp+8Ch] [ebp-21Ch]
  std::exception *v41; // [esp+90h] [ebp-218h]
  _DWORD *v42; // [esp+98h] [ebp-210h]
  const void **v43; // [esp+A0h] [ebp-208h]
  std::exception *v44; // [esp+A8h] [ebp-200h]
  _DWORD *v45; // [esp+B0h] [ebp-1F8h]
  int *v46; // [esp+B8h] [ebp-1F0h]
  _DWORD *v47; // [esp+C0h] [ebp-1E8h]
  _DWORD *v48; // [esp+C8h] [ebp-1E0h]
  _DWORD *v49; // [esp+D0h] [ebp-1D8h]
  std::exception *v50; // [esp+D8h] [ebp-1D0h]
  _DWORD *v51; // [esp+E0h] [ebp-1C8h]
  int *v52; // [esp+E8h] [ebp-1C0h]
  _DWORD *v53; // [esp+F0h] [ebp-1B8h]
  _DWORD *v54; // [esp+F8h] [ebp-1B0h]
  _DWORD *v55; // [esp+100h] [ebp-1A8h]
  std::exception *v56; // [esp+108h] [ebp-1A0h]
  _DWORD *v57; // [esp+110h] [ebp-198h]
  const void **v58; // [esp+118h] [ebp-190h]
  int v59; // [esp+120h] [ebp-188h]
  int v60; // [esp+124h] [ebp-184h]
  int v61; // [esp+128h] [ebp-180h]
  _BYTE v62[8]; // [esp+12Ch] [ebp-17Ch] BYREF
  _BYTE v63[8]; // [esp+134h] [ebp-174h] BYREF
  int v64[2]; // [esp+13Ch] [ebp-16Ch] BYREF
  _BYTE v65[8]; // [esp+144h] [ebp-164h] BYREF
  _BYTE v66[8]; // [esp+14Ch] [ebp-15Ch] BYREF
  int v67[2]; // [esp+154h] [ebp-154h] BYREF
  _BYTE v68[8]; // [esp+15Ch] [ebp-14Ch] BYREF
  _BYTE v69[8]; // [esp+164h] [ebp-144h] BYREF
  int v70[2]; // [esp+16Ch] [ebp-13Ch] BYREF
  _BYTE v71[8]; // [esp+174h] [ebp-134h] BYREF
  _BYTE v72[8]; // [esp+17Ch] [ebp-12Ch] BYREF
  int v73[2]; // [esp+184h] [ebp-124h] BYREF
  _BYTE v74[8]; // [esp+18Ch] [ebp-11Ch] BYREF
  _BYTE v75[8]; // [esp+194h] [ebp-114h] BYREF
  int v76[2]; // [esp+19Ch] [ebp-10Ch] BYREF
  _BYTE v77[8]; // [esp+1A4h] [ebp-104h] BYREF
  _BYTE v78[8]; // [esp+1ACh] [ebp-FCh] BYREF
  _DWORD v79[2]; // [esp+1B4h] [ebp-F4h] BYREF
  _BYTE v80[8]; // [esp+1BCh] [ebp-ECh] BYREF
  _BYTE v81[8]; // [esp+1C4h] [ebp-E4h] BYREF
  _BYTE v82[8]; // [esp+1CCh] [ebp-DCh] BYREF
  _BYTE v83[8]; // [esp+1D4h] [ebp-D4h] BYREF
  _DWORD v84[2]; // [esp+1DCh] [ebp-CCh] BYREF
  _DWORD v85[2]; // [esp+1E4h] [ebp-C4h] BYREF
  _BYTE v86[8]; // [esp+1ECh] [ebp-BCh] BYREF
  _BYTE v87[8]; // [esp+1F4h] [ebp-B4h] BYREF
  _BYTE v88[8]; // [esp+1FCh] [ebp-ACh] BYREF
  _BYTE v89[8]; // [esp+204h] [ebp-A4h] BYREF
  _DWORD v90[2]; // [esp+20Ch] [ebp-9Ch] BYREF
  _DWORD v91[2]; // [esp+214h] [ebp-94h] BYREF
  _BYTE v92[8]; // [esp+21Ch] [ebp-8Ch] BYREF
  _BYTE v93[8]; // [esp+224h] [ebp-84h] BYREF
  _DWORD v94[2]; // [esp+22Ch] [ebp-7Ch] BYREF
  int v95; // [esp+234h] [ebp-74h]
  int v96; // [esp+238h] [ebp-70h]
  int source_record_name_pointer; // [esp+23Ch] [ebp-6Ch]
  int v98; // [esp+240h] [ebp-68h]
  int v99; // [esp+244h] [ebp-64h] BYREF
  int v100; // [esp+248h] [ebp-60h] BYREF
  float v101; // [esp+24Ch] [ebp-5Ch]
  float v102; // [esp+250h] [ebp-58h]
  float v103; // [esp+254h] [ebp-54h]
  float v104; // [esp+258h] [ebp-50h]
  float v105; // [esp+25Ch] [ebp-4Ch]
  int j; // [esp+260h] [ebp-48h]
  int v107; // [esp+264h] [ebp-44h] BYREF
  int v108; // [esp+268h] [ebp-40h] BYREF
  int v109; // [esp+26Ch] [ebp-3Ch]
  float v110; // [esp+270h] [ebp-38h]
  float v111; // [esp+274h] [ebp-34h]
  float v112; // [esp+278h] [ebp-30h]
  float v113; // [esp+27Ch] [ebp-2Ch]
  int v114; // [esp+280h] [ebp-28h]
  float v115; // [esp+284h] [ebp-24h]
  _DWORD *i; // [esp+288h] [ebp-20h]
  void *v117[3]; // [esp+28Ch] [ebp-1Ch] BYREF
  int k; // [esp+298h] [ebp-10h]
  int v119; // [esp+2A4h] [ebp-4h]

  v114 = 0;
  rf_dword_array_construct_capacity(v117, 0);
  v119 = 0;
  v115 = 0.0;
  v113 = 0.0;
  for ( i = (_DWORD *)rf_receiver_get_first_dword((void *)(a1 + 112)); i; i = (_DWORD *)rf_solid_face_next_link((int)i) )
  {
    if ( (int)i[12] >= 0 )
    {
      rf_pointer_array_append_unique(v117, i[12]);
      rf_bitmap_get_resolved_dimensions(i[12], &v108, &v107);
      v109 = i[16];
      if ( *(_DWORD *)(v109 + 20) == i[16] )
        v61 = 0;
      else
        v61 = *(_DWORD *)(v109 + 20);
      j = v61;
      if ( *(_DWORD *)(v61 + 20) == i[16] )
        v60 = 0;
      else
        v60 = *(_DWORD *)(j + 20);
      for ( j = v60; j; j = v59 )
      {
        v1 = *(float *)(v109 + 4);
        rf_texture_scaled_uv_edge_length(
          v108,
          v107,
          *(float *)(v109 + 4),
          *(float *)(v109 + 8),
          *(float *)(*(_DWORD *)(j + 24) + 4),
          *(float *)(*(_DWORD *)(j + 24) + 8));
        v105 = v1;
        v2 = *(float *)(v109 + 4);
        rf_texture_scaled_uv_edge_length(
          v108,
          v107,
          *(float *)(v109 + 4),
          *(float *)(v109 + 8),
          *(float *)(j + 4),
          *(float *)(j + 8));
        v103 = v2;
        v3 = *(float *)(j + 4);
        rf_texture_scaled_uv_edge_length(
          v108,
          v107,
          *(float *)(j + 4),
          *(float *)(j + 8),
          *(float *)(*(_DWORD *)(j + 24) + 4),
          *(float *)(*(_DWORD *)(j + 24) + 8));
        v101 = v3;
        v104 = (v105 + v103 + v101) / 2.0;
        v102 = (v104 - v105) * v104 * (v104 - v103) * (v104 - v101);
        if ( v102 < 0.0 )
          v102 = 0.0;
        v4 = rf_sqrt_float(v102);
        v115 = v4 / 1000.0 + v115;
        if ( *(_DWORD *)(j + 20) == i[16] )
          v59 = 0;
        else
          v59 = *(_DWORD *)(j + 20);
      }
      v5 = rf_geomod_face_area(i);
      v113 = v5 / 1000.0 + v113;
    }
    else
    {
      ++v114;
    }
  }
  if ( v114 > 0 )
  {
    v58 = (const void **)rf_string_format_int32_decimal(v94, v114);
    LOBYTE(v119) = 1;
    v57 = rf_string_concat_cstr_object(v93, "Warning: ", v58);
    LOBYTE(v119) = 2;
    v56 = (std::exception *)rf_string_concat_object_cstr(v92, v57, " faces aren't textured.\n");
    LOBYTE(v119) = 3;
    v6 = rf_string_object_c_str_or_empty(v56);
    rf_console_output_append_text_lines(v6, nullptr);
    LOBYTE(v119) = 2;
    rf_string_destroy_buffer(v92);
    LOBYTE(v119) = 1;
    rf_string_destroy_buffer(v93);
    LOBYTE(v119) = 0;
    rf_string_destroy_buffer(v94);
  }
  v112 = 0.0;
  if ( v113 > 0.0 )
    v112 = v115 / v113;
  v110 = 0.0;
  for ( k = 0; ; ++k )
  {
    first_dword = rf_receiver_get_first_dword(v117);
    if ( k >= first_dword )
      break;
    v8 = (unsigned int *)sub_552200(v117, k);
    rf_bitmap_get_resolved_dimensions(*v8, &v100, &v99);
    v110 = (double)v100 * (double)v99 / 1000.0 + v110;
    if ( v100 > 256 || v99 > 256 )
    {
      v98 = 0;
      for ( i = (_DWORD *)rf_receiver_get_first_dword((void *)(a1 + 112)); i; i = (_DWORD *)rf_solid_face_next_link((int)i) )
      {
        v9 = (_DWORD *)sub_552200(v117, k);
        if ( i[12] == *v9 )
          ++v98;
      }
      v10 = (unsigned int *)sub_552200(v117, k);
      source_record_name_pointer = rf_bitmap_get_source_record_name_pointer(*v10);
      v55 = rf_string_format_int32_decimal(v91, v98);
      LOBYTE(v119) = 4;
      v22 = (const char *)source_record_name_pointer;
      v54 = rf_string_construct_from_cstr(v90, "Warning: ");
      LOBYTE(v119) = 5;
      v53 = rf_string_concat_object_cstr(v89, v54, v22);
      LOBYTE(v119) = 6;
      v52 = (int *)rf_string_concat_object_cstr(v88, v53, " is larger than 256x256 and used ");
      LOBYTE(v119) = 7;
      v51 = rf_string_concat_two_objects(v87, v52, (int)v55);
      LOBYTE(v119) = 8;
      v50 = (std::exception *)rf_string_concat_object_cstr(v86, v51, " times.\n");
      LOBYTE(v119) = 9;
      v11 = rf_string_object_c_str_or_empty(v50);
      rf_console_output_append_text_lines(v11, nullptr);
      LOBYTE(v119) = 8;
      rf_string_destroy_buffer(v86);
      LOBYTE(v119) = 7;
      rf_string_destroy_buffer(v87);
      LOBYTE(v119) = 6;
      rf_string_destroy_buffer(v88);
      LOBYTE(v119) = 5;
      rf_string_destroy_buffer(v89);
      LOBYTE(v119) = 4;
      rf_string_destroy_buffer(v90);
      LOBYTE(v119) = 0;
      rf_string_destroy_buffer(v91);
    }
    if ( !rf_u32_has_exactly_one_set_bit(v100) || !rf_u32_has_exactly_one_set_bit(v99) )
    {
      v96 = 0;
      for ( i = (_DWORD *)rf_receiver_get_first_dword((void *)(a1 + 112)); i; i = (_DWORD *)rf_solid_face_next_link((int)i) )
      {
        v12 = (_DWORD *)sub_552200(v117, k);
        if ( i[12] == *v12 )
          ++v96;
      }
      v13 = (unsigned int *)sub_552200(v117, k);
      v95 = rf_bitmap_get_source_record_name_pointer(*v13);
      v49 = rf_string_format_int32_decimal(v85, v96);
      LOBYTE(v119) = 10;
      v23 = (const char *)v95;
      v48 = rf_string_construct_from_cstr(v84, "Warning: ");
      LOBYTE(v119) = 11;
      v47 = rf_string_concat_object_cstr(v83, v48, v23);
      LOBYTE(v119) = 12;
      v46 = (int *)rf_string_concat_object_cstr(v82, v47, " isn't a power of two and is used ");
      LOBYTE(v119) = 13;
      v45 = rf_string_concat_two_objects(v81, v46, (int)v49);
      LOBYTE(v119) = 14;
      v44 = (std::exception *)rf_string_concat_object_cstr(v80, v45, " times.\n");
      LOBYTE(v119) = 15;
      v14 = rf_string_object_c_str_or_empty(v44);
      rf_console_output_append_text_lines(v14, nullptr);
      LOBYTE(v119) = 14;
      rf_string_destroy_buffer(v80);
      LOBYTE(v119) = 13;
      rf_string_destroy_buffer(v81);
      LOBYTE(v119) = 12;
      rf_string_destroy_buffer(v82);
      LOBYTE(v119) = 11;
      rf_string_destroy_buffer(v83);
      LOBYTE(v119) = 10;
      rf_string_destroy_buffer(v84);
      LOBYTE(v119) = 0;
      rf_string_destroy_buffer(v85);
    }
  }
  v111 = 0.0;
  if ( v110 > 0.0 )
    v111 = v115 / v110;
  v15 = rf_receiver_get_first_dword(v117);
  v43 = (const void **)rf_string_format_int32_decimal(v79, v15);
  LOBYTE(v119) = 16;
  v42 = rf_string_concat_cstr_object(v78, "Info: ", v43);
  LOBYTE(v119) = 17;
  v41 = (std::exception *)rf_string_concat_object_cstr(v77, v42, " textures used.\n");
  LOBYTE(v119) = 18;
  v16 = rf_string_object_c_str_or_empty(v41);
  rf_console_output_append_text_lines(v16, nullptr);
  LOBYTE(v119) = 17;
  rf_string_destroy_buffer(v77);
  LOBYTE(v119) = 16;
  rf_string_destroy_buffer(v78);
  LOBYTE(v119) = 0;
  rf_string_destroy_buffer(v79);
  v40 = v115 / 1000.0;
  v39 = (const void **)rf_string_format_float_fixed_precision(v76, v40, 3);
  LOBYTE(v119) = 19;
  v38 = rf_string_concat_cstr_object(v75, "  Level used ", v39);
  LOBYTE(v119) = 20;
  v37 = (std::exception *)rf_string_concat_object_cstr(v74, v38, " million texels.\n");
  LOBYTE(v119) = 21;
  v17 = rf_string_object_c_str_or_empty(v37);
  rf_console_output_append_text_lines(v17, nullptr);
  LOBYTE(v119) = 20;
  rf_string_destroy_buffer(v74);
  LOBYTE(v119) = 19;
  rf_string_destroy_buffer(v75);
  LOBYTE(v119) = 0;
  rf_string_destroy_buffer(v76);
  v36 = (const void **)rf_string_format_float_fixed_precision(v73, v113, 3);
  LOBYTE(v119) = 22;
  v35 = rf_string_concat_cstr_object(v72, "  Level's surface area is ", v36);
  LOBYTE(v119) = 23;
  v34 = (std::exception *)rf_string_concat_object_cstr(v71, v35, " thousand square meters\n");
  LOBYTE(v119) = 24;
  v18 = rf_string_object_c_str_or_empty(v34);
  rf_console_output_append_text_lines(v18, nullptr);
  LOBYTE(v119) = 23;
  rf_string_destroy_buffer(v71);
  LOBYTE(v119) = 22;
  rf_string_destroy_buffer(v72);
  LOBYTE(v119) = 0;
  rf_string_destroy_buffer(v73);
  v33 = (const void **)rf_string_format_float_fixed_precision(v70, v112, 2);
  LOBYTE(v119) = 25;
  v32 = rf_string_concat_cstr_object(v69, "  Average texels per square meter: ", v33);
  LOBYTE(v119) = 26;
  v31 = (std::exception *)rf_string_concat_object_cstr(v68, v32, "\n");
  LOBYTE(v119) = 27;
  v19 = rf_string_object_c_str_or_empty(v31);
  rf_console_output_append_text_lines(v19, nullptr);
  LOBYTE(v119) = 26;
  rf_string_destroy_buffer(v68);
  LOBYTE(v119) = 25;
  rf_string_destroy_buffer(v69);
  LOBYTE(v119) = 0;
  rf_string_destroy_buffer(v70);
  v24 = rf_sqrt_float(v112);
  v30 = (const void **)rf_string_format_float_fixed_precision(v67, v24, 2);
  LOBYTE(v119) = 28;
  v29 = rf_string_concat_cstr_object(v66, "  Average texels per meter: ", v30);
  LOBYTE(v119) = 29;
  v28 = (std::exception *)rf_string_concat_object_cstr(v65, v29, "\n");
  LOBYTE(v119) = 30;
  v20 = rf_string_object_c_str_or_empty(v28);
  rf_console_output_append_text_lines(v20, nullptr);
  LOBYTE(v119) = 29;
  rf_string_destroy_buffer(v65);
  LOBYTE(v119) = 28;
  rf_string_destroy_buffer(v66);
  LOBYTE(v119) = 0;
  rf_string_destroy_buffer(v67);
  v27 = (const void **)rf_string_format_float_fixed_precision(v64, v111, 1);
  LOBYTE(v119) = 31;
  v26 = rf_string_concat_cstr_object(v63, "  Each texel is used approximately ", v27);
  LOBYTE(v119) = 32;
  v25 = (std::exception *)rf_string_concat_object_cstr(v62, v26, " times. (Tiling factor)\n");
  LOBYTE(v119) = 33;
  v21 = rf_string_object_c_str_or_empty(v25);
  rf_console_output_append_text_lines(v21, nullptr);
  LOBYTE(v119) = 32;
  rf_string_destroy_buffer(v62);
  LOBYTE(v119) = 31;
  rf_string_destroy_buffer(v63);
  LOBYTE(v119) = 0;
  rf_string_destroy_buffer(v64);
  v119 = -1;
  rf_pointer_array_destroy_backing_storage(v117);
}

