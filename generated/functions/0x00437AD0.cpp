// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437AD0 rf_mark_owned_class_flag40_objects_for_delete
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(owner pointer), canonical AL0/1. NULL owner returnsAL0. Scans global list head911F74 until
// sentinel911CE8, using each entry DWORD+652 as next link, loaded AFTER any deferred-delete delegate. For each entry whose owner full identifier DWORD+48 equals input owner
// fullhandle44 AND entry class(+660) DWORD+612 mask0x40 set, calls4BCFD0(entry), then remembers result1. Visits ALL matches, no first-match exit or
// pending-delete/live/type/reciprocity test; already-marked entries still count. ReturnsAL1 iff at least one matching mark was requested, independent of delegate result.
// Mark-for-delete is deferred, not synchronous destruction/unlink. No input type/self/negative-handle guard or own list-integrity check.
char __cdecl rf_mark_owned_class_flag40_objects_for_delete(int a1)
{
  char v2; // [esp+3h] [ebp-5h]
  int i; // [esp+4h] [ebp-4h]

  if ( !a1 )
    return 0;
  v2 = 0;
  for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 48) == *(_DWORD *)(a1 + 44) && (*(_DWORD *)(*(_DWORD *)(i + 660) + 612) & 0x40) != 0 )
    {
      rf_object_mark_for_deferred_delete(i);
      v2 = 1;
    }
  }
  return v2;
}

