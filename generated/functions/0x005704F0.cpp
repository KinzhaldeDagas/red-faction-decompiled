// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005704F0 rf_console_atexit_save_history_and_clear_text
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Calls history save56E930,then clears ONLY first byte of each500 ring text records and current prompt. Does not clear initialization/visibility flags,history buffers,indices,colors,registry or font resources. Registered by570210;not a complete console teardown.
void __cdecl rf_console_atexit_save_history_and_clear_text()
{
  int i; // [esp+0h] [ebp-4h]

  rf_console_history_save_if_enabled();
  for ( i = 0; i < 500; ++i )
    unk_180A5B0[261 * i] = 0;
  unk_180A4A0 = 0;
}

