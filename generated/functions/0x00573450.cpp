// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573450 rf_renderer_begin_texture_residency_scope
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Backend102 increments texture-cache resident ages. Then writes bitmap load-context byte189744C=1 through573F10 for every backend and returns that byte. No texture load is performed directly.
char rf_renderer_begin_texture_residency_scope()
{
  if ( dword_187CC9C == 102 )
    rf_d3d8_texture_cache_increment_resident_ages();
  return rf_bitmap_set_load_context_byte(1);
}

