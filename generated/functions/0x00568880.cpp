// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568880 rf_ambient_voice_set_source_gain
// UNREALRED VERIFIED [ambient-audio]: For a valid assigned frontend slot 0..24, updates only its live source-gain field at +20.
int *__cdecl rf_ambient_voice_set_source_gain(unsigned int a1, float a2)
{
  int *result; // eax
  int *v3; // [esp+0h] [ebp-4h]

  result = (int *)rf_sound_system_ready[0];
  if ( rf_sound_system_ready[0] )
  {
    v3 = &rf_ambient_voice_pool[6 * a1];
    if ( a1 <= 0x18 && *v3 >= 0 )
    {
      *((float *)v3 + 5) = a2;
      return &rf_ambient_voice_pool[6 * a1];
    }
  }
  return result;
}

