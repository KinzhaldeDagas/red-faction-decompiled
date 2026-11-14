// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005700E0 rf_console_lexer_accumulate_quoted_token
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Writes opening double-quote into raw buffer,advances,then copies at most198 body bytes until double-quote,NUL or preincremented count199. ALWAYS advances once after loop and appends synthetic closing quote+NUL,sets kind3. No escapes. Unterminated quote atNUL becomes syntactically quoted token;at capacity break,the still-current199th body byte is consumed/discarded by final advance,remaining tail becomes later token. Output at most200bytes plusNUL:at198-body maximum,NUL lands at1809AB8 (also status-mode flag low byte);the subsequent201-byte normalized copy to1809928 places its NUL at18099F0,clearing raw token first byte. Literal percent body characters become underscores through shared
// advance.
char *rf_console_lexer_accumulate_quoted_token()
{
  char *result; // eax
  int v1; // [esp+0h] [ebp-4h]

  *(_BYTE *)off_663EFC = 34;
  off_663EFC = (_UNKNOWN *)((char *)off_663EFC + 1);
  rf_console_lexer_advance_character_percent_to_underscore();
  v1 = 0;
  while ( unk_180930C != 34 )
  {
    if ( !unk_180930C )
      break;
    if ( ++v1 >= 199 )
      break;
    *(_BYTE *)off_663EFC = unk_180930C;
    off_663EFC = (_UNKNOWN *)((char *)off_663EFC + 1);
    rf_console_lexer_advance_character_percent_to_underscore();
  }
  rf_console_lexer_advance_character_percent_to_underscore();
  *(_BYTE *)off_663EFC = 34;
  result = (char *)off_663EFC + 1;
  off_663EFC = (_UNKNOWN *)((char *)off_663EFC + 1);
  *(_BYTE *)off_663EFC = 0;
  unk_1809924 = 3;
  return result;
}

