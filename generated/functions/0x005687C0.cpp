// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005687C0 rf_ambient_voice_reserve_frontend_slot
// UNREALRED VERIFIED [ambient-audio]: Scans exactly 25 frontend ambient slots for the first free record, stores sound handle, position, and source gain, initializes backend voice to -1, and returns the slot index. Reservation does not start backend playback.
int __cdecl rf_ambient_voice_reserve_frontend_slot(unsigned int a1, float *source, float a3)
{
  float copy_result[3]; // [esp+0h] [ebp-18h] BYREF
  int v5; // [esp+Ch] [ebp-Ch]
  int i; // [esp+10h] [ebp-8h]
  int *v7; // [esp+14h] [ebp-4h]

  if ( !rf_sound_system_ready[0] )
    return -1;
  if ( a1 >= 0xA28 )
    return -1;
  v5 = -1;
  for ( i = 0; v5 < 0 && i < 25; ++i )
  {
    if ( rf_ambient_voice_pool[6 * i] < 0 )
      v5 = i;
  }
  if ( v5 < 0 )
    return -1;
  v7 = &rf_ambient_voice_pool[6 * v5];
  *v7 = a1;
  v7[1] = -1;
  rf_vector_copy((float *)v7 + 2, copy_result, source);
  *((float *)v7 + 5) = a3;
  return v5;
}

