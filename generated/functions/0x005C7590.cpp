// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C7590 rf_positional_sound_get_resource_index
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Returns slot resource index +8 for signed index in [0,127], otherwise -1. No initialized or allocated flag check; reset sets this field to -1.
int __cdecl rf_positional_sound_get_resource_index(int instance_index)
{
  if ( (unsigned int)instance_index < 0x80 )
    return dword_1DAEE60[27 * instance_index];
  else
    return -1;
}

