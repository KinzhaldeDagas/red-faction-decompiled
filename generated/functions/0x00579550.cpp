// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579550 rf_text_parser_skip_trivia_then_read_rfstring_line
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus RFString output,RET4. Calls5789E0 full leading trivia/comment/CR skipper,then579380 raw line reader and returns itsAL. Only LEADING comments removed;inline comment markers after returned text start remain literal. Failure may already have consumed whitespace/comments/lines;EOF clears RFString through underlying reader.
unsigned __int8 __thiscall rf_text_parser_skip_trivia_then_read_rfstring_line(void *self, void *out_string)
{
  rf_text_parser_skip_trivia_and_cr_lines(self);
  return rf_text_parser_read_cr_line_into_rfstring((int)self, out_string);
}

