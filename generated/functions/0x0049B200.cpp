// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049B200 sub_49B200
// UNREALRED VERIFIED [lan-killfeed-20261028] #Characters producer stores $EntityType: resolved through0x431680 at pc_multi character record+4, and $EntityAnimType: similarly at+8; stride0x140, base0x77D760. Suicide pronoun helper0x49BBF0 uses the latter field to identify multi_female.
BOOL __cdecl sub_49B200(void *parser)
{
  BOOL result; // eax
  const char *v2; // eax
  unsigned int v3; // eax
  char *v4; // eax
  char *v5; // eax
  const char *v6; // [esp-4h] [ebp-5D0h]
  void *v7; // [esp+8h] [ebp-5C4h]
  void *v8; // [esp+10h] [ebp-5BCh]
  void *v9; // [esp+18h] [ebp-5B4h]
  void *v10; // [esp+20h] [ebp-5ACh]
  void *v11; // [esp+28h] [ebp-5A4h]
  void *v12; // [esp+30h] [ebp-59Ch]
  _BYTE v13[8]; // [esp+38h] [ebp-594h] BYREF
  _BYTE v14[8]; // [esp+40h] [ebp-58Ch] BYREF
  _BYTE v15[8]; // [esp+48h] [ebp-584h] BYREF
  _BYTE v16[8]; // [esp+50h] [ebp-57Ch] BYREF
  _BYTE v17[8]; // [esp+58h] [ebp-574h] BYREF
  _BYTE v18[8]; // [esp+60h] [ebp-56Ch] BYREF
  int type_by_name; // [esp+68h] [ebp-564h]
  int v20; // [esp+6Ch] [ebp-560h]
  const char *v21[2]; // [esp+70h] [ebp-55Ch] BYREF
  int v22[2]; // [esp+78h] [ebp-554h] BYREF
  _DWORD v23[2]; // [esp+80h] [ebp-54Ch] BYREF
  int self[70]; // [esp+88h] [ebp-544h] BYREF
  _DWORD v25[2]; // [esp+1A0h] [ebp-42Ch] BYREF
  char *v26; // [esp+1A8h] [ebp-424h]
  int i; // [esp+1ACh] [ebp-420h]
  int v28; // [esp+1B0h] [ebp-41Ch]
  int j; // [esp+1B4h] [ebp-418h]
  char String1[1028]; // [esp+1B8h] [ebp-414h] BYREF
  int v31; // [esp+5C8h] [ebp-4h]

  rf_multiplayer_character_count = 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "#Characters");
  while ( 1 )
  {
    result = rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "#End");
    if ( result )
      return result;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Name:");
    rf_text_parser_read_delimited_cstring(
      (int)parser,
      (char *)&unk_77D76C + 320 * rf_multiplayer_character_count,
      30,
      34,
      34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$ScreenName:");
    rf_text_parser_find_before_stop_and_consume_required((char **)parser, "En:", nullptr);
    rf_text_parser_read_delimited_cstring((int)parser, String1, 1024, 34, 34);
    unk_77D78C[80 * rf_multiplayer_character_count] = (int)rf_localization_copy_escaped_string_without_index(String1);
    rf_text_parser_find_before_stop_and_consume_required((char **)parser, "Gr:", nullptr);
    rf_text_parser_read_delimited_cstring((int)parser, String1, 1024, 34, 34);
    rf_text_parser_find_before_stop_and_consume_required((char **)parser, "Fr:", nullptr);
    rf_text_parser_read_delimited_cstring((int)parser, String1, 1024, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$ImageName:");
    rf_text_parser_read_delimited_cstring((int)parser, String1, 1024, 34, 34);
    rf_multiplayer_character_table[80 * rf_multiplayer_character_count] = rf_bitmap_load_with_optional_mipmap_generation(
                                                                            String1,
                                                                            (void *)0xFFFFFFFF,
                                                                            1);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$EntityType:");
    rf_text_parser_read_delimited_cstring((int)parser, String1, 1024, 34, 34);
    unk_77D764[80 * rf_multiplayer_character_count] = sub_431680(String1);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$EntityAnimType:");
    rf_text_parser_read_delimited_cstring((int)parser, String1, 1024, 34, 34);
    unk_77D768[80 * rf_multiplayer_character_count] = sub_431680(String1);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$SkinName:");
    rf_text_parser_read_delimited_cstring(
      (int)parser,
      (char *)&unk_77D790 + 320 * rf_multiplayer_character_count,
      16,
      34,
      34);
    if ( unk_77D764[80 * rf_multiplayer_character_count] > -1 )
    {
      v26 = &rf_entity_info_definitions[5396 * unk_77D764[80 * rf_multiplayer_character_count]];
      v28 = -1;
      for ( i = 0; i < *((_DWORD *)v26 + 991); ++i )
      {
        v6 = (char *)&unk_77D790 + 320 * rf_multiplayer_character_count;
        v2 = rf_string_object_c_str_or_empty(&v26[108 * i + 3968]);
        if ( !_stricmp(v2, v6) )
        {
          v28 = i;
          break;
        }
      }
      if ( v28 != -1 )
      {
        v12 = rf_string_concat_object_cstr(v18, &v26[108 * v28 + 3968], "_red");
        v31 = 0;
        rf_string_assign_from_object(&v26[108 * *((_DWORD *)v26 + 991) + 3968], (int)v12);
        v31 = -1;
        rf_string_destroy_buffer(v18);
        v11 = rf_string_concat_object_cstr(v17, &v26[108 * v28 + 3968], "_blue");
        v31 = 1;
        rf_string_assign_from_object(&v26[108 * *((_DWORD *)v26 + 991) + 4076], (int)v11);
        v31 = -1;
        rf_string_destroy_buffer(v17);
        *(_DWORD *)&v26[108 * *((_DWORD *)v26 + 991) + 3976] = *(_DWORD *)&v26[108 * v28 + 3976];
        *(_DWORD *)&v26[108 * *((_DWORD *)v26 + 991) + 4084] = *(_DWORD *)&v26[108 * v28 + 3976];
        for ( i = 0; i < *(_DWORD *)&v26[108 * v28 + 3976]; ++i )
        {
          rf_string_copy_construct_from_object(v21, (char **)&v26[108 * v28 + 3980 + 8 * i]);
          v31 = 2;
          v3 = rf_string_length_from_cstr(v21);
          rf_string_substring_inclusive(v21, v22, 0, v3 - 5);
          LOBYTE(v31) = 3;
          rf_vfile_construct_unopened(self);
          LOBYTE(v31) = 4;
          rf_string_construct_empty(v23);
          LOBYTE(v31) = 5;
          if ( rf_string_find_case_insensitive(v22, "-mip", 1) <= -1
            && rf_string_find_case_insensitive(v22, "_mip", 1) <= -1 )
          {
            v9 = rf_string_concat_object_cstr(v15, v22, "_red.tga");
            LOBYTE(v31) = 7;
            rf_string_assign_from_object(v23, (int)v9);
            LOBYTE(v31) = 5;
            rf_string_destroy_buffer(v15);
          }
          else
          {
            v10 = rf_string_concat_object_cstr(v16, v22, "r.tga");
            LOBYTE(v31) = 6;
            rf_string_assign_from_object(v23, (int)v10);
            LOBYTE(v31) = 5;
            rf_string_destroy_buffer(v16);
          }
          v4 = (char *)rf_string_object_c_str_or_empty(v23);
          if ( rf_vfile_resolve_open_source((int)self, v4, (int)byte_98967F) == 1 )
            rf_string_assign_from_object(&v26[108 * *((_DWORD *)v26 + 991) + 3980 + 8 * i], (int)v23);
          else
            rf_string_assign_from_object(&v26[108 * *((_DWORD *)v26 + 991) + 3980 + 8 * i], (int)v21);
          rf_string_construct_empty(v25);
          LOBYTE(v31) = 8;
          if ( rf_string_find_case_insensitive(v22, "-mip", 1) <= -1
            && rf_string_find_case_insensitive(v22, "_mip", 1) <= -1 )
          {
            v7 = rf_string_concat_object_cstr(v13, v22, "_blue.tga");
            LOBYTE(v31) = 10;
            rf_string_assign_from_object(v25, (int)v7);
            LOBYTE(v31) = 8;
            rf_string_destroy_buffer(v13);
          }
          else
          {
            v8 = rf_string_concat_object_cstr(v14, v22, "b.tga");
            LOBYTE(v31) = 9;
            rf_string_assign_from_object(v25, (int)v8);
            LOBYTE(v31) = 8;
            rf_string_destroy_buffer(v14);
          }
          v5 = (char *)rf_string_object_c_str_or_empty(v25);
          if ( rf_vfile_resolve_open_source((int)self, v5, (int)byte_98967F) == 1 )
            rf_string_assign_from_object(&v26[108 * *((_DWORD *)v26 + 991) + 4088 + 8 * i], (int)v25);
          else
            rf_string_assign_from_object(&v26[108 * *((_DWORD *)v26 + 991) + 4088 + 8 * i], (int)v21);
          LOBYTE(v31) = 5;
          rf_string_destroy_buffer(v25);
          LOBYTE(v31) = 4;
          rf_string_destroy_buffer(v23);
          LOBYTE(v31) = 3;
          rf_vfile_destruct_close_if_open(self);
          LOBYTE(v31) = 2;
          rf_string_destroy_buffer(v22);
          v31 = -1;
          rf_string_destroy_buffer(v21);
        }
        *((_DWORD *)v26 + 991) += 2;
      }
    }
    for ( j = 0; j < 64; ++j )
      unk_77D7A0[80 * rf_multiplayer_character_count + j] = -1;
    while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Custom Fpgun:") )
    {
      rf_text_parser_read_delimited_cstring((int)parser, String1, 1024, 34, 34);
      v20 = sub_50FB80(String1);
      if ( v20 < 0 )
        rf_fatal_error_show_message_and_exit(
          "D:\\projects\\rf_pc\\gamesrc\\multi\\multi_entity.cpp",
          940,
          "Weapon type specified in pc_multi.tbl could not be found in weapons.tbl!");
      rf_text_parser_read_delimited_cstring((int)parser, String1, 1024, 34, 34);
      type_by_name = rf_fpgun_find_type_by_name(String1);
      if ( type_by_name < 0 )
        rf_fatal_error_show_message_and_exit(
          "D:\\projects\\rf_pc\\gamesrc\\multi\\multi_entity.cpp",
          947,
          "Fpgun type specified in pc_multi.tbl could not be found in fpgun.tbl!");
      unk_77D7A0[80 * rf_multiplayer_character_count + v20] = type_by_name;
    }
    ++rf_multiplayer_character_count;
  }
}

