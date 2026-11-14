// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA370 rf_animation_clip_acquire_registry_entry
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Calls get-or-create5BA0D0 then increments DWORD+112 and returns entry. This is character-registration counter, DISTINCT from instance-action reference count+116 managed by5BA400/420. No failure, overflow or capacity guard; get-or-create can fault on full pool.
char *__cdecl rf_animation_clip_acquire_registry_entry(char *a1)
{
  char *result; // eax

  result = rf_animation_clip_pool_get_or_create(a1);
  ++*((_DWORD *)result + 28);
  return result;
}

