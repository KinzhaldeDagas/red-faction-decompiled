// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566910 rf_model_caches_release_unretained
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Runs V3C sweep5B9E00,scene-definition sweep5B21C0,then character release-unretained helper. No handle/instance invalidation or clearing of retained bits by this dispatcher. Returns final delegate bits.
int rf_model_caches_release_unretained()
{
  rf_v3c_cache_release_unretained();
  rf_scene_cache_release_unretained();
  return rf_character_cache_release_unretained();
}

