// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587B80 rf_character_system_reset_cache_headers
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Calls reset-all-character headers5898A0 and reset800clipnames5BA450, then clears circular instance-list head18CDA28. Does not destroy existing instances/resources first. Returns clip reset loop value; not a verified boolean status.
int __cdecl rf_character_system_reset_cache_headers()
{
  int result; // eax

  rf_character_cache_reset_all_headers();
  result = rf_animation_clip_pool_reset_names();
  unk_18CDA28 = 0;
  return result;
}

