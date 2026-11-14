// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004759D0 rf_ambient_sounds_initialize_frontend_slots
// UNREALRED VERIFIED [ambient-audio]: Initial admission pass over every persistent record. Zero-delay records immediately reserve one of 25 frontend slots in list order; nonzero-delay records arm their +56 timer for the exact authored +52 milliseconds.
int rf_ambient_sounds_initialize_frontend_slots()
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  result = rf_ambient_sound_list_head;
  for ( i = rf_ambient_sound_list_head; (_DWORD *)i != &rf_ambient_sound_list_head; i = *(_DWORD *)i )
  {
    result = i;
    if ( *(_DWORD *)(i + 16) == -1 )
    {
      if ( *(_DWORD *)(i + 52) )
      {
        result = rf_replicator_arm_milliseconds((int *)(i + 56), *(_DWORD *)(i + 52));
      }
      else
      {
        result = rf_ambient_voice_reserve_frontend_slot(*(_DWORD *)(i + 12), (float *)(i + 20), *(float *)(i + 44));
        *(_DWORD *)(i + 16) = result;
      }
    }
  }
  return result;
}

