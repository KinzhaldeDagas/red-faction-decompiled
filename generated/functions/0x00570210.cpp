// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570210 rf_console_initialize_once_and_load_history
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl(saveHistoryByte). Only skips setup when initialized byte180A484 exactly1. Builds lexer class table5702D0,stores save-history flag663EE0,clears first text byte of500 ring slots and current prompt,sets prompt color fromdefault180A49C,write index0,scroll-1,animation0,cursor deadline+300 and cursor-on1. Loads history5703E0 REGARDLESS saveHistoryByte,then sets initialized1 and registers5704F0 withatexit. Does not reset visible byte,input string/cursor,registry or all record colors. Returns incidental existing init byte or atexit status; repeated direct init with corrupted non1 byte can register cleanup again.
int __cdecl rf_console_initialize_once_and_load_history(char a1)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = unk_180A484;
  if ( unk_180A484 != 1 )
  {
    rf_console_lexer_initialize_character_classes();
    byte_663EE0 = a1;
    for ( i = 0; i < 500; ++i )
      unk_180A5B0[261 * i] = 0;
    unk_180A4A0 = 0;
    unk_180A5A1 = unk_180A49C;
    dword_1809920 = 0;
    dword_1809ABC = -1;
    unk_180A485 = 0;
    rf_clock_deadline_set_wrapped_offset(&unk_180A5A8, 300);
    byte_180930D[0] = 1;
    rf_console_history_load_clamped_last_index();
    unk_180A484 = 1;
    return atexit(rf_console_atexit_save_history_and_clear_text);
  }
  return result;
}

