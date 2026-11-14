// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567FB0 rf_gamesound_resolve_and_load
// Resolves a UI game-sound event ID to its positional table entry and lazily loads the referenced sound.
// UNREALRED VERIFIED [sound-backend]: Resolves a game-sound event to its registered 64-byte resource record and performs lazy resource loading before voice admission.
int __cdecl rf_gamesound_resolve_and_load(int a1)
{
  if ( !rf_sound_system_ready )
    return -1;
  if ( !unk_1D85DF5[64 * a1] )
  {
    if ( rf_sound_load_entry(a1, 0, 0) < 0 )
      return -1;
    unk_1D85DF5[64 * a1] = 1;
  }
  return 0;
}

