// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C7550 rf_positional_sound_get_base_frequency
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Returns slot+32 for signed index in [0,127], otherwise 11025. Does not test initialization or allocation. Reset does not initialize +32, so unused slots may retain an older value.
int __cdecl rf_positional_sound_get_base_frequency(int instance_index)
{
  if ( (unsigned int)instance_index < 0x80 )
    return unk_1DAEE58[27 * instance_index + 8];
  else
    return 11025;
}

