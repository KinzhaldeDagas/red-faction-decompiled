// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578850 rf_text_parser_skip_block_comment_body
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver,no stack args. Starting at current cursor4,advances until NUL or first literal */;increments signed line counter264 ONLY for CR13. If closing pair found advances past BOTH bytes;unterminated comment silently stops at NUL with no error. No nesting,escape or quoted-text interpretation and no check for opening /*. Returns receiver incidentally,not closed-comment status;stored file size268 not consulted.
int __thiscall rf_text_parser_skip_block_comment_body(int this)
{
  int result; // eax

  while ( **(_BYTE **)(this + 4) && (**(_BYTE **)(this + 4) != 42 || *(_BYTE *)(*(_DWORD *)(this + 4) + 1) != 47) )
  {
    if ( **(_BYTE **)(this + 4) == 13 )
      ++*(_DWORD *)(this + 264);
    ++*(_DWORD *)(this + 4);
  }
  result = this;
  if ( **(_BYTE **)(this + 4) )
  {
    *(_DWORD *)(this + 4) += 2;
    return this;
  }
  return result;
}

