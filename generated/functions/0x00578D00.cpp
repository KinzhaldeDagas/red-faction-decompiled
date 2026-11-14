// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578D00 rf_text_parser_find_before_stop_and_consume_required
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus(target,optionalStop),RET8. Calls578BF0 bounded-by-optional-stop raw search;failure0. On success calls5797A0 required-prefix consumer and returns1. Search is case-sensitive,consumer case-insensitive and trivia-skipping;does not create token-boundary,comment-scope or transactional rollback guarantees.
char __thiscall rf_text_parser_find_before_stop_and_consume_required(char **this, char *SubStr, char *a3)
{
  if ( !rf_text_parser_find_substring_before_optional_stop(this, SubStr, a3) )
    return 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(this, SubStr);
  return 1;
}

