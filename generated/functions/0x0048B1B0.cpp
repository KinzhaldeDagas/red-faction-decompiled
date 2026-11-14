// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048B1B0 rf_mover_find_for_linked_object
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Cdecl common object pointer; NULL returnsNULL. Traverses mover list70489C..704610 via next652, scans each handle array704, compares stored DWORD directly with object's FULL
// handleDWORD44. Returns FIRST matching mover orNULL; no per-entry resolver or type check. Does not search array716, compare authored UID32, detach or compact arrays.
int __cdecl rf_mover_find_for_linked_object(int a1)
{
  int i; // [esp+0h] [ebp-8h]
  int j; // [esp+4h] [ebp-4h]

  if ( !a1 )
    return 0;
  for ( i = unk_70489C; (_UNKNOWN *)i != &unk_704610; i = *(_DWORD *)(i + 652) )
  {
    for ( j = 0; j < rf_receiver_get_first_dword((void *)(i + 704)); ++j )
    {
      if ( *(_DWORD *)sub_552200((_DWORD *)(i + 704), j) == *(_DWORD *)(a1 + 44) )
        return i;
    }
  }
  return 0;
}

