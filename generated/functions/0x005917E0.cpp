// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005917E0 rf_command_line_initialize_from_process_string
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Cdecl validate-unknown-options byte. Gets GetCommandLineA process string, passes it DIRECTLY to5918C0 with caller validation byte and skip-first-logical-token=1, then registers cleanup591820 via atexit and returns atexit result. Tokenizer uses destructive strtok, so process command-line storage is modified in place. No copy, NULL handling, repeated-init guard, count reset or cleanup before parse; validation fatal can occur before atexit registration.
int __cdecl rf_command_line_initialize_from_process_string(char a1)
{
  LPSTR String; // [esp+4h] [ebp-4h]

  String = GetCommandLineA();
  rf_command_line_parse_match_and_optionally_validate(String, a1, 1);
  return atexit(rf_command_line_clear_arguments_preserve_option_registry);
}

