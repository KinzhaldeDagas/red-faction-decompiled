// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568000 sub_568000
// UNREALRED VERIFIED [persona-lifecycle-20260923]: Persona sound helper saves the backend mode byte via 0x5915B0, sets it to zero via 0x5915E0, calls rf_gamesound_play_event, restores the saved byte, and returns the voice handle. The semantic meaning of that backend flag is not established here; do not infer a 2D/3D label from the caller alone.
int __cdecl sub_568000(int a1, int a2, float a3, float a4)
{
  int v5; // [esp+8h] [ebp-8h]
  char _3d_mode_byte; // [esp+Fh] [ebp-1h]

  _3d_mode_byte = rf_audio_get_3d_mode_byte();
  rf_audio_set_3d_mode_byte_raw(0);
  v5 = rf_gamesound_play_event(a1, a2, a3, a4);
  rf_audio_set_3d_mode_byte_raw(_3d_mode_byte);
  return v5;
}

