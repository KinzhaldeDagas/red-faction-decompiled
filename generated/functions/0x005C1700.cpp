// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1700 rf_sound_resource_get_record_if_ready
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Returns the 64-byte record pointer only when backend ready and unsigned index<2600, otherwise NULL. Does not require the filename or backend sample to be populated.
char *__cdecl rf_sound_resource_get_record_if_ready(unsigned int a1)
{
  if ( !rf_sound_backend_ready )
    return nullptr;
  if ( a1 >= 0xA28 )
    return nullptr;
  return &rf_sound_resource_registry[64 * a1];
}

