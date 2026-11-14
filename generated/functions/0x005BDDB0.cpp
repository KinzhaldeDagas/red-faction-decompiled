// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BDDB0 rf_scene_effects_enable_named_source_cache
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Writes global DWORD1D85DAC=1,then calls rf_named_source_cache_enable_and_clear_head and forwards its incidental EAX. Does not allocate particle pools,walk loaded instances or release previous cache entries itself. Exact role of first global beyond enable-like initialization remains unproven.
int rf_scene_effects_enable_named_source_cache()
{
  unk_1D85DAC = 1;
  return rf_named_source_cache_enable_and_clear_head();
}

