// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475CA0 rf_ambient_sound_disable_by_uid
// UNREALRED VERIFIED [world-uid-ownership]: Resolves an ambient-sound UID and sets its runtime handle scalar to 0.0; returns false when the UID is absent.
// UNREALRED VERIFIED [ambient-audio]: Finds one persistent record and writes 0.0 only to its live frontend source gain. The authored volume at record +44 is preserved; an unassigned slot produces no frontend mutation.
char __cdecl rf_ambient_sound_disable_by_uid(int a1)
{
  int *v2; // [esp+4h] [ebp-4h]

  v2 = rf_ambient_sound_find_by_uid(a1);
  if ( !v2 )
    return 0;
  rf_ambient_voice_set_source_gain(v2[4], 0.0);
  return 1;
}

