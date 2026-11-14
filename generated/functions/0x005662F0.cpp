// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005662F0 rf_model_resources_release_caches
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): False generic runtime label:releases entire V3C cache,entire scene-definition cache,then character cache entries without protected flag8,then named/owned animation-clip buffers. No handle enumeration, reference-count gate or retained-bit filtering for first two release-all calls. Raw return is final clip-pool helper result.
int rf_model_resources_release_caches()
{
  rf_v3c_asset_cache_release_all();
  rf_asset_cache1D6CF28_release_all();
  rf_character_cache_release_without_flag8();
  return rf_animation_clip_pool_release_named_owned_buffers();
}

