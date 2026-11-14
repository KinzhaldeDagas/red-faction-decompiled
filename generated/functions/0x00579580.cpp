// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579580 rf_text_parser_skip_trivia_then_read_cstring_line
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus(destination,capacity),RET8. Calls5789E0 then579460;returns raw reader0/1. Too-long/EOF leaves destination unchanged but initial trivia already consumed;not a transactional line read. Inline comment text retained. Used by console script loader with256B line storage.
char __thiscall rf_text_parser_skip_trivia_then_read_cstring_line(_DWORD *this, char *Destination, int a3)
{
  rf_text_parser_skip_trivia_and_cr_lines(this);
  return rf_text_parser_read_cr_line_cstring_if_fits((int)this, Destination, a3);
}

