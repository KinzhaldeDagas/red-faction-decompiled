// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045AB90 rf_console_say_chat
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Noarg registered say callback. Require console parsed-argument count1809818 NONZERO, runtimeBYTE NONZERO (not exactly1), and
// raw argument Cstring pointed by1809810 nonempty after full scan. Call shared500ms chat throttle(text,0). Then repeatedly console_read_argument_validate_type_mask(-1,0) until parser
// flags1809308 mask1 set; drains remaining parser input even when throttle rejected send. Missing initial gate returns without drain. No explicit authority/local-player/source/length
// guard; does not concatenate individually parsed words or send each word. Original static registration62AAC0 binds command say.
void rf_console_say_chat()
{
  if ( dword_1809818 && rf_multiplayer_runtime_mode && strlen((const char *)unk_1809810) )
  {
    rf_multiplayer_send_chat_with_500ms_throttle((char *)unk_1809810, 0);
    while ( (dword_1809308 & 1) == 0 )
      rf_console_read_argument_validate_type_mask(-1, 0);
  }
}

