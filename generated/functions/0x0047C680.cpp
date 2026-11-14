// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047C680 rf_level_loading_network_poll_callback_a
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL header and prelude control flow, legacy light layouts, native ECX/stack arguments, environment initialization and multiplayer room tracking): 
// Cdecl no arguments; byte-for-byte equivalent logic to47C6A0. Loads multiplayer mode as unsigned byte and calls network_poll_udp_into_receive_queues only when EXACT1. Other mode
// values return raw mode EAX; exact1 returns delegate result. Does not process queued application messages here. Address referenced as callback at447C90; separate callback identity
// retained.
int rf_level_loading_network_poll_callback_a()
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 )
    return rf_network_poll_udp_into_receive_queues();
  return result;
}

