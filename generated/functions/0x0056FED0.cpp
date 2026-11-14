// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056FED0 rf_console_lexer_next_token
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl NO args; ECX entry value is not a receiver. Skips only space/tab,sets raw-token write cursor663EFC=18099F0 and initialNUL. Uses unsigned currentBYTE as index into256DWORD class table1809410. Class0/4 invokes ordinary accumulator;class1 quoted accumulator;class3 sets token kind0 without consuming end;other classes produce single-character token and advance,kind1. Then copies/casefolds into1809928 through56FFB0 and returns its incidental cursor pointer,not necessarily token base. Token buffers/current/cursors/type global and unsynchronized.
char *__cdecl rf_console_lexer_next_token()
{
  rf_console_lexer_skip_spaces_and_tabs();
  off_663EFC = unk_18099F0;
  unk_18099F0[0] = 0;
  switch ( unk_1809410[unk_180930C] )
  {
    case 0:
    case 4:
      rf_console_lexer_accumulate_ordinary_token();
      break;
    case 1:
      rf_console_lexer_accumulate_quoted_token();
      break;
    case 3:
      unk_1809924 = 0;
      break;
    default:
      *(_BYTE *)off_663EFC = unk_180930C;
      off_663EFC = (_UNKNOWN *)((char *)off_663EFC + 1);
      *(_BYTE *)off_663EFC = 0;
      rf_console_lexer_advance_character_percent_to_underscore();
      unk_1809924 = 1;
      break;
  }
  return rf_console_lexer_copy_and_fold_ascii_uppercase();
}

