// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C17D0 rf_sound_resource_get_record_out
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): If unsigned index>=2600 returns -1 without writing output. Otherwise writes registry+64*index to the output pointer and returns 0. Unlike 5C1700, does not test backend_ready or record population; output pointer must be valid.
int __cdecl rf_sound_resource_get_record_out(unsigned int a1, _DWORD *a2)
{
  if ( a1 >= 0xA28 )
    return -1;
  *a2 = &rf_sound_resource_registry[64 * a1];
  return 0;
}

