// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A230 rf_mover_find_by_key_uid
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Cdecl key UID. Traverses type8 mover list from70489C to sentinel704610 through next652, then each mover key-pointer vector668 in index order. Compares key DWORD0 with supplied UID;
// returns FIRST matching mover pointer orNULL. This differs from mover_find_by_saved_identifier and does not compare mover common id32/handle44. No key NULL guard, duplicate
// detection or mutation.
int __cdecl rf_mover_find_by_key_uid(int a1)
{
  int i; // [esp+0h] [ebp-8h]
  int j; // [esp+4h] [ebp-4h]

  for ( i = unk_70489C; (_UNKNOWN *)i != &unk_704610; i = *(_DWORD *)(i + 652) )
  {
    for ( j = 0; j < rf_receiver_get_first_dword((void *)(i + 668)); ++j )
    {
      if ( **(_DWORD **)sub_552200((_DWORD *)(i + 668), j) == a1 )
        return i;
    }
  }
  return 0;
}

