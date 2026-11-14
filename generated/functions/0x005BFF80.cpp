// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BFF80 rf_sound_resource_registry_initialize_once
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): If byte 1DAE7CD is not exactly 1, initializes all 2600 64-byte records: backend sample index +48=-1, filename first byte +0=0, byte +60=0; then sets the once flag to 1. Does not initialize every field or reset resource_count. EAX is incidental.
int rf_sound_resource_registry_initialize_once()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = byte_1DAE7CD[0];
  if ( byte_1DAE7CD[0] != 1 )
  {
    for ( i = 0; i < 2600; ++i )
    {
      unk_1D85DE8[16 * i] = -1;
      result = i << 6;
      rf_sound_resource_registry[64 * i] = 0;
      unk_1D85DF4[64 * i] = 0;
    }
    byte_1DAE7CD[0] = 1;
  }
  return result;
}

