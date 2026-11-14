// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C7520 rf_positional_sound_set_base_frequency
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): For signed index in [0,127], writes frequency to slot+32. No initialized, allocated, range-of-frequency or backend check. Does not change a playing voice directly; Doppler update may later use this base.
void __cdecl rf_positional_sound_set_base_frequency(int instance_index, int frequency)
{
  if ( (unsigned int)instance_index < 0x80 )
    unk_1DAEE58[27 * instance_index + 8] = frequency;
}

