// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B2000 rf_asset_cache1D6CF28_release_all
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Loops global pointer cache1D6CF28 up to count1D6D24C; for nonnull entries calls5B7EE0(element,flags1), then zeros slot. Sets count0. Does not release pointer-array storage or inspect duplicate ownership; return incidental1/index/deleter bits. Exact element destructor retained by address because this pass does not infer an additional class layout.
int rf_asset_cache1D6CF28_release_all()
{
  int result; // eax
  int i; // [esp+Ch] [ebp-4h]

  result = 1;
  for ( i = 0; i < dword_1D6D24C; ++i )
  {
    result = i;
    if ( (&unk_1D6CF28)[i] )
    {
      result = (int)(&unk_1D6CF28)[i];
      if ( result )
        result = (int)rf_scene_definition_scalar_deleting_destructor((&unk_1D6CF28)[i], 1);
      (&unk_1D6CF28)[i] = nullptr;
    }
  }
  dword_1D6D24C = 0;
  return result;
}

