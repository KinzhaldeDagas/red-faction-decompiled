// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005668F0 rf_model_caches_mark_all_retained
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Marks every nonnull V3C cache entry flag1,then scene definition flag1,then character cache retained state through its helper. Does not clear older retention marks, counts or slots; raw return final character helper. Later sweeps preserve records bearing corresponding markers.
int rf_model_caches_mark_all_retained()
{
  rf_v3c_cache_mark_all_retained();
  rf_scene_cache_mark_all_retained();
  return rf_character_cache_mark_all_retained();
}

