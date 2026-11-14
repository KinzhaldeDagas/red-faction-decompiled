// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005789E0 rf_text_parser_skip_trivia_and_cr_lines
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver. Skips space32,9..12 and CR13;only CR increments DWORD264 line number. Consumes // through CR-or-NUL then outer loop consumes/counts CR;LF never terminates // by itself. Handles /* through578850,first closing pair only,no nesting/error onEOF. Leading trivia only;does not process later comments until called again. Zero return may also mean slash followed byNUL while cursor still points slash. Uses current C string,not stored size bounds;return incidental.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Trivia grammar reconfirmed: ASCIIspace or9..13; CR alone increments line. // skips through LF until CR/NUL; /* closes at first */ or stops atNUL without immediate fatal. Comments recognized only by trivia scanning, not inside quoted bodies.
int __thiscall rf_text_parser_skip_trivia_and_cr_lines(_DWORD *this)
{
  _BYTE *v1; // edx
  int result; // eax

  while ( 1 )
  {
    v1 = (_BYTE *)*(this + 1);
    result = (char)*v1;
    if ( !*v1 )
      break;
    if ( *(_BYTE *)*(this + 1) == 32 || *(char *)*(this + 1) >= 9 && *(char *)*(this + 1) < 13 )
    {
      ++*(this + 1);
    }
    else if ( *(_BYTE *)*(this + 1) == 13 )
    {
      ++*(this + 1);
      ++*(this + 66);
    }
    else if ( *(_BYTE *)*(this + 1) == 47 && *(_BYTE *)(*(this + 1) + 1) == 47 )
    {
      while ( *(_BYTE *)*(this + 1) && *(_BYTE *)*(this + 1) != 13 )
        ++*(this + 1);
    }
    else
    {
      result = *(char *)*(this + 1);
      if ( result != 47 )
        return result;
      result = *(char *)(*(this + 1) + 1);
      if ( result != 42 )
        return result;
      *(this + 1) += 2;
      rf_text_parser_skip_block_comment_body((int)this);
    }
  }
  return result;
}

