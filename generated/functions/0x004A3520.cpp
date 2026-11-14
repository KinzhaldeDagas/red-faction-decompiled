// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A3520 rf_server_validate_join_request
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(endpoint,request record). Ordered first-failure reasons:5 unless runtime1/authority exactly1;10 if banlist contains address;1 if signed current player count>=signed
// max704EDC;5 if game flags mask2 clear;3 if configured password RFString704EC8 nonempty and differs CASE-INSENSITIVELY from request RFString+0. Empty password constant63A91F
// verified against original PE.
// Then scans ALL players (including local/pending), with no net-null guard, and returns4 when network_compare_endpoints(playerNet,endpoint,1)==0: strict endpoint including port.
// Finally compares2 pairs of DWORD signatures request+20/+28 to88E674/88E67C, returns7 at first mismatch. Returns0 only after all checks. No state mutation, string-length validation
// or player-name policy. Pending join IP-only filter in client accept is a separate, weaker check.
int __cdecl rf_server_validate_join_request(u_long *a1, int a2)
{
  _DWORD *v3; // [esp+0h] [ebp-10h]
  int j; // [esp+4h] [ebp-Ch]
  _DWORD *i; // [esp+Ch] [ebp-4h]

  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority != 1 )
    return 5;
  if ( rf_banlist_contains_address(a1) )
    return 10;
  if ( rf_player_runtime_list_count() >= *(int *)unk_704EDC )
    return 1;
  if ( (rf_multiplayer_game_flags & 2) == 0 )
    return 5;
  if ( rf_rf_string_not_equals_cstring_case_insensitive((int)dword_704EC8, (char *)&byte_63A91F)
    && rf_string_not_equals_case_insensitive((int)dword_704EC8, a2) )
  {
    return 3;
  }
  for ( i = (_DWORD *)dword_87C324; i; i = v3 )
  {
    if ( *i == dword_87C324 )
      v3 = nullptr;
    else
      v3 = (_DWORD *)*i;
    if ( !rf_network_compare_endpoints(i[1152], (int)a1, 1) )
      return 4;
  }
  for ( j = 0; j < 2; ++j )
  {
    if ( *(_DWORD *)(a2 + 4 * j + 20) != unk_88E674[j] || *(_DWORD *)(a2 + 4 * j + 28) != unk_88E67C[j] )
      return 7;
  }
  return 0;
}

