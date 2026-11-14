// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045AC10 rf_console_team_say_chat
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Noarg registered team_say callback; same admission/drain as45AB90 but modeDWORD1. Require nonzero parsed
// count1809818,nonzero runtimeBYTE,nonempty raw argument Cstring1809810;invoke shared500ms throttle,then consume parser arguments with(-1,0) until mask1 set. No independent team-game
// check here,unlike interactive start45B470; transport/display delegates own audience. Failure of initial gates does not drain; rejected throttled send still drains. No own
// normalization,length cap,sound or buffer clear. Static registration62AAE0 verifies name team_say.
void rf_console_team_say_chat()
{
  if ( dword_1809818 && rf_multiplayer_runtime_mode && strlen((const char *)unk_1809810) )
  {
    rf_multiplayer_send_chat_with_500ms_throttle((char *)unk_1809810, 1);
    while ( (dword_1809308 & 1) == 0 )
      rf_console_read_argument_validate_type_mask(-1, 0);
  }
}

