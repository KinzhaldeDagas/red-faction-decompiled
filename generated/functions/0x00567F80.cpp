// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567F80 rf_sound_resource_load
// UNREALRED VERIFIED [combat-speech-providers-20261111]: Thin resource registration adapter calls5C0220 with filename,minDistance,volume,rolloff and final option0. Resource identity and registration failure belong to5C0220; it is not tuple-based interning or lazy PCM decode.
int __cdecl rf_sound_resource_load(const char *filename, float distance, float volume, float scale)
{
  return rf_sound_find_or_register((char *)filename, distance, volume, scale, 0);
}

