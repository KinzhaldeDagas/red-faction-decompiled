// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005213D0 rf_world_decal_pool_clear_level
// UNREALRED VERIFIED [resource-pools-20261028]: Calls0x5213F0 to recycle decals except protected flag0x400, then releases pointer-array backing at0xA7063C and0xCFACA4. Protected decals can remain active. Does not reset entire fixed pool or individually free array pointees here.
void **rf_world_decal_pool_clear_level()
{
  rf_world_decal_recycle_unprotected();
  rf_pointer_array_release_storage((void **)unk_A7063C);
  return rf_pointer_array_release_storage((void **)&unk_CFACA4);
}

