// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047C6A0 rf_level_loading_network_poll_callback_b
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL header and prelude control flow, legacy light layouts, native ECX/stack arguments, environment initialization and multiplayer room tracking): 
// Cdecl no arguments; equivalent logic to47C680 with distinct callback address referenced447CA8. Mode unsigned BYTE EXACT1 invokes network_poll_udp_into_receive_queues; otherwise
// returns raw mode EAX. No authority check or queued application-message dispatch in wrapper.
int rf_level_loading_network_poll_callback_b()
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 )
    return rf_network_poll_udp_into_receive_queues();
  return result;
}

