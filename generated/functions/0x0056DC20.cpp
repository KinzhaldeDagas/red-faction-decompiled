// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056DC20 rf_console_lexer_advance_character_percent_to_underscore
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. If *cursor663EF8 nonzero,copies raw byte to current180930C and increments cursor;then replaces current percent(37) with underscore(95). At NUL sets current0 and leaves cursor at terminator. Original input memory is unchanged. Global state,no locking/NULL guard. EAX/AL incidental:percent replacement affects current global but AL may still be original byte;at NUL EAX originates cursor address.
char rf_console_lexer_advance_character_percent_to_underscore()
{
  char result; // al

  result = (char)off_663EF8;
  if ( *(_BYTE *)off_663EF8 )
  {
    result = *(_BYTE *)off_663EF8;
    unk_180930C = *(_BYTE *)off_663EF8;
    off_663EF8 = (_UNKNOWN *)((char *)off_663EF8 + 1);
    if ( unk_180930C == 37 )
      unk_180930C = 95;
  }
  else
  {
    unk_180930C = 0;
  }
  return result;
}

