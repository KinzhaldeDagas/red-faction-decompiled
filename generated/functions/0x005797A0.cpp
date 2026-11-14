// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005797A0 rf_text_parser_require_case_insensitive_prefix_or_fatal
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus keyword,RET4. Calls579630;successfulAL1 returned. On mismatch unbounded sprintf wraps expected keyword in quotes inside260B local,then579200 fatal diagnostic. Does not demand keyword boundary or roll back skipped trivia;long expected text can overrun diagnostic formatting. No recoverable error return.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Required raw cursor prefix delegates579630 then fatal context on mismatch. Its location is CURRENT cursor after trivia, never search-ahead. Full record order therefore cannot be proved by permissive document entries.
bool __thiscall rf_text_parser_require_case_insensitive_prefix_or_fatal(void *parser, const char *keyword)
{
  bool result; // al
  char Buffer[260]; // [esp+4h] [ebp-108h] BYREF

  result = rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, (char *)keyword);
  if ( !result )
  {
    sprintf(Buffer, "\"%s\"", keyword);
    rf_text_parser_fatal_expected_with_context((char **)parser, Buffer);
  }
  return result;
}

