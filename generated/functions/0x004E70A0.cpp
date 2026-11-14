// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E70A0 rf_fpgun_cleanup_idle_actions
// UNREALRED VERIFIED [fpgun-action-dispatch]: Cleans idle_1, idle_2, and idle_3 mesh-action and sound records.
int __cdecl rf_fpgun_cleanup_idle_actions(int a1)
{
  int result; // eax
  int named_animation_entry; // [esp+4h] [ebp-18h]
  char *v3; // [esp+Ch] [ebp-10h]
  int i; // [esp+10h] [ebp-Ch]
  int v5; // [esp+14h] [ebp-8h]

  result = a1;
  if ( a1 == rf_local_fpgun_player )
  {
    result = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    if ( result )
    {
      result = a1;
      if ( *(_DWORD *)(a1 + 52) )
      {
        result = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)a1);
        v5 = result;
        if ( result != -1 )
        {
          v3 = (char *)&rf_weapon_records + 1360 * result;
          for ( i = 0; i < 3; ++i )
          {
            named_animation_entry = rf_weapon_find_named_animation_entry(v5, (char *)rf_fpgun_action_names[i + 3], 0);
            if ( named_animation_entry >= 0 )
            {
              if ( *(_DWORD *)&v3[28 * named_animation_entry + 772] )
              {
                rf_model_handle_zero_action_weight_adapter(
                  *(float ***)(a1 + 52),
                  *(_DWORD *)&v3[28 * named_animation_entry + 772]);
                rf_gamesound_stop_voice_handle(*(_DWORD *)&v3[28 * named_animation_entry + 780]);
              }
            }
            result = i + 1;
          }
        }
      }
    }
  }
  return result;
}

