// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057A3F0 rf_text_parser_read_parenthesized_rfstring_list_unbounded
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): ECX parser, array of existing8-byte RFString elements, third capacity-like argument UNUSED. Requires (, reads quoted strings via579FB0 into successive array elements until ) or EOF, skips full trivia between, requires/consumes ), returns element count. No array capacity check, allocation or element construction. No comma separator handling; adjacent quoted strings accepted. Prior elements are written before missing-terminator diagnostic. Empty parentheses return0.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: String-list native helper ignores passed limit and writes repeated quoted values until CURRENT closing ). Empty list valid, commas not separators. Host represented-storage limit must report Unsupported for unsafe writes, not claim native clamp/fatal.
int __thiscall rf_text_parser_read_parenthesized_rfstring_list_unbounded(char **this, int a2, int a3)
{
  int v5; // [esp+8h] [ebp-4h]

  rf_text_parser_skip_trivia_and_cr_lines(this);
  if ( **(this + 1) != 40 )
    rf_text_parser_fatal_expected_with_context(this, "a string list");
  ++*(this + 1);
  rf_text_parser_skip_trivia_and_cr_lines(this);
  v5 = 0;
  while ( **(this + 1) && **(this + 1) != 41 )
  {
    rf_text_parser_read_delimited_rfstring(this, (void *)(a2 + 8 * v5++), 34, 34);
    rf_text_parser_skip_trivia_and_cr_lines(this);
  }
  if ( **(this + 1) != 41 )
    rf_text_parser_fatal_expected_with_context(this, "a string list terminator");
  ++*(this + 1);
  return v5;
}

