// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578CC0 rf_text_parser_find_with_wrap_and_consume_required
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus target,RET4. Calls578B80 case-sensitive find-with-wrap;failure0. Success calls5797A0 case-insensitive required-prefix consumer at found position,then returns1. No bookmark rollback around required consumer/fatal failure;keyword ending boundary not required. Inherits raw search matching inside comments/quotes and skip-trivia effects.
unsigned __int8 __thiscall rf_text_parser_find_with_wrap_and_consume_required(void *self, const char *keyword)
{
  if ( !rf_text_parser_find_substring_with_wrap((char **)self, (char *)keyword) )
    return 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, keyword);
  return 1;
}

