// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00506AF0 sub_506AF0
// UNREALRED VERIFIED [clutter-vclip-debris]: Optional $particle count is parsed as integer into definition +0x34, then emitter fields are parsed at +0x38; absent count writes zero. Getter 0x507830 returns this same field.
// UNREALRED VERIFIED [combat-particle-range-20261104]: Optional $VBM Filename is independently retained at definition string+0x0C; runtime506E20 has a separate bitmap representation before graph/inline. A zero-count inline branch does not prove an empty VClip if this filename is present (retail screenboom also namesboom01.vbm). Retain this field when classifying verified zero-particle presentation; do not hide unsupported bitmap behavior behind handled-empty success.
// UNREALRED VERIFIED [combat-particle-vbm-20261104]: Optional$VBM Glow byte atdefinition+0x20 is readonlyfollowing$VBM Filename anddefaultszero. Flagtable663A18 decodesbit1 liquid_surface,bit2 radius_in_multiples,bit4 no_z_check,bit8 code_explode. VBMglow isindependentofinline particle flags. VClip no_z_check alsoORsdepthbitintoinline onlywhenexplicit sourcepredicate438B00 passes.
void __cdecl sub_506AF0(_BYTE **parser)
{
  int parenthesized_named_flag_mask; // eax
  double number_with_optional_decimal_fraction; // st7
  char boolean_word_prefix; // al
  double v4; // st7
  char *v5; // eax
  int name; // eax
  int signed_decimal_or_hex_integer; // eax
  void *v8[2]; // [esp+4h] [ebp-18h] BYREF
  void *destination; // [esp+Ch] [ebp-10h]
  int v10; // [esp+18h] [ebp-4h]

  rf_string_construct_empty(v8);
  v10 = 0;
  destination = (char *)&unk_90DC80 + 224 * unk_90B820++;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Name:");
  rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Flags:") )
  {
    parenthesized_named_flag_mask = rf_text_parser_read_parenthesized_named_flag_mask(parser, (int)off_663A18, 4);
    *((_DWORD *)destination + 12) = parenthesized_named_flag_mask;
  }
  else
  {
    *((_DWORD *)destination + 12) = 0;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$damage:") )
  {
    number_with_optional_decimal_fraction = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 2) = number_with_optional_decimal_fraction;
  }
  else
  {
    *((float *)destination + 2) = 0.0;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$VBM Filename:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, (char *)destination + 12, 34, 34);
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$VBM Glow:") )
    {
      boolean_word_prefix = rf_text_parser_read_boolean_word_prefix((const char **)parser);
      *((_BYTE *)destination + 32) = boolean_word_prefix;
    }
    else
    {
      *((_BYTE *)destination + 32) = 0;
    }
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Explosion Name:") )
    rf_text_parser_read_delimited_cstring((int)parser, (char *)destination + 192, 32, 34, 34);
  else
    *((_BYTE *)destination + 192) = 0;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$VFX Filename:") )
    rf_text_parser_read_delimited_rfstring(parser, (char *)destination + 36, 34, 34);
  else
    rf_string_assign_from_cstr((_DWORD *)destination + 9, (char *)&byte_63E50E);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$VFX Radius:") )
  {
    v4 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 47) = v4;
  }
  else
  {
    *((float *)destination + 47) = 20.0;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Foley Sound:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, v8, 34, 34);
    v5 = (char *)rf_string_object_c_str_or_empty(v8);
    name = rf_foley_definition_find_name(v5);
    *((_DWORD *)destination + 11) = name;
  }
  else
  {
    *((_DWORD *)destination + 11) = -1;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$particle count:") )
  {
    signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
    *((_DWORD *)destination + 13) = signed_decimal_or_hex_integer;
    rf_particle_emitter_definition_parse(parser, (int)destination + 56);
  }
  else
  {
    *((_DWORD *)destination + 13) = 0;
  }
  v10 = -1;
  rf_string_destroy_buffer(v8);
}

