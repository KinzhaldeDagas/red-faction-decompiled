// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0053A0A0 rf_procedural_bitmap_system_clear
// UNREALRED VERIFIED [resource-pools-20261028]: Releases all active procedural bitmap records through0x539F70, then invokes0x552EC0 to scalar-delete records in auxiliary array0x15A7148 and release backing when count>0. Pool records themselves remain fixed allocations.
void **rf_procedural_bitmap_system_clear()
{
  _DWORD *i; // [esp+0h] [ebp-4h]

  for ( i = (_DWORD *)unk_142665C; i; i = (_DWORD *)unk_142665C )
    rf_procedural_bitmap_record_release(i);
  return rf_lightmap_atlas_destroy_all_registered_pages();
}

