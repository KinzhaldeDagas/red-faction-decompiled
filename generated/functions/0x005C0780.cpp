// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0780 rf_sound_resources_release_all_unpinned
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): When ready, calls release_if_unpinned for all 2600 slots, including unnamed records. Does not reset resource_count.
char *rf_sound_resources_release_all_unpinned()
{
  char *result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = (char *)rf_sound_backend_ready;
  if ( rf_sound_backend_ready )
  {
    for ( i = 0; i < 2600; ++i )
      result = rf_sound_resource_release_if_unpinned(i);
  }
  return result;
}

