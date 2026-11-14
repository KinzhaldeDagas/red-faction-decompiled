// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056DC00 rf_console_lexer_set_input_and_prime
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl(inputPointer). Stores pointer663EF8 then immediately calls56DC20 to populate current byte180930C and advance pointer past it. NULL input not checked. AL return is helper incidental value,not guaranteed current normalized character,especially at end-of-input.
char __cdecl rf_console_lexer_set_input_and_prime(void *a1)
{
  off_663EF8 = a1;
  return rf_console_lexer_advance_character_percent_to_underscore();
}

