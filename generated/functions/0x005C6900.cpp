// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6900 rf_positional_sound_find_free_slot
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Scans all 128 instance slots for flags(+80) bit 1 clear and returns the first index, else -1. Does not reserve or reset the returned slot.
int rf_positional_sound_find_free_slot()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 128; ++i )
  {
    if ( (dword_1DAEEA8[27 * i] & 1) == 0 )
      return i;
  }
  return -1;
}

