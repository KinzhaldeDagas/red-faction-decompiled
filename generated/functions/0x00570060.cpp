// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570060 rf_console_lexer_accumulate_ordinary_token
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. While current char class0 or4,preincrements count then stops at count>=199 BEFORE copying/advancing. Stores at most198 bytes plusNUL in raw buffer and sets kind1. A199th eligible byte stays current for next token;there is no oversized-token error or truncation of all remaining input. Percent has already become underscore during advance. Returns write-end cursor incidentally.
void *rf_console_lexer_accumulate_ordinary_token()
{
  void *result; // eax
  int v1; // [esp+0h] [ebp-4h]

  v1 = 0;
  while ( !unk_1809410[unk_180930C] || unk_1809410[unk_180930C] == 4 )
  {
    if ( ++v1 >= 199 )
      break;
    *(_BYTE *)off_663EFC = unk_180930C;
    off_663EFC = (_UNKNOWN *)((char *)off_663EFC + 1);
    rf_console_lexer_advance_character_percent_to_underscore();
  }
  result = off_663EFC;
  *(_BYTE *)off_663EFC = 0;
  unk_1809924 = 1;
  return result;
}

