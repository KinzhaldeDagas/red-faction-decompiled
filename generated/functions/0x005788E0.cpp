// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005788E0 rf_text_parser_skip_trivia_preserving_cr
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver. Skips space32 and bytes9..12 (tab,LF,VT,FF),but leaves CR13 unconsumed/un-counted. // skips until CR orNUL,so LF-only comment consumes rest of buffer;/* advances2 then578850 handles body/closing and CR counting. Unterminated block comment does not fail. Returns signed current character in ordinary cases,but slash not followed by comment returns FOLLOWING character while cursor remains slash;return is incidental,not reliable EOF/current-char status. No cursor/size guard.
int __thiscall rf_text_parser_skip_trivia_preserving_cr(void *self)
{
  _BYTE *v1; // edx
  int result; // eax

  while ( 1 )
  {
    v1 = *((_BYTE **)self + 1);
    result = (char)*v1;
    if ( !*v1 )
      break;
    if ( **((_BYTE **)self + 1) == 32 || **((char **)self + 1) >= 9 && **((char **)self + 1) < 13 )
    {
      ++*((_DWORD *)self + 1);
    }
    else if ( **((_BYTE **)self + 1) == 47 && *(_BYTE *)(*((_DWORD *)self + 1) + 1) == 47 )
    {
      while ( **((_BYTE **)self + 1) && **((_BYTE **)self + 1) != 13 )
        ++*((_DWORD *)self + 1);
    }
    else
    {
      result = **((char **)self + 1);
      if ( result != 47 )
        return result;
      result = *(char *)(*((_DWORD *)self + 1) + 1);
      if ( result != 42 )
        return result;
      *((_DWORD *)self + 1) += 2;
      rf_text_parser_skip_block_comment_body((int)self);
    }
  }
  return result;
}

