// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062AA90 rf_chat_input_string_static_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Recovered62AA90..62AAAC,lastRET62AAAB. Noarg. Construct empty RFString at6F2CDC,then register destructor callback62ECF0 with
// atexit. No active/init/mode/throttle writes or network/UI activation. Original constructor and atexit ABI native;return unspecified rather than constructor result. Function
// recovery preserves all original executable bytes.
void __cdecl rf_chat_input_string_static_construct()
{
  rf_string_construct_empty(unk_6F2CDC);
  atexit(rf_chat_input_string_atexit_destroy);
}

