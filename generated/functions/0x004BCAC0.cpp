// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BCAC0 rf_object_pool_delete_all_when_gate_set
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): No arguments. If global DWORD7B8E18 is zero, returns0 without traversing slots. Otherwise scans live global pointer table7B7E10 indices0..1023 ONCE in ascending order, immediately calls object-delete dispatcher for each currently nonnull slot, then sets gate7B8E18=0. Does not snapshot pointers, repeat until empty, filter protection/hidden flags, or provide uniform status (returns last dispatcher EAX or initial gate bits when no slots). Callback mutations can affect later slots; no unwind restoration or list/pool integrity check.
int *rf_object_pool_delete_all_when_gate_set()
{
  int *result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = (int *)unk_7B8E18;
  if ( unk_7B8E18 )
  {
    for ( i = 0; i < 1024; ++i )
    {
      if ( unk_7B7E10[i] )
        result = rf_object_delete_dispatch((_DWORD *)unk_7B7E10[i]);
    }
    unk_7B8E18 = 0;
  }
  return result;
}

