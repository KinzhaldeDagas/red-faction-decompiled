// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005918C0 rf_command_line_parse_match_and_optionally_validate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Cdecl mutable input string, validate-unknown byte, skip-first-logical-token byte. Calls tokenizer5918F0, then registered-option matcher591C40, then unknown-dash validator591E80 only if validation byte nonzero. Does not clear previous option argument/matched state or reset token count before parsing. Validation is separate from required-argument capture diagnostics.
void __cdecl rf_command_line_parse_match_and_optionally_validate(char *String, char a2, char a3)
{
  rf_command_line_tokenize_in_place_with_quote_grouping(String, a3);
  rf_command_line_match_registered_options();
  if ( a2 )
    rf_command_line_fatal_on_unrecognized_dash_options();
}

