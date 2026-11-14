// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ACC70 rf_powerup_node_find_player_kind
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl(playerPointer,kind,outNodeOptional), bool in AL. Traverse root7B2548 circular list with next12 and root wrap termination. Return FIRST node whose DWORD0 equals
// playerPointer and DWORD4 equals kind. On hit, write node pointer only if output nonNULL and return1; on miss return0 WITHOUT clearing output. No pointer/kind validation, expiration
// test or list mutation; corrupt circular list not containing root can loop indefinitely.
char __cdecl rf_powerup_node_find_player_kind(int a1, int a2, _DWORD *a3)
{
  _DWORD *v4; // [esp+0h] [ebp-Ch]
  _DWORD *i; // [esp+8h] [ebp-4h]

  for ( i = (_DWORD *)unk_7B2548; ; i = v4 )
  {
    if ( !i )
      return 0;
    v4 = i[3] == unk_7B2548 ? nullptr : (_DWORD *)i[3];
    if ( *i == a1 && i[1] == a2 )
      break;
  }
  if ( a3 )
    *a3 = i;
  return 1;
}

