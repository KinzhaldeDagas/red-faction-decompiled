// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C74C0 rf_positional_sound_resume
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Requires initialized, index in [0,127], and allocated flag 1. Clears suspended bit 2. Does not start playback immediately; a subsequent eligible update may restart it.
void __cdecl rf_positional_sound_resume(int instance_index)
{
  if ( byte_1DAEE54 && (unsigned int)instance_index < 0x80 && (dword_1DAEEA8[27 * instance_index] & 1) != 0 )
    dword_1DAEEA8[27 * instance_index] &= ~2u;
}

