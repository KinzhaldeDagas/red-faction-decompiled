// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E1B50 rf_d3d8_texture_cache_destroy_array
// UNREALRED VERIFIED [image-headers-20261028]: Calls0x5E1860(force1), deletes array0x1E01548, sets global array pointer null. Does not reset slot count or stage cache storage. Force helper makes unconditional device call, so destruction requires a valid device despite its initial unbind guard.
void rf_d3d8_texture_cache_destroy_array()
{
  rf_d3d8_texture_cache_age_or_release_all(1);
  operator delete(dword_1E01548);
  dword_1E01548 = nullptr;
}

