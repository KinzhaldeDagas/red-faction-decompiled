// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048DC70 rf_multiplayer_process_shutdown_banlist
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ban-list validation and wildcard matching, native text-reader capacity and list ownership, multiplayer process initialization and character-cache ABI): 
// Cdecl no arguments,ten-byte wrapper calling banlist_export_and_destroy_nodes48DA30 and returning delegate EAX. Called by application cleanup before backend shutdown. Does not
// independently tear down live player sessions, network sockets or character caches; those lifetimes belong to other routines.
int rf_multiplayer_process_shutdown_banlist()
{
  return rf_banlist_export_and_destroy_nodes();
}

