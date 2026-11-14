// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00485B90 rf_material_tables_load
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl stack-owned memory parser and RFString temporaries. Opens materials.tbl (directory0x98967F,flags0); nonzero open result fatal material.cpp:266, repeated fatal-call loop if
// handler returns. Requires '#Materials', loops until case-insensitive '#End'. Each required '$name:' is a quoted RFString resolved through fixed executable ten-name table, NOT its
// row order. Unknown name silently aliases Default id0; duplicate rows overwrite previous fields and absent rows retain prior bytes. The property loop does not require exactly ten
// material declarations or reset all records before parsing.
// Each optional repeated '$bitmap prefix:' allocates12 bytes, constructs first RFString, assigns quoted prefix, stores low8 material id at+8, appends pointer to registry0x70046C in
// source order. No duplicate-prefix check or allocation-failure rejection after nullable ctor branch. Required ordered numeric tokens
// '$elasticity:','$friction:','$density:',misspelled '$bouyancy:','$traction:' write FLOAT record offsets0,4,8,12,16 at base0x6FFE98,stride28. No range/finite clamp. Required quoted
// '$debris bitmap:' with string length<=4 stores handle+20=-1,aux+24=0 (not only empty names). Longer names: final extension equals '.vbm' case-insensitively -> sequence loader
// writes aux frame count at+24, returns first handle at+20; FPS output is local/discarded. Otherwise single bitmap load(-1,1), handle+20,aux+24=1 even if handle load fails.
// After materials '#End', requires '#Material Hit Sounds', reads EXACTLY ten quoted column labels to local resolved-id map, then ten row labels each followed by ten signed
// decimal/hex counts. Stores signed count[row_id][column_id] at0x6FFD08+40*row_id+4*column_id (distinct from pair-vector base0x6FFFB0). Labels both map through same fixed name
// lookup; unknown/duplicate labels alias slots. No count nonnegative/cap validation or matrix symmetrization. Closes materials buffer before opening foley.tbl (fatal
// material.cpp:337, same retry-fatal behavior).
// Finds optional '#Custom Sound Sets' substring anywhere in foley (NULL stop token); if absent just closes file. If found requires section header, loops while '$name:' consumed.
// Allocates212-byte set, constructs it when nonnull, then reads quoted name into RFString+204 even if allocation path returned NULL. For each '+sound:' reads quoted material selector
// and signed variation count. Counts>4 trigger fatal material.cpp:360 and repeatedly reconstruct/retry error if fatal returns. Counts<=0 parse zero sound entries. Parses each direct
// sound into local4-handle array; effective parsed count resets0 for EVERY '+sound:' clause. Exact case-insensitive selector 'all' invokes all/default setter storing row0/count0 and
// byte+200=1; otherwise resolved material id (unknown->0) invokes row setter. Repeated clauses replace that row/count without clearing trailing old handles. Appends set only after
// all clauses, then requires '#End' for section. Does not clear existing registries before append, free previously loaded resource handles, reject duplicate sets, or roll back all
// prior rows on errors. Normal closes both parser buffers and destroys strings/parser; unwind handles current raw allocation and locals, not all earlier objects.
void **rf_material_tables_load()
{
  double number_with_optional_decimal_fraction; // st7
  double v1; // st7
  double v2; // st7
  double v3; // st7
  double v4; // st7
  char *v5; // eax
  char *last_dot_or_empty_literal; // eax
  char *v7; // eax
  int v8; // eax
  char *v9; // eax
  int v10; // eax
  void *v11; // eax
  int signed_decimal_or_hex_integer; // eax
  const char *v13; // eax
  int v14; // eax
  int *p_debris_bitmap_auxiliary; // [esp-8h] [ebp-1F4h]
  std::exception *v17; // [esp+4h] [ebp-1E8h]
  _DWORD *v18; // [esp+Ch] [ebp-1E0h]
  const void **v19; // [esp+14h] [ebp-1D8h]
  _DWORD *v20; // [esp+1Ch] [ebp-1D0h]
  _DWORD *string_empty; // [esp+20h] [ebp-1CCh]
  _BYTE v22[8]; // [esp+24h] [ebp-1C8h] BYREF
  _BYTE v23[8]; // [esp+2Ch] [ebp-1C0h] BYREF
  int v24; // [esp+34h] [ebp-1B8h] BYREF
  void *v25; // [esp+3Ch] [ebp-1B0h]
  _DWORD *v26; // [esp+40h] [ebp-1ACh]
  _DWORD *v27; // [esp+44h] [ebp-1A8h]
  _DWORD *v28; // [esp+48h] [ebp-1A4h]
  int v29; // [esp+4Ch] [ebp-1A0h]
  _DWORD *v30; // [esp+50h] [ebp-19Ch]
  _DWORD v31[4]; // [esp+54h] [ebp-198h] BYREF
  int v32; // [esp+64h] [ebp-188h]
  char destination[4]; // [esp+68h] [ebp-184h] BYREF
  unsigned int v34; // [esp+70h] [ebp-17Ch]
  int k; // [esp+74h] [ebp-178h]
  int v36; // [esp+78h] [ebp-174h] BYREF
  int v37[2]; // [esp+7Ch] [ebp-170h] BYREF
  _DWORD *v38; // [esp+84h] [ebp-168h]
  char name[8]; // [esp+88h] [ebp-164h] BYREF
  int j; // [esp+90h] [ebp-15Ch]
  int v41; // [esp+94h] [ebp-158h]
  int v42; // [esp+98h] [ebp-154h]
  int i; // [esp+9Ch] [ebp-150h]
  void *self[80]; // [esp+A0h] [ebp-14Ch] BYREF
  int v45; // [esp+1E8h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v45 = 0;
  rf_string_construct_empty(name);
  LOBYTE(v45) = 1;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "materials.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\level\\material.cpp",
      266,
      "Unable to open materials.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Materials");
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#End") )
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$name:");
    rf_text_parser_read_delimited_rfstring(self, name, 34, 34);
    v41 = rf_material_name_to_index(name);
    while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "$bitmap prefix:") )
    {
      rf_text_parser_read_delimited_rfstring(self, name, 34, 34);
      v27 = operator new(0xCu);
      LOBYTE(v45) = 2;
      if ( v27 )
        string_empty = rf_record_construct_first_string_empty(v27);
      else
        string_empty = nullptr;
      v28 = string_empty;
      LOBYTE(v45) = 1;
      v38 = string_empty;
      rf_string_assign_from_object(string_empty, (int)name);
      *((_BYTE *)v38 + 8) = v41;
      rf_pointer_array_append_dword(rf_material_bitmap_prefix_registry, (int)v38);
    }
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$elasticity:");
    number_with_optional_decimal_fraction = rf_text_parser_read_number_with_optional_decimal_fraction(self);
    rf_material_physics_records[v41].elasticity = number_with_optional_decimal_fraction;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$friction:");
    v1 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
    rf_material_physics_records[v41].friction = v1;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$density:");
    v2 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
    rf_material_physics_records[v41].density = v2;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$bouyancy:");
    v3 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
    rf_material_physics_records[v41].buoyancy = v3;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$traction:");
    v4 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
    rf_material_physics_records[v41].traction = v4;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$debris bitmap:");
    rf_text_parser_read_delimited_rfstring(self, name, 34, 34);
    if ( (int)rf_string_length_from_cstr((const char **)name) <= 4 )
    {
      rf_material_physics_records[v41].debris_bitmap_handle = -1;
      rf_material_physics_records[v41].debris_bitmap_auxiliary = 0;
    }
    else
    {
      v5 = (char *)rf_string_object_c_str_or_empty(name);
      last_dot_or_empty_literal = rf_path_find_last_dot_or_empty_literal(v5);
      rf_string_construct_from_cstr(v37, last_dot_or_empty_literal);
      LOBYTE(v45) = 3;
      if ( rf_string_equals_case_insensitive((int)v37, ".vbm") )
      {
        p_debris_bitmap_auxiliary = &rf_material_physics_records[v41].debris_bitmap_auxiliary;
        v7 = (char *)rf_string_object_c_str_or_empty(name);
        v8 = rf_bitmap_vbm_sequence_load(v7, p_debris_bitmap_auxiliary, &v36);
        rf_material_physics_records[v41].debris_bitmap_handle = v8;
      }
      else
      {
        v9 = (char *)rf_string_object_c_str_or_empty(name);
        v10 = rf_bitmap_load_with_optional_mipmap_generation(v9, (void *)0xFFFFFFFF, 1);
        rf_material_physics_records[v41].debris_bitmap_handle = v10;
        rf_material_physics_records[v41].debris_bitmap_auxiliary = 1;
      }
      LOBYTE(v45) = 1;
      rf_string_destroy_buffer(v37);
    }
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Material Hit Sounds");
  for ( i = 0; i < 10; ++i )
  {
    rf_text_parser_read_delimited_rfstring(self, name, 34, 34);
    v11 = (void *)rf_material_name_to_index(name);
    self[i + 70] = v11;
  }
  for ( i = 0; i < 10; ++i )
  {
    rf_text_parser_read_delimited_rfstring(self, name, 34, 34);
    v42 = rf_material_name_to_index(name);
    for ( j = 0; j < 10; ++j )
    {
      signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(self);
      rf_material_hit_sound_count_matrix[v42][(_DWORD)self[j + 70]] = signed_decimal_or_hex_integer;
    }
  }
  rf_memory_text_parser_close_buffer(self);
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "foley.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\level\\material.cpp",
      337,
      "Unable to open foley.tbl");
  if ( rf_text_parser_find_substring_before_optional_stop((char **)self, "#Custom Sound Sets", nullptr) )
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Custom Sound Sets");
    rf_string_construct_empty(destination);
    LOBYTE(v45) = 4;
    while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "$name:") )
    {
      v25 = operator new(0xD4u);
      LOBYTE(v45) = 5;
      if ( v25 )
        v20 = (_DWORD *)rf_material_custom_sound_set_construct((int)v25);
      else
        v20 = nullptr;
      v26 = v20;
      LOBYTE(v45) = 4;
      v30 = v20;
      rf_text_parser_read_delimited_rfstring(self, v20 + 51, 34, 34);
      v32 = 0;
      while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+sound:") )
      {
        v32 = 0;
        rf_text_parser_read_delimited_rfstring(self, destination, 34, 34);
        v29 = rf_text_parser_read_signed_decimal_or_hex_integer(self);
        if ( v29 > 4 )
        {
          v19 = (const void **)rf_string_format_int32_decimal(&v24, 4);
          LOBYTE(v45) = 6;
          v18 = rf_string_concat_cstr_object(
                  v23,
                  "Too many sound variations for sound set in materials.tbl!  No more than ",
                  v19);
          LOBYTE(v45) = 7;
          v17 = (std::exception *)rf_string_concat_object_cstr(v22, v18, "!");
          LOBYTE(v45) = 8;
          v13 = rf_string_object_c_str_or_empty(v17);
          rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\gamesrc\\level\\material.cpp", 360, v13);
        }
        for ( k = 0; k < v29; ++k )
        {
          v14 = rf_gamesound_parse_direct_sound(self);
          v31[v32++] = v14;
        }
        if ( rf_string_equals_case_insensitive((int)destination, (char *)off_6392BC) )
        {
          rf_material_custom_sound_set_assign_all((int)v30, (int)v31, v32);
        }
        else
        {
          v34 = rf_material_name_to_index(destination);
          rf_material_custom_sound_set_assign_row(v30, v34, (int)v31, v32);
        }
      }
      rf_pointer_array_append_dword(rf_material_custom_sound_sets, (int)v30);
    }
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#End");
    LOBYTE(v45) = 1;
    rf_string_destroy_buffer(destination);
  }
  rf_memory_text_parser_close_buffer(self);
  LOBYTE(v45) = 0;
  rf_string_destroy_buffer(name);
  v45 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

