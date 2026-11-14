// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005915C0 rf_audio_get_property_extension_mode_byte
// UNREALRED VERIFIED [dsound-playback-20261028]: Returns raw globalbyte0x193BBE2. No readiness/capability check or normalization. Extension initializer0x598950 uses nonzero; device init starts extension only ifbyte==1.
char rf_audio_get_property_extension_mode_byte()
{
  return unk_193BBE2;
}

