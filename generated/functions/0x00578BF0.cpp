// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578BF0 rf_text_parser_find_substring_before_optional_stop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus(target,optionalStop),RET8. Skips leading trivia first. If signed(cursor-base)>storedSize268 returns0;does not reject negative offset or enforce found-position bounds separately. Calls41F140/CRT strstr for first CASE-SENSITIVE target anywhere in remaining C string. Optional stop searched similarly;rejects only when stop match strictly BEFORE target (equal allowed). On success advances cursor to target start,counting CR along raw span,returns1;does not consume target or ignore comments/quotes within search span. On failure initial trivia remains consumed. No NULL target/valid-buffer guard.
char __thiscall rf_text_parser_find_substring_before_optional_stop(char **this, char *SubStr, char *a3)
{
  int v4; // eax
  char *v6; // [esp+4h] [ebp-8h]
  char *first_substring; // [esp+8h] [ebp-4h]

  rf_text_parser_skip_trivia_and_cr_lines(this);
  if ( *(this + 1) - *this > (int)*(this + 67) )
    return 0;
  first_substring = rf_cstring_find_first_substring(*(this + 1), SubStr);
  if ( !first_substring )
    return 0;
  if ( a3 )
  {
    v6 = rf_cstring_find_first_substring(*(this + 1), a3);
    if ( v6 )
    {
      if ( v6 < first_substring )
        return 0;
    }
  }
  while ( *(this + 1) != first_substring )
  {
    v4 = *(*(this + 1))++;
    if ( v4 == 13 )
      ++*(this + 66);
  }
  return 1;
}

