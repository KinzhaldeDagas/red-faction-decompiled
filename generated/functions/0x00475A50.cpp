// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475A50 rf_ambient_sounds_update
// UNREALRED VERIFIED [world-uid-ownership]: Walks the ambient-sound list, lazily creates an admitted runtime sound handle, and otherwise updates each existing handle's position.
// UNREALRED VERIFIED [ambient-audio]: Updates every persistent ambient record. Assigned records refresh frontend position; unassigned records whose timer is armed and elapsed retry 25-slot reservation, then reset the timer even when the pool remains full.
unsigned __int8 rf_ambient_sounds_update()
{
  unsigned __int8 result; // al
  int *i; // [esp+4h] [ebp-4h]

  result = rf_ambient_sound_list_head;
  for ( i = (int *)rf_ambient_sound_list_head; i != &rf_ambient_sound_list_head; i = (int *)*i )
  {
    if ( i[4] < 0 )
    {
      result = rf_replicator_is_armed(i + 14);
      if ( result )
      {
        result = rf_replicator_has_elapsed(i + 14);
        if ( result )
        {
          i[4] = rf_ambient_voice_reserve_frontend_slot(i[3], (float *)i + 5, *((float *)i + 11));
          result = (unsigned __int8)rf_replicator_reset(i + 14);
        }
      }
    }
    else
    {
      result = rf_ambient_voice_set_position(i[4], (float *)i + 5);
    }
  }
  return result;
}

