// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005688D0 rf_ambient_voice_set_position
// UNREALRED VERIFIED [ambient-audio]: For a valid assigned frontend slot 0..24, updates its three-float position at +8.
float *__cdecl rf_ambient_voice_set_position(unsigned int a1, float *source)
{
  float *result; // eax
  float copy_result[3]; // [esp+0h] [ebp-10h] BYREF
  int *v4; // [esp+Ch] [ebp-4h]

  result = (float *)rf_sound_system_ready[0];
  if ( rf_sound_system_ready[0] )
  {
    v4 = &rf_ambient_voice_pool[6 * a1];
    if ( a1 <= 0x18 && *v4 >= 0 )
      return rf_vector_copy((float *)v4 + 2, copy_result, source);
  }
  return result;
}

