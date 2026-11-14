// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568780 rf_ambient_sound_resource_register
// UNREALRED VERIFIED [ambient-audio]: Registers an ambient sound resource with minimum distance, authored volume, and rolloff only while the sound system is ready; otherwise returns -1.
int __cdecl rf_ambient_sound_resource_register(char *filename, float distance, float volume, float scale)
{
  if ( rf_sound_system_ready[0] )
    return rf_sound_resource_load(filename, distance, volume, scale);
  else
    return -1;
}

