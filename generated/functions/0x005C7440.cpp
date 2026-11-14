// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C7440 rf_positional_sound_suspend
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Requires initialized, index in [0,127], and allocated flag 1. Sets suspended bit 2, caches gain zero at +16, and stops current voice with fade 0. Does not unlink or free the instance. The XOR EAX,EAX / JNZ sequence on the unallocated path cannot loop because XOR sets ZF=1.
void __cdecl rf_positional_sound_suspend(int instance_index)
{
  if ( byte_1DAEE54 && (unsigned int)instance_index < 0x80 && (dword_1DAEEA8[27 * instance_index] & 1) != 0 )
  {
    dword_1DAEEA8[27 * instance_index] |= 2u;
    *((float *)&unk_1DAEE68 + 27 * instance_index) = 0.0;
    rf_positional_sound_stop_voice(instance_index, 0);
  }
}

