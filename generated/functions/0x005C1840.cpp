// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1840 rf_sound_query_duration_backend
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Unsigned soundID>=0xA28 (including-1)=>float0. Valid registered sound whose samplehandle+30 isnegative calls5C04C0 lazy load; load failure-1=>0. Otherwise duration is5916E0 RIFF-size/rate estimate. Native completed invalid/load-failure0 differs from host source-epoch/provider unavailability.
double __cdecl rf_sound_query_duration_backend(unsigned int a1)
{
  if ( a1 >= 0xA28 )
    return 0.0;
  if ( *(int *)&rf_sound_resource_registry[64 * a1 + 48] < 0 && rf_sound_load_entry(a1, 0, 0) == -1 )
    return 0.0;
  return rf_sound_sample_riff_size_rate_estimate(*(_DWORD *)&rf_sound_resource_registry[64 * a1 + 48]);
}

