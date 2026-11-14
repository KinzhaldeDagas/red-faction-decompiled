// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005054C0 rf_trigger_runtime_activate
// UNREALRED VERIFIED [mission-mover-activation-20261013] Direct trigger link of common type8 activates mover using linked UID, trigger+0x2C UID and activating object argument2. Argument3 suppresses ONLY direct mover activation. Links are walked in authored order, including duplicates. Type6 event dispatch carries the same trigger/object context.
// UNREALRED VERIFIED [mission-startup-20261020] Startup uses the same heterogeneous ordered link dispatch: common type4 clutter toggle, type5 trigger enable, type6 event forward, type8 mover activation; unresolved common IDs use ambient fallback. Duplicates remain operations. Empty/unresolved lists still return to0x505360, which increments activation count. The trigger is not required to have a scene overlap object.
// UNREALRED VERIFIED [trigger-use-20261021] Non-4/5/6/8 common families (including linked entity targets) are ignored by effect dispatch, yet commit count/cooldown proceeds. Missing common uses ambient fallback. UnrealRed spatial/auto commit now allows ignored/entity-only lists and routes direct trigger enable and ambient enable, retaining existing mission-graph validation limits.
int __cdecl rf_trigger_runtime_activate(int a1, int a2, char a3)
{
  int result; // eax
  int *v4; // eax
  int *v5; // eax
  int v6; // [esp+14h] [ebp-10h]
  int v7; // [esp+18h] [ebp-Ch]
  int *v8; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 724));
    if ( i >= result )
      break;
    v4 = (int *)sub_552200((_DWORD *)(a1 + 724), i);
    v7 = rf_object_resolve_handle(*v4);
    if ( v7 )
    {
      switch ( *(_DWORD *)(v7 + 36) )
      {
        case 4:
          rf_clutter_toggle_first_two_skins(*(_DWORD *)(v7 + 44));
          rf_gamesound_play_positional_event(37, (float *)(v7 + 60), 1.0, (int)flt_17F10B0, 0);
          if ( *(float *)(a1 + 752) >= 0.0 )
            rf_replicator_arm_milliseconds((int *)(a1 + 756), (int)(*(float *)(a1 + 752) * 1000.0));
          if ( *(_DWORD *)(a1 + 672) + 1 < *(_DWORD *)(a1 + 676) || *(_DWORD *)(a1 + 676) == -1 )
            rf_hud_world_target_arm_red_deadline(*(_DWORD *)(v7 + 44), *(_DWORD *)(a1 + 668));
          else
            rf_hud_world_target_registry_remove(*(_DWORD *)(v7 + 44));
          break;
        case 5:
          rf_trigger_set_forward_enabled(v7);
          break;
        case 6:
          if ( rf_multiplayer_runtime_mode )
          {
            if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
            {
              v6 = rf_mission_event_find_by_uid(*(_DWORD *)(v7 + 44));
              if ( v6 )
              {
                if ( *(_DWORD *)(v6 + 656) == 17 )
                  rf_mission_event_activate_by_uid(*(_DWORD *)(v7 + 44), *(_DWORD *)(a1 + 44), a2);
              }
            }
          }
          else
          {
            rf_mission_event_activate_by_uid(*(_DWORD *)(v7 + 44), *(_DWORD *)(a1 + 44), a2);
          }
          break;
        case 8:
          if ( !a3 )
            rf_mover_activate_forward(*(_DWORD *)(v7 + 44), *(_DWORD *)(a1 + 44), a2);
          break;
        default:
          continue;
      }
    }
    else
    {
      v5 = (int *)sub_552200((_DWORD *)(a1 + 724), i);
      v8 = rf_ambient_sound_find_by_uid(*v5);
      if ( v8 )
        rf_ambient_sound_enable_by_uid(v8[2]);
    }
  }
  return result;
}

