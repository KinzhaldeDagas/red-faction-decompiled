// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579E00 rf_text_parser_read_bracketed_matrix3
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): ECX parser, nine consecutive float outputs. Requires [, reads three angle-bracket vector3 values579D40 at offsets0/12/24, probes optional commas between vectors, requires ] and consumes it, returns receiver. No transpose, orthogonality or normalization operation; earlier output writes remain before a later parse error.
int __thiscall rf_text_parser_read_bracketed_matrix3(void *self, float *out_matrix)
{
  rf_text_parser_skip_trivia_and_cr_lines(self);
  if ( **((_BYTE **)self + 1) != 91 )
    rf_text_parser_fatal_expected_with_context((char **)self, "a matrix");
  ++*((_DWORD *)self + 1);
  rf_text_parser_read_angle_bracket_vector3((int)self, out_matrix);
  rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, ",");
  rf_text_parser_read_angle_bracket_vector3((int)self, out_matrix + 3);
  rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, ",");
  rf_text_parser_read_angle_bracket_vector3((int)self, out_matrix + 6);
  rf_text_parser_skip_trivia_and_cr_lines(self);
  if ( **((_BYTE **)self + 1) != 93 )
    rf_text_parser_fatal_expected_with_context((char **)self, "a matrix terminator");
  ++*((_DWORD *)self + 1);
  return (int)self;
}

