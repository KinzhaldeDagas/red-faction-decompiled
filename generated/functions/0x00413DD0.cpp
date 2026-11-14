// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413DD0 rf_clutter_class_parse_next_into_registry
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Cdecl parser;destination=667000+232*globalcount666B60 BEFORE admission,no own450-slot guard,slot construction/clear or count increment. Searches $Class Name:;if absent,searches #End with resultIGNORED,returns-1 even if end token absent. On class:requires quoted className RFString0 andV3D filename8. Case-insensitive final-dot suffix .vfx ->modelkind56=3,otherwise1 (no extension rejection). Optional debris filename24 defaultsEMPTY;absent debris sound-set32/corpse class16 leave prior strings. Repeated $Emitter resolves names and APPENDS IDs including failures to existing array40;emitter life52 defaults-1. Required material name stores ONLY BYTE76;optional radius64
// defaults-1;required life60 numeric. Initializes11 damage factors156..196 to1 then repeated $Damage Type Factor maps name;index-1 fatal,other indices written at156+4*index without own upper check. Sound80/useSound84 default-1;explodeAnim88 initialized-1,explodeRadius92 initially0 but final absent-tag default1;explodeDamage96 default1;explodeOffset100 XYZ default0;glare124/rodGlare128 default-1. Required flags116 uses9-name table6612AC:bits0..8 collectable,collide_weapon,collide_object,is_screen,shatters,has_alpha,is_switch,can_carry,is_clock. Screen width224/height228 default64,unclamped signed parser values otherwise. Delegates optional Use classification/radius into68/72;absent Use leaves both prior values,unrecognized present value writes68=0 but retains72. DebrisVelocity120 defaultsfloat8.0. Before nextClass,optional Skin search starts loop:try-consumes $Skin: BEFORE checking existing
// skin count200<10;an eleventh tag can be consumed with its quoted payload left unread. Each accepted108-byte record:construct13 empty RFStrings but count8 initiallyunset;read skinName0 and parenthesized texture list at12,pass nominal limit12 to helper that IGNORES limit;store returned count8. More than12 entries can overwrite local storage;no own bounds check. Deep-copy-construct by-value108-byte argument,append into existing array200;callee destroys by-value copy,then parser appends +Glare lookup or-1 to parallel array212 and destroys original temporary. No clearing of old skins/emitters,uniqueness/finite/range checks or rollback;malformed/fatal parsing can leave partial slot writes. Returns0 after class parse,does NOT increment globalcount.
int __cdecl rf_clutter_class_parse_next_into_registry(_DWORD *parser)
{
  char *v2; // eax
  char *last_dot_or_empty_literal; // eax
  char *v4; // eax
  int v5; // eax
  double number_with_optional_decimal_fraction; // st7
  char v7; // al
  double v8; // st7
  double v9; // st7
  char *v10; // eax
  double v11; // st7
  char *v12; // eax
  int v13; // eax
  char *v14; // eax
  int v15; // eax
  char *v16; // eax
  int v17; // eax
  double v18; // st7
  double v19; // st7
  const char *v20; // eax
  int name_case_sensitive; // eax
  const char *v22; // eax
  int v23; // eax
  int parenthesized_named_flag_mask; // eax
  int signed_decimal_or_hex_integer; // eax
  int v26; // eax
  double v27; // st7
  const char *v28; // eax
  int v29[29]; // [esp-6Ch] [ebp-110h] BYREF
  int v30; // [esp+8h] [ebp-9Ch]
  int *v31; // [esp+Ch] [ebp-98h]
  int v32; // [esp+14h] [ebp-90h]
  int word24[3]; // [esp+18h] [ebp-8Ch] BYREF
  int word25[25]; // [esp+24h] [ebp-80h] BYREF
  char name[4]; // [esp+88h] [ebp-1Ch] BYREF
  void *destination; // [esp+90h] [ebp-14h]
  int i; // [esp+94h] [ebp-10h]
  int v38; // [esp+A0h] [ebp-4h]

  rf_string_construct_empty(name);
  v38 = 0;
  destination = &byte_667000[232 * unk_666B60];
  if ( rf_text_parser_find_substring_before_optional_stop((char **)parser, "$Class Name:", nullptr) )
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Class Name:");
    rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$V3D Filename:");
    rf_text_parser_read_delimited_rfstring(parser, (char *)destination + 8, 34, 34);
    v2 = (char *)rf_string_object_c_str_or_empty((char *)destination + 8);
    last_dot_or_empty_literal = rf_path_find_last_dot_or_empty_literal(v2);
    rf_string_assign_from_cstr(name, last_dot_or_empty_literal);
    if ( rf_string_equals_case_insensitive((int)name, ".vfx") )
      *((_DWORD *)destination + 14) = 3;
    else
      *((_DWORD *)destination + 14) = 1;
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Debris Filename:") )
      rf_text_parser_read_delimited_rfstring(parser, (char *)destination + 24, 34, 34);
    else
      rf_string_assign_from_cstr((_DWORD *)destination + 6, (char *)&byte_63128B);
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Debris Sound Set:") )
      rf_text_parser_read_delimited_rfstring(parser, (char *)destination + 32, 34, 34);
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Corpse Class Name:") )
      rf_text_parser_read_delimited_rfstring(parser, (char *)destination + 16, 34, 34);
    while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Emitter:") )
    {
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v4 = (char *)rf_string_object_c_str_or_empty(name);
      v5 = rf_particle_emitter_definition_find_name(v4);
      rf_pointer_array_append_dword((_DWORD *)destination + 10, v5);
    }
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Emitter Life:") )
    {
      number_with_optional_decimal_fraction = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)destination + 13) = number_with_optional_decimal_fraction;
    }
    else
    {
      *((float *)destination + 13) = -1.0;
    }
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Material:");
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v7 = rf_material_name_to_index(name);
    *((_BYTE *)destination + 76) = v7;
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Radius:") )
    {
      v8 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)destination + 16) = v8;
    }
    else
    {
      *((float *)destination + 16) = -1.0;
    }
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Life:");
    v9 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 15) = v9;
    for ( i = 0; i < 11; ++i )
      *((float *)destination + i + 39) = 1.0;
    while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Damage Type Factor:") )
    {
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v10 = (char *)rf_string_object_c_str_or_empty(name);
      i = sub_4BCFF0(v10);
      if ( i == -1 )
        rf_fatal_error_show_message_and_exit(
          "D:\\projects\\rf_pc\\gamesrc\\clutter\\clutter.cpp",
          836,
          "Clutter.tbl error! Cannot set damage factor for damage type 'undefined'!");
      v11 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)destination + i + 39) = v11;
    }
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Sound:") )
    {
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v12 = (char *)rf_string_object_c_str_or_empty(name);
      v13 = rf_foley_definition_find_name(v12);
      *((_DWORD *)destination + 20) = v13;
    }
    else
    {
      *((_DWORD *)destination + 20) = -1;
    }
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Use Sound:") )
    {
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v14 = (char *)rf_string_object_c_str_or_empty(name);
      v15 = rf_foley_definition_find_name(v14);
      *((_DWORD *)destination + 21) = v15;
    }
    else
    {
      *((_DWORD *)destination + 21) = -1;
    }
    *((_DWORD *)destination + 22) = -1;
    *((float *)destination + 23) = 0.0;
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Explode Anim:") )
    {
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v16 = (char *)rf_string_object_c_str_or_empty(name);
      v17 = sub_507610(v16);
      *((_DWORD *)destination + 22) = v17;
    }
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Explode Anim Radius:") )
    {
      v18 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)destination + 23) = v18;
    }
    else
    {
      *((float *)destination + 23) = 1.0;
    }
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Explode Damage:") )
    {
      v19 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)destination + 24) = v19;
    }
    else
    {
      *((float *)destination + 24) = 1.0;
    }
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Explode Offset:") )
      rf_text_parser_read_angle_bracket_vector3((int)parser, (float *)destination + 25);
    else
      rf_vector3_zero_return_destination((float *)destination + 25);
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Glare:") )
    {
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v20 = rf_string_object_c_str_or_empty(name);
      name_case_sensitive = rf_glare_definition_find_name_case_sensitive(v20);
      *((_DWORD *)destination + 31) = name_case_sensitive;
    }
    else
    {
      *((_DWORD *)destination + 31) = -1;
    }
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Rod Glare:") )
    {
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v22 = rf_string_object_c_str_or_empty(name);
      v23 = rf_glare_definition_find_name_case_sensitive(v22);
      *((_DWORD *)destination + 32) = v23;
    }
    else
    {
      *((_DWORD *)destination + 32) = -1;
    }
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Flags:");
    parenthesized_named_flag_mask = rf_text_parser_read_parenthesized_named_flag_mask(
                                      (_BYTE **)parser,
                                      (int)off_6612AC,
                                      9);
    *((_DWORD *)destination + 29) = parenthesized_named_flag_mask;
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Screen Width:") )
    {
      signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
      *((_DWORD *)destination + 56) = signed_decimal_or_hex_integer;
    }
    else
    {
      *((_DWORD *)destination + 56) = 64;
    }
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Screen Height:") )
    {
      v26 = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
      *((_DWORD *)destination + 57) = v26;
    }
    else
    {
      *((_DWORD *)destination + 57) = 64;
    }
    rf_text_parse_optional_use_classification((int)parser, (_DWORD *)destination + 17, (float *)destination + 18);
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Debris Velocity:") )
    {
      v27 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)destination + 30) = v27;
    }
    else
    {
      *((float *)destination + 30) = flt_6612F4;
    }
    if ( rf_text_parser_find_substring_before_optional_stop((char **)parser, "$Skin:", "$Class Name:") == 1 )
    {
      while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Skin:")
           && rf_receiver_get_first_dword((char *)destination + 200) < 10 )
      {
        rf_clutter_skin108_construct_strings((char *)word24);
        LOBYTE(v38) = 1;
        rf_text_parser_read_delimited_rfstring(parser, word24, 34, 34);
        word24[2] = rf_text_parser_read_parenthesized_rfstring_list_unbounded((_BYTE **)parser, (int)word25, 12);
        v31 = v29;
        v29[28] = (int)rf_clutter_skin108_copy_construct(v29, (char *)word24);
        rf_clutter_skin_array_append_value108(
          (_DWORD *)destination + 50,
          v29[0],
          v29[1],
          v29[2],
          v29[3],
          v29[4],
          v29[5],
          v29[6],
          v29[7],
          v29[8],
          v29[9],
          v29[10],
          v29[11],
          v29[12],
          v29[13],
          v29[14],
          v29[15],
          v29[16],
          v29[17],
          v29[18],
          v29[19],
          v29[20],
          v29[21],
          v29[22],
          v29[23],
          v29[24],
          v29[25],
          v29[26]);
        if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Glare:") )
        {
          rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
          v28 = rf_string_object_c_str_or_empty(name);
          v32 = rf_glare_definition_find_name_case_sensitive(v28);
          rf_pointer_array_append_dword((_DWORD *)destination + 53, v32);
        }
        else
        {
          rf_pointer_array_append_dword((_DWORD *)destination + 53, -1);
        }
        LOBYTE(v38) = 0;
        rf_clutter_skin108_destroy_strings((char *)word24);
      }
    }
    v30 = 0;
    v38 = -1;
    rf_string_destroy_buffer(name);
    return v30;
  }
  else
  {
    rf_text_parser_find_substring_before_optional_stop((char **)parser, "#End", nullptr);
    v38 = -1;
    rf_string_destroy_buffer(name);
    return -1;
  }
}

