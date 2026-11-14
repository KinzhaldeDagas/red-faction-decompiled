// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B2090 rf_scene_cache_mark_all_retained
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): For each nonnull scene cache1D6CF28 entry below count1D6D24C, ORs definition DWORD304 with1 via5B7F10. Does not reset previous markers, counts or objects. EAX loop bookkeeping/undefined on empty list.
int rf_scene_cache_mark_all_retained()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_1D6D24C; ++i )
  {
    if ( (&unk_1D6CF28)[i] )
      rf_scene_definition_set_retained_flag1((&unk_1D6CF28)[i]);
    result = i + 1;
  }
  return result;
}

