// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062AAE0 rf_console_register_team_say_command
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Recovered62AAE0..62AAFE,lastRET62AAFD. Noarg. Console command record6F2CE4: register_sorted(name="team_say"
// original63610C,description original6360D8,callback45AC10). Native cdecl-like stack arguments plus ECXrecord as registration ABI. Does not query team mode or execute callback;sender
// admission occurs later. Original PE string/callback binding and exact native boundaries verified.
void __cdecl rf_console_register_team_say_command()
{
  rf_console_command_record_register_sorted(
    dword_6F2CE4,
    "team_say",
    (int)"Sends a chat message to other players on your team",
    (int)rf_console_team_say_chat);
}

