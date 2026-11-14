// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062AAC0 rf_console_register_say_command
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Recovered62AAC0..62AADE,lastRET62AADD. Noarg. Console command record at6F2CD0: register_sorted(name="say"
// original6360D4,description original6360A8,callback45AB90). Native push callback,description,name thenECXrecord;callee owns registration storage/list. No callback execution,message
// send or argument parsing in initializer. Distinct record from team_say. Original PE strings and native callback pointer verified.
void __cdecl rf_console_register_say_command()
{
  rf_console_command_record_register_sorted(
    dword_6F2CD0,
    (char *)&off_6360D4,
    (int)"Sends a chat message to all other players",
    (int)rf_console_say_chat);
}

