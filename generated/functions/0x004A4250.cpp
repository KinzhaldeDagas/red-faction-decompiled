// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A4250 rf_multiplayer_browser_query_callback
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(payload,source endpoint). Ignores first argument, forwards second to server_send_browser_info_packet1 and propagates EAX. No own checks. Original descriptor0 at662948 names
// game_info_request and points here; indirect dispatcher49FB50 supplies both DWORD arguments. Server-only admission resides in delegate.
int __cdecl rf_multiplayer_browser_query_callback(int a1, int a2)
{
  return rf_server_send_browser_info_packet1(a2);
}

