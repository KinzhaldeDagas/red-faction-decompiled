// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048D590 rf_banlist_append_address
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ban-list validation and wildcard matching, native text-reader capacity and list ownership, multiplayer process initialization and character-cache ABI): 
// Cdecl address-record pointer. Copies input first8 bytes locally; transforms firstDWORD with ntohl then inet_ntoa,ignores copied secondDWORD. Nonnull returned Cstring passed to
// append_unique_text48D4A0; NULL skips. No inputNULL guard, separate validity test, port handling or immediate file export. Preserves original conversion sequence shared with
// contains_address.
void __cdecl rf_banlist_append_address(u_long *a1)
{
  char *String1; // [esp+0h] [ebp-10h]
  u_long in; // [esp+4h] [ebp-Ch]

  in = ntohl(*a1);
  String1 = inet_ntoa((struct in_addr)in);
  if ( String1 )
    rf_banlist_append_unique_text(String1);
}

