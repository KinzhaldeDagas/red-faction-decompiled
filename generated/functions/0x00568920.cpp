// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568920 rf_sound_query_duration
// UNREALRED VERIFIED [sound-backend]: Resolves and lazy-loads one sound event, then returns the backend-reported duration for its registered resource.
double __cdecl rf_sound_query_duration(unsigned int a1)
{
  if ( rf_sound_system_ready[0] )
    return rf_sound_query_duration_backend(a1);
  else
    return 0.0;
}

