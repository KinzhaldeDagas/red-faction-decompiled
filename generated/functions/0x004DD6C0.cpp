// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DD6C0 rf_players_destroy_all_except_local_record
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): No arguments. Traverses circular player list from current head87C324, snapshots next before possible delete; next==CURRENT global head becomesNULL terminator. Destroys every record whose ADDRESS differs from global local-player pointer through full unlink/network/resource cleanup4DD4D0. Keeps local record regardless of entity, ID, state or network connection. No shared presentation shutdown or explicit global-local-pointer clear. EAX is traversal/destructor residue (possibly freed pointer), not count/status.
char *rf_players_destroy_all_except_local_record()
{
  char *result; // eax
  char *v1; // [esp+0h] [ebp-Ch]
  char *i; // [esp+8h] [ebp-4h]

  result = (char *)dword_87C324;
  for ( i = (char *)dword_87C324; i; i = v1 )
  {
    if ( *(_DWORD *)i == dword_87C324 )
      v1 = nullptr;
    else
      v1 = *(char **)i;
    result = i;
    if ( i != (char *)rf_local_fpgun_player )
      result = rf_player_unlink_close_and_destroy_record(i);
  }
  return result;
}

