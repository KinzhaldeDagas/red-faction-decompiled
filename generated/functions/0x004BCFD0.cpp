// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BCFD0 rf_object_mark_for_deferred_delete
// UNREALRED VERIFIED [mission-when-dead-20261013] Sets common flags +0x7C bit 2 (pending delete); does NOT clear When_Dead blocker bit 0x00400000 or invalidate the common handle immediately.
int __cdecl rf_object_mark_for_deferred_delete(int a1)
{
  int result; // eax

  if ( a1 )
  {
    *(_DWORD *)(a1 + 124) |= 2u;
    return a1;
  }
  return result;
}

