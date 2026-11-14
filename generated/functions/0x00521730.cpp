// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00521730 rf_world_decal_pool_abandon_lists
// UNREALRED VERIFIED [decal-projection-20261028]: Clears active/free heads and active count;128-iteration loop has no body. Releases scratch pointer-array backing0xA7063C and0xCFACA4. Does NOT iterate/recycle active decals, release attached polygons, rebuild free list or reset category counters. Use only under correct owning lifecycle; do not describe as full destruction.
void **rf_world_decal_pool_abandon_lists()
{
  int i; // [esp+0h] [ebp-4h]

  unk_A7051C = 0;
  unk_A70620 = 0;
  for ( i = 0; i < 128; ++i )
    ;
  unk_A70624 = 0;
  rf_pointer_array_release_storage((void **)unk_A7063C);
  return rf_pointer_array_release_storage((void **)&unk_CFACA4);
}

