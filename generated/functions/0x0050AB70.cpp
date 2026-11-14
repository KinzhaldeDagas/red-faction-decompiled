// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050AB70 rf_weapon_parse_light_block
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Weapon light cursor: require +Inner Radius number, +Outer Radius number, +Color RGBA. Native stored RGB=byte/255; parsed alpha ignored. Token presence, not successful light-resource creation, determines all reads.
float *__cdecl rf_weapon_parse_light_block(_DWORD *parser, float *a2)
{
  _BYTE v3[4]; // [esp+Ch] [ebp-4h] BYREF

  rf_rgba8_default_construct_noop(v3);
  a2[2] = 1.0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Inner Radius:");
  *a2 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Outer Radius:");
  a2[1] = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Color:");
  rf_text_parser_read_braced_rgba_bytes((int)parser, v3);
  a2[3] = (double)v3[0] / 255.0;
  a2[4] = (double)v3[1] / 255.0;
  a2[5] = (double)v3[2] / 255.0;
  return a2;
}

