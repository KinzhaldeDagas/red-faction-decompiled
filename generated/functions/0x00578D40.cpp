// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578D40 rf_text_parser_copy_until_substring_or_read_line
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus(destination,capacity,target,optionalStop),RET16. Saves source cursor BEFORE578BF0 skips trivia. Found target:Count=current-source,copies that entire span including leading skipped trivia/comments via strncpy,addsNUL,and returnsCount;capacity argument is IGNORED on this path. Cursor remains target start. Search failure:reads raw CR-terminated line from CURRENT post-skip cursor with579460(capacity),IGNORES its0/1 result,and returns strlen(destination). EOF/too-long fallback can therefore inspect unchanged/uninitialized destination. No rewind,buffer/alias or success-capacity protection.
size_t __thiscall rf_text_parser_copy_until_substring_or_read_line(
        char **this,
        char *Destination,
        int a3,
        char *SubStr,
        char *a5)
{
  char *Source; // [esp+14h] [ebp-8h]
  size_t Count; // [esp+18h] [ebp-4h]

  Source = *(this + 1);
  if ( rf_text_parser_find_substring_before_optional_stop(this, SubStr, a5) )
  {
    Count = *(this + 1) - Source;
    strncpy(Destination, Source, Count);
    Destination[Count] = 0;
    return Count;
  }
  else
  {
    rf_text_parser_read_cr_line_cstring_if_fits((int)this, Destination, a3);
    return strlen(Destination);
  }
}

