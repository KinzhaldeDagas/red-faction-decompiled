// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578B10 rf_text_parser_advance_to_cr_with_terminator_quirk
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver,no stack args. While current!=CR,reads byte then advances cursor;encountered NUL returns AFTER advancing one byte past terminator. On CR increments line264 but DOES NOT advance cursor before comparing same byte toLF,so ordinary CR path returns13 leaving CR unconsumed. Repeated calls atCR repeatedly increment line without progress. Intended-looking LF branch is unreachable for unchanged input because current stillCR. EAX mixes receiver pointer/character,not a boolean or length;no size/NULL guard.
int __thiscall rf_text_parser_advance_to_cr_with_terminator_quirk(void *self)
{
  int v1; // edx
  int result; // eax

  while ( **((_BYTE **)self + 1) != 13 )
  {
    v1 = **((char **)self + 1);
    result = (int)self;
    ++*((_DWORD *)self + 1);
    if ( !v1 )
      return result;
  }
  ++*((_DWORD *)self + 66);
  result = **((char **)self + 1);
  if ( result == 10 )
  {
    ++*((_DWORD *)self + 1);
    return (int)self;
  }
  return result;
}

