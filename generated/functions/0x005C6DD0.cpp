// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6DD0 rf_positional_sound_instances_initialize_once
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): If byte 1DAEE54==1, returns 0. Otherwise initializes the sentinel at 1DB2458/1DB245C to self-linked pointers, resets 128 instance slots via 5C68B0, clears active voice count 1DAEE50, sets the once flag, and returns 0.
int rf_positional_sound_instances_initialize_once()
{
  int i; // [esp+0h] [ebp-4h]

  if ( byte_1DAEE54 == 1 )
    return 0;
  dword_1DB2458 = &dword_1DB2458;
  unk_1DB245C = &dword_1DB2458;
  for ( i = 0; i < 128; ++i )
    rf_positional_sound_instance_reset(i);
  dword_1DAEE50 = 0;
  byte_1DAEE54 = 1;
  return 0;
}

