// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573470 rf_renderer_end_texture_residency_scope
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Backend102 delegates age/release handling with caller byte to texture cache. Clears bitmap load-context byte189744C. Unless backend104, invalidates all font atlas handles via58BF20. Return is last helper EAX/AL, not a uniform success contract.
char __cdecl rf_renderer_end_texture_residency_scope(char a1)
{
  char result; // al

  if ( dword_187CC9C == 102 )
    rf_d3d8_texture_cache_age_or_release_all(a1);
  result = rf_bitmap_set_load_context_byte(0);
  if ( dword_187CC9C != 104 )
    return rf_font_invalidate_all_atlas_bitmap_handles();
  return result;
}

