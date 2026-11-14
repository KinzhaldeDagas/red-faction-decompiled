// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0480 rf_sound_resource_unregister
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): When ready and index != -1, invokes release_if_unpinned and clears record filename[0]. A pinned record can therefore lose its name while retaining the loaded backend reference. No general 0..2599 bounds check; EAX is incidental.
char *__cdecl rf_sound_resource_unregister(int a1)
{
  char *result; // eax

  result = (char *)rf_sound_backend_ready;
  if ( rf_sound_backend_ready )
  {
    if ( a1 != -1 )
    {
      result = rf_sound_resource_release_if_unpinned(a1);
      rf_sound_resource_registry[64 * a1] = 0;
    }
  }
  return result;
}

