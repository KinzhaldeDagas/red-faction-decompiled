// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0700 rf_sound_resource_release_if_unpinned
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): When ready and index != -1, inspects the 64-byte record. If pin byte +63 is zero and backend sample index +48 >=0, mode 1 releases its sample reference, then all modes set +48=-1 and clear byte +61. Does not clear filename or pin flag; no general bounds check.
char *__cdecl rf_sound_resource_release_if_unpinned(int a1)
{
  char *result; // eax
  char *v2; // [esp+4h] [ebp-4h]

  result = (char *)rf_sound_backend_ready;
  if ( rf_sound_backend_ready )
  {
    if ( a1 != -1 )
    {
      v2 = &rf_sound_resource_registry[64 * a1];
      result = (char *)(unsigned __int8)v2[63];
      if ( !v2[63] && *((int *)v2 + 12) >= 0 )
      {
        if ( rf_sound_backend_mode == 1 )
          rf_sound_sample_release_reference(*((_DWORD *)v2 + 12));
        *((_DWORD *)v2 + 12) = -1;
        v2[61] = 0;
        return &rf_sound_resource_registry[64 * a1];
      }
    }
  }
  return result;
}

