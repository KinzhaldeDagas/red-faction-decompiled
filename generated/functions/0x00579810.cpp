// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579810 rf_text_parser_read_boolean_word_prefix
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver,no stack args. Skips trivia,then consumes true or yes as1,false or no as0 using case-insensitive prefix helpers;others invoke579200 expected a boolean value. Does not accept numeric0/1 or enforce word boundary: trueX leavesX, nope consumesno and leavespe. Additional attempted-prefix skips do not restore cursor. Returns normalizedBYTE0/1 on normal paths.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Boolean reader uses CURRENT CI prefixes true/yes =>1 and false/no=>0; no token boundary. Numeric0/1 are not alternate native boolean spellings.
char __thiscall rf_text_parser_read_boolean_word_prefix(const char **this)
{
  rf_text_parser_skip_trivia_and_cr_lines(this);
  if ( rf_text_parser_try_consume_case_insensitive_prefix(this, "true")
    || rf_text_parser_try_consume_case_insensitive_prefix(this, (char *)off_6411B4) )
  {
    return 1;
  }
  if ( !rf_text_parser_try_consume_case_insensitive_prefix(this, "false")
    && !rf_text_parser_try_consume_case_insensitive_prefix(this, "no") )
  {
    rf_text_parser_fatal_expected_with_context((char **)this, "a boolean value");
  }
  return 0;
}

