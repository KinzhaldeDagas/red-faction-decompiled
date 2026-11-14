// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005795B0 rf_text_parser_peek_case_insensitive_prefix
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus keyword,RET4. Computes strlen(keyword),skips full leading trivia,then returns1 iff current byte nonzero AND _strnicmp(cursor,keyword,length)==0. Does not consume matched characters but DOES consume leading trivia on mismatch. No token-ending boundary:keyword true matches trueSuffix. Empty keyword matches any non-EOF position;atEOF returns0. No NULL/size validation.
bool __thiscall rf_text_parser_peek_case_insensitive_prefix(int this, char *String2)
{
  unsigned int MaxCount; // [esp+18h] [ebp-4h]

  MaxCount = strlen(String2);
  rf_text_parser_skip_trivia_and_cr_lines((_DWORD *)this);
  return **(_BYTE **)(this + 4) && _strnicmp(*(const char **)(this + 4), String2, MaxCount) == 0;
}

