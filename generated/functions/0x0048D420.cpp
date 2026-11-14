// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048D420 rf_banlist_contains_address
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ban-list validation and wildcard matching, native text-reader capacity and list ownership, multiplayer process initialization and character-cache ABI): 
// Cdecl pointer to address record. Native copies EIGHT bytes from input; only firstDWORD participates in ntohl then inet_ntoa, secondDWORD ignored afterward. No inputNULL guard. NULL
// text result returns0. Traverses ban records from704C74 to sentinel704C5C through next24; returns1 at FIRST pattern_match(record.inlineText0,convertedAddress),else0. Preserves exact
// native byte-order conversion sequence rather than assuming caller representation. No port comparison, list mutation or wildcard validation here.
int __cdecl rf_banlist_contains_address(u_long *a1)
{
  char *v2; // [esp+0h] [ebp-14h]
  u_long in; // [esp+4h] [ebp-10h]
  int i; // [esp+8h] [ebp-Ch]

  in = ntohl(*a1);
  v2 = inet_ntoa((struct in_addr)in);
  if ( !v2 )
    return 0;
  for ( i = unk_704C74; (_UNKNOWN *)i != &unk_704C5C; i = *(_DWORD *)(i + 24) )
  {
    if ( rf_ban_pattern_matches_ipv4_text((char *)i, v2) )
      return 1;
  }
  return 0;
}

