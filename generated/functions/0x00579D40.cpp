// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579D40 rf_text_parser_read_angle_bracket_vector3
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): ECX parser, float[3] destination. Requires <, reads three numbers via579C20 into consecutive floats, requires > and consumes it, returns receiver. Comma probes between components ignore failure, so commas are optional; numeric readers/trivia rules determine boundaries. Writes components before validating later components or closing bracket. No normalization or range validation.
int __thiscall rf_text_parser_read_angle_bracket_vector3(int this, float *a2)
{
  rf_text_parser_skip_trivia_and_cr_lines((_DWORD *)this);
  if ( **(_BYTE **)(this + 4) != 60 )
    rf_text_parser_fatal_expected_with_context((char **)this, "a vector");
  ++*(_DWORD *)(this + 4);
  *a2 = rf_text_parser_read_number_with_optional_decimal_fraction((char **)this);
  rf_text_parser_try_consume_case_insensitive_prefix((const char **)this, ",");
  a2[1] = rf_text_parser_read_number_with_optional_decimal_fraction((char **)this);
  rf_text_parser_try_consume_case_insensitive_prefix((const char **)this, ",");
  a2[2] = rf_text_parser_read_number_with_optional_decimal_fraction((char **)this);
  rf_text_parser_skip_trivia_and_cr_lines((_DWORD *)this);
  if ( **(_BYTE **)(this + 4) != 62 )
    rf_text_parser_fatal_expected_with_context((char **)this, "a vector terminator");
  ++*(_DWORD *)(this + 4);
  return this;
}

