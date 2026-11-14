// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BEB80 rf_collision_pair_try_enqueue
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Cdecl(objectA,objectB), AL1 enqueued/0 rejected or exhausted. Starts local flags DWORD0, calls full skip filter4BEC10(A,B,&flags); nonzero filter rejects. Free-list header813C18 must have nonnull head; getter called twice. Removes first free node through generic remove helper, prepends to active header813BD0, THEN writes pair object pointers+4/+8 and flags+12. No duplicate-pair scan, payload reset, allocation/heap fallback, locking or failure rollback. Filter can change local flags even on rejection; rejected local flags are discarded. Does not itself resolve handles or run physical collision response.
char __cdecl rf_collision_pair_try_enqueue(int a1, int a2)
{
  _DWORD *first_dword; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h] BYREF

  v4 = 0;
  if ( rf_collision_pair_should_skip(a1, a2, &v4) )
    return 0;
  if ( !rf_receiver_get_first_dword(dword_813C18) )
    return 0;
  first_dword = (_DWORD *)rf_receiver_get_first_dword(dword_813C18);
  rf_intrusive_slist_remove_search_unchecked_count(dword_813C18, first_dword);
  rf_intrusive_slist_push_front(dword_813BD0, first_dword);
  first_dword[1] = a1;
  first_dword[2] = a2;
  first_dword[3] = v4;
  return 1;
}

