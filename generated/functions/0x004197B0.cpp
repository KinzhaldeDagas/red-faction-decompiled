// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004197B0 rf_glare_definition_parse_into_current_slot
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl parser pointer; destination is0x680DD8+52*globalCount0x680AE0, without own bound check or count increment. Requires quoted $Name: RFString+0 and $Light Color: RGBA bytes+8. Optional $Corona Bitmap: loads bitmap(-1,1) into DWORD+12, then REQUIRES $Cone Angle: (float half-angle at+16), $Intensity:+20, $Radius Distance Factor:+28, $Radius Scale Factor:+24, $Diminish Distance:+32 in that order. If absent writes only bitmap+12=0, leaving associated scalars untouched. Optional $Volumetric Bitmap: stores handle+36 and requires Height:+40,Length:+44; absent writes only handle+36=0. Optional $Reflection Bitmap: stores handle+48, else0. Numeric results round to binary32 at destination stores; cone is halved
// with no degree/radian conversion here. No load-result check, defaults for absent scalar groups, finite/range validation or release of overwritten bitmap handles. Destroys only temporary filename RFString.
void __cdecl rf_glare_definition_parse_into_current_slot(const char **parser)
{
  char *v1; // eax
  int v2; // eax
  double number_with_optional_decimal_fraction; // st7
  double v4; // st7
  double v5; // st7
  double v6; // st7
  double v7; // st7
  char *v8; // eax
  int v9; // eax
  double v10; // st7
  double v11; // st7
  char *v12; // eax
  int v13; // eax
  void *v14[2]; // [esp+4h] [ebp-18h] BYREF
  void *destination; // [esp+Ch] [ebp-10h]
  int v16; // [esp+18h] [ebp-4h]

  rf_string_construct_empty(v14);
  v16 = 0;
  destination = &byte_680DD8[52 * dword_680AE0];
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Name:");
  rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Light Color:");
  rf_text_parser_read_braced_rgba_bytes((int)parser, (_BYTE *)destination + 8);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "$Corona Bitmap:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, v14, 34, 34);
    v1 = (char *)rf_string_object_c_str_or_empty(v14);
    v2 = rf_bitmap_load_with_optional_mipmap_generation(v1, (void *)0xFFFFFFFF, 1);
    *((_DWORD *)destination + 3) = v2;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Cone Angle:");
    number_with_optional_decimal_fraction = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 4) = number_with_optional_decimal_fraction * 0.5;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Intensity:");
    v4 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 5) = v4;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Radius Distance Factor:");
    v5 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 7) = v5;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Radius Scale Factor:");
    v6 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 6) = v6;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Diminish Distance:");
    v7 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 8) = v7;
  }
  else
  {
    *((_DWORD *)destination + 3) = 0;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "$Volumetric Bitmap:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, v14, 34, 34);
    v8 = (char *)rf_string_object_c_str_or_empty(v14);
    v9 = rf_bitmap_load_with_optional_mipmap_generation(v8, (void *)0xFFFFFFFF, 1);
    *((_DWORD *)destination + 9) = v9;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Volumetric Height:");
    v10 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 10) = v10;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Volumetric Length:");
    v11 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 11) = v11;
  }
  else
  {
    *((_DWORD *)destination + 9) = 0;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix(parser, "$Reflection Bitmap:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, v14, 34, 34);
    v12 = (char *)rf_string_object_c_str_or_empty(v14);
    v13 = rf_bitmap_load_with_optional_mipmap_generation(v12, (void *)0xFFFFFFFF, 1);
    *((_DWORD *)destination + 12) = v13;
  }
  else
  {
    *((_DWORD *)destination + 12) = 0;
  }
  v16 = -1;
  rf_string_destroy_buffer(v14);
}

