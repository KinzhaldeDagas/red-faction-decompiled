// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056FF80 rf_console_lexer_skip_spaces_and_tabs
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Repeatedly advances current character while exactly ASCII space32 or tab9;LF/CR and other whitespace are not skipped. Returns first other current byte as integer,without consuming it. Uses global cursor state.
int rf_console_lexer_skip_spaces_and_tabs()
{
  int result; // eax

  while ( 1 )
  {
    result = unk_180930C;
    if ( unk_180930C != 32 && unk_180930C != 9 )
      break;
    rf_console_lexer_advance_character_percent_to_underscore();
  }
  return result;
}

