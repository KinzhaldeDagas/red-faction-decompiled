// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005761C0 rf_bitmap_hash_insert_record_pointer
// UNREALRED VERIFIED [bitmap-loading-20261028]: Arguments initialized record pointer with hash DWORD+32. Linear probes table0x189734C at signed hash%(slotcount+1), incrementing until null, then stores record pointer. Returns table base, not insertion index. No duplicate lookup, table-full bound, tombstone or negative-hash correction. Does not copy name or compute hash.
void *__cdecl rf_bitmap_hash_insert_record_pointer(int a1)
{
  void *result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = *(_DWORD *)(a1 + 32); *((_DWORD *)dword_189734C + i % (dword_663F14 + 1)); ++i )
    ;
  result = dword_189734C;
  *((_DWORD *)dword_189734C + i % (dword_663F14 + 1)) = a1;
  return result;
}

