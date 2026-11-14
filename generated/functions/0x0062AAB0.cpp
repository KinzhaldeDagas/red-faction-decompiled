// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062AAB0 rf_chat_send_deadline_static_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Recovered62AAB0..62AABF,lastRET62AABE. Noarg. Call clock_deadline_construct_invalid with ECX=&6F2CCC,leaving shared chat
// throttle disarmed according to verified clock constructor. No chat send,string construction,flag write or atexit registration. Separate from later500ms arming on accepted sends.
// Native function exact bytes/boundaries recovered.
void __cdecl rf_chat_send_deadline_static_construct()
{
  rf_clock_deadline_construct_invalid(&dword_6F2CCC);
}

