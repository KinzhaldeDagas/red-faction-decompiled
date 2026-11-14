// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040FD30 rf_route_record_advance_next_index
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(required DWORD record), canonical EAX0 or-1. Snapshots old nextIndex=record DWORD+24, forms wrapped32 lastIndex=DWORD+0-1,
// then compares signed current DWORD+24 against lastIndex. If next>=last returns-1 WITHOUT any stores. Otherwise stores wrapped32 oldNext+1 at+24, then stores oldNext at DWORD+20,
// returns0. No array dereference, index>=0 check, route point copy or count mutation; signed negative indices and arithmetic wrap retain literal native behavior.
int __cdecl rf_route_record_advance_next_index(_DWORD *a1)
{
  int v2; // [esp+0h] [ebp-8h]

  v2 = a1[6];
  if ( v2 >= *a1 - 1 )
    return -1;
  a1[6] = v2 + 1;
  a1[5] = v2;
  return 0;
}

