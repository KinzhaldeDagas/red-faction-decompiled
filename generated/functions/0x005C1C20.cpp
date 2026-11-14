// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1C20 rf_sound_resource_find_name_case_insensitive
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Scans indices 0..resource_count-1, compares each record filename with _stricmp, returns first matching index or -1. Does not register, load, check backend_ready, or normalize paths.
int __cdecl rf_sound_resource_find_name_case_insensitive(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_sound_resource_count; ++i )
  {
    if ( !_stricmp(&rf_sound_resource_registry[64 * i], String2) )
      return i;
  }
  return -1;
}

