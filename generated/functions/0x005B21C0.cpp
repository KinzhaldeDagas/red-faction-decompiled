// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B21C0 rf_scene_cache_release_unretained
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Same sweep/compaction policy on scene cache1D6CF28,testing definition DWORD304&1. Deletes unmarked through5B7EE0 flags1,keeps marked in source order without clearing marker. Count decremented only for deleted nonnull entries,not preexistingNULL holes. No runtime-instance invalidation or shared-reference accounting.
int rf_scene_cache_release_unretained()
{
  int result; // eax
  int v1; // [esp+Ch] [ebp-Ch]
  int i; // [esp+10h] [ebp-8h]
  int v3; // [esp+14h] [ebp-4h]

  v3 = 0;
  v1 = 0;
  for ( i = 0; i < dword_1D6D24C; ++i )
  {
    if ( (&unk_1D6CF28)[i] )
    {
      if ( rf_scene_definition_test_retained_flag1((&unk_1D6CF28)[i]) )
      {
        if ( v1 < i )
        {
          (&unk_1D6CF28)[v1] = (&unk_1D6CF28)[i];
          (&unk_1D6CF28)[i] = nullptr;
        }
        ++v1;
      }
      else
      {
        if ( (&unk_1D6CF28)[i] )
          rf_scene_definition_scalar_deleting_destructor((&unk_1D6CF28)[i], 1);
        (&unk_1D6CF28)[i] = nullptr;
        ++v3;
      }
    }
    result = i + 1;
  }
  dword_1D6D24C -= v3;
  return result;
}

