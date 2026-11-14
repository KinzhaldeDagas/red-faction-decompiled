// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B20F0 rf_scene_cache_remove_pointer_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Scene equivalent:find first exact pointer,delete via5B7EE0 flags1,zero/shift entries. ALWAYS writesNULL at cache[oldCount],then decrements reloaded global count even on not-found/empty input. New logical tail slot not cleared; no retained flag, ownership or existing-instance protection. Do not substitute safe remove-if-present behavior.
int __cdecl rf_scene_cache_remove_pointer_unchecked(char *a1)
{
  int result; // eax
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < dword_1D6D24C; ++i )
  {
    if ( (&unk_1D6CF28)[i] == a1 )
    {
      if ( (&unk_1D6CF28)[i] )
        rf_scene_definition_scalar_deleting_destructor((&unk_1D6CF28)[i], 1);
      (&unk_1D6CF28)[i] = nullptr;
      break;
    }
  }
  while ( 1 )
  {
    result = dword_1D6D24C - 1;
    if ( i >= dword_1D6D24C - 1 )
      break;
    (&unk_1D6CF28)[i] = (char *)unk_1D6CF2C[i];
    ++i;
  }
  (&unk_1D6CF28)[dword_1D6D24C--] = nullptr;
  return result;
}

