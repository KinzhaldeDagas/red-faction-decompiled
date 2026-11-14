// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C7010 rf_positional_sound_destroy_instance
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Returns -1 when the subsystem is uninitialized. Otherwise, if flags bit 1 is set, stops/fades the voice, unlinks prev/next, clears both links and resets slot fields. Returns 0 for both a destroyed and an already-unallocated slot. No index bounds check before reading flags.
int __cdecl rf_positional_sound_destroy_instance(int a1, int a2)
{
  if ( !byte_1DAEE54 )
    return -1;
  if ( (dword_1DAEEA8[27 * a1] & 1) != 0 )
  {
    rf_positional_sound_stop_voice(a1, a2);
    *(_DWORD *)unk_1DAEE5C[27 * a1] = unk_1DAEE58[27 * a1];
    *(_DWORD *)(unk_1DAEE58[27 * a1] + 4) = unk_1DAEE5C[27 * a1];
    unk_1DAEE58[27 * a1] = 0;
    unk_1DAEE5C[27 * a1] = 0;
    rf_positional_sound_instance_reset(a1);
  }
  return 0;
}

