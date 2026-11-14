// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DF630 rf_player_record_is_in_live_list
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): Cdecl candidate pointer. Walks circular global player list head87C324, comparing ADDRESS equality; returnsAL1 on first match, otherwise next==current head terminates and returns0. NULL head/candidate yields0 unless corrupt list semantics intervene. Does not dereference candidate or validate its entity, connection, local-entry registration, ownership or lifetime beyond list membership; no cycle-integrity guard.
char __cdecl rf_player_record_is_in_live_list(_DWORD *a1)
{
  _DWORD *v2; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  for ( i = (_DWORD *)dword_87C324; i; i = v2 )
  {
    if ( a1 == i )
      return 1;
    if ( *i == dword_87C324 )
      v2 = nullptr;
    else
      v2 = (_DWORD *)*i;
  }
  return 0;
}

