// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057A660 rf_text_parser_read_parenthesized_float_list_unbounded
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): ECX parser, float output array, third capacity-like argument UNUSED. Requires (, reads579C20 values into consecutive floats until )/EOF with full trivia between, requires/consumes ), returns count. No capacity check or comma syntax, empty list valid. Numeric grammar can split adjacent signed values; writes earlier entries before later error. Stores each ST0 result to float regardless of integer-only reader precision.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Number-list native helper ignores passed limit and writes native-number values until CURRENT closing ). Empty/mismatched lists consumed. No native pair-count equality/positive requirement. Host unsafe storage boundary must remain explicit.
int __thiscall rf_text_parser_read_parenthesized_float_list_unbounded(int this, int a2, int a3)
{
  int v5; // [esp+4h] [ebp-4h]

  rf_text_parser_skip_trivia_and_cr_lines((_DWORD *)this);
  if ( **(_BYTE **)(this + 4) != 40 )
    rf_text_parser_fatal_expected_with_context((char **)this, "a float list");
  ++*(_DWORD *)(this + 4);
  rf_text_parser_skip_trivia_and_cr_lines((_DWORD *)this);
  v5 = 0;
  while ( **(_BYTE **)(this + 4) && **(_BYTE **)(this + 4) != 41 )
  {
    *(float *)(a2 + 4 * v5++) = rf_text_parser_read_number_with_optional_decimal_fraction((char **)this);
    rf_text_parser_skip_trivia_and_cr_lines((_DWORD *)this);
  }
  if ( **(_BYTE **)(this + 4) != 41 )
    rf_text_parser_fatal_expected_with_context((char **)this, "a float list terminator");
  ++*(_DWORD *)(this + 4);
  return v5;
}

