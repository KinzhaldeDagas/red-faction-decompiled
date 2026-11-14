// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475CE0 rf_ambient_sound_enable_by_uid
// UNREALRED VERIFIED [world-uid-ownership]: Resolves an ambient-sound UID and restores its runtime handle scalar from authored record +0x2C; returns false when absent.
// UNREALRED VERIFIED [ambient-audio]: Finds one persistent record and restores its live frontend source gain from authored volume +44. An unassigned slot produces no frontend mutation.
char __cdecl rf_ambient_sound_enable_by_uid(int a1)
{
  int *v2; // [esp+4h] [ebp-4h]

  v2 = rf_ambient_sound_find_by_uid(a1);
  if ( !v2 )
    return 0;
  rf_ambient_voice_set_source_gain(v2[4], *((float *)v2 + 11));
  return 1;
}

