// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005915E0 rf_audio_set_3d_mode_byte_raw
// UNREALRED VERIFIED [dsound-playback-20261028]: Stores arbitrary callerbyte in0x193BBE0 andreturns it. Does not create/release listener orbuffers,rebuild lookup tables,validate device support or alter overall initialized flag.
char __cdecl rf_audio_set_3d_mode_byte_raw(char a1)
{
  unk_193BBE0 = a1;
  return a1;
}

