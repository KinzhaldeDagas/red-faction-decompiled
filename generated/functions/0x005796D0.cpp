// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005796D0 rf_text_parser_try_quoted_literal_fixed_advance
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus expected literal,RET4. Skips leading trivia;requires opening double-quote. Saves cursor/line bookmark,advances past quote,then579630 performs ANOTHER trivia skip and case-insensitive prefix match;requires immediate closing quote afterward. Restores bookmark on BOTH success/failure. Failure0 leaves opening quote after initial trivia. Success advances ORIGINAL quote position by strlen(expected)+2 and returns1,ignoring any skipped trivia inside quote. Thus input doublequote+twoSpaces+foo+doublequote can match foo but leave cursor two bytes before correct end. No escapes,text output or capacity/range guard.
unsigned __int8 __thiscall rf_text_parser_try_quoted_literal_fixed_advance(void *self, const char *literal)
{
  _DWORD v4[2]; // [esp+14h] [ebp-Ch] BYREF
  bool v5; // [esp+1Fh] [ebp-1h]

  rf_text_parser_skip_trivia_and_cr_lines(self);
  if ( **((_BYTE **)self + 1) != 34 )
    return 0;
  rf_text_parser_save_cursor_bookmark(self, v4);
  ++*((_DWORD *)self + 1);
  v5 = rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, (char *)literal);
  if ( v5 && **((_BYTE **)self + 1) != 34 )
    v5 = 0;
  rf_text_parser_restore_cursor_bookmark(self, v4);
  if ( !v5 )
    return 0;
  *((_DWORD *)self + 1) += strlen(literal) + 2;
  return 1;
}

