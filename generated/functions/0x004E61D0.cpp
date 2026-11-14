// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E61D0 rf_fpgun_clear_action_sound_handles
// UNREALRED VERIFIED [fpgun-action-dispatch]: Stops every valid live action-sound handle in the active fpgun definition and writes -1.
char *__cdecl rf_fpgun_clear_action_sound_handles(char *a1)
{
  char *result; // eax
  char *v2; // [esp+0h] [ebp-10h]
  int i; // [esp+4h] [ebp-Ch]
  char *v4; // [esp+8h] [ebp-8h]

  result = a1;
  if ( a1 == (char *)rf_local_fpgun_player )
  {
    result = (char *)rf_entity_resolve_handle(*((_DWORD *)a1 + 5));
    if ( result )
    {
      result = (char *)rf_player_get_selected_weapon_and_resolve_mesh(a1);
      v4 = result;
      if ( result != (char *)-1 )
      {
        v2 = (char *)&rf_weapon_records + 1360 * (_DWORD)result;
        for ( i = 0; ; ++i )
        {
          result = (char *)&rf_weapon_records + 1360 * (_DWORD)v4;
          if ( i >= *((_DWORD *)v2 + 167) )
            break;
          if ( rf_gamesound_voice_is_playing(*(_DWORD *)&v2[28 * i + 780]) )
            rf_gamesound_stop_voice_handle(*(_DWORD *)&v2[28 * i + 780]);
          *(_DWORD *)&v2[28 * i + 780] = -1;
        }
      }
    }
  }
  return result;
}

