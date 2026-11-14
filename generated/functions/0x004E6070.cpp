// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E6070 rf_fpgun_dispatch_semantic_action
// UNREALRED VERIFIED [fpgun-action-dispatch]: Local-owner-only dispatcher for 12 semantic slots; resets action context, starts the held VMesh action, and replaces the live action sound.
void __cdecl rf_fpgun_dispatch_semantic_action(int a1, unsigned int a2)
{
  int v2; // eax
  int named_animation_entry; // [esp+Ch] [ebp-18h]
  char *v4; // [esp+14h] [ebp-10h]
  unsigned int selected_weapon_and_resolve_mesh; // [esp+1Ch] [ebp-8h]
  int v6; // [esp+20h] [ebp-4h]

  if ( a1 == rf_local_fpgun_player )
  {
    v6 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    if ( v6 )
    {
      if ( a2 < 0xC )
      {
        if ( *(_DWORD *)(a1 + 52) )
        {
          selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)a1);
          if ( selected_weapon_and_resolve_mesh != -1 )
          {
            v4 = (char *)&rf_weapon_records + 1360 * selected_weapon_and_resolve_mesh;
            named_animation_entry = rf_weapon_find_named_animation_entry(
                                      selected_weapon_and_resolve_mesh,
                                      (char *)rf_fpgun_action_names[a2],
                                      0);
            if ( named_animation_entry >= 0 )
            {
              if ( *(_DWORD *)&v4[28 * named_animation_entry + 772] )
              {
                rf_model_handle_get_runtime_pointer(*(int **)(a1 + 52));
                rf_fpgun_clear_action_sound_handles((char *)a1);
                rf_model_handle_reset_actions_adapter(*(_DWORD *)(a1 + 52));
                rf_vfx_start_instance(*(int **)(a1 + 52), *(_DWORD *)&v4[28 * named_animation_entry + 772], 1.0, 1);
                if ( *(_DWORD *)&v4[28 * named_animation_entry + 776] != -1 )
                {
                  v2 = rf_foley_choose_random_sound(*(_DWORD *)&v4[28 * named_animation_entry + 776]);
                  *(_DWORD *)&v4[28 * named_animation_entry + 780] = rf_gamesound_play_positional_event(
                                                                       v2,
                                                                       (float *)(v6 + 2004),
                                                                       1.0,
                                                                       (int)flt_17F10B0,
                                                                       0);
                }
              }
            }
          }
        }
      }
    }
  }
}

