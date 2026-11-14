// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578B80 rf_text_parser_find_substring_with_wrap
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus target,RET4. Tries578BF0(target,NULL) from current cursor;success leaves cursor at match start. First failure may already skip leading trivia. Saves bookmark of THAT post-failure state,rewinds loaded buffer to base/line1,and tries once from beginning. Wrapped success keeps new position;wrapped failure restores saved post-skip state,not original pre-call trivia position. Case-sensitive raw substring search;does not consume target. No buffer-load or stored-size initialization added.
char __thiscall rf_text_parser_find_substring_with_wrap(char **this, char *SubStr)
{
  _DWORD v4[2]; // [esp+4h] [ebp-8h] BYREF

  if ( rf_text_parser_find_substring_before_optional_stop(this, SubStr, nullptr) )
    return 1;
  rf_text_parser_save_cursor_bookmark(this, v4);
  rf_memory_text_parser_reset_cursor_if_loaded(this);
  if ( rf_text_parser_find_substring_before_optional_stop(this, SubStr, nullptr) )
    return 1;
  rf_text_parser_restore_cursor_bookmark(this, v4);
  return 0;
}

