// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DA9F0 rf_player_try_local_special_use_action
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl player,entity; no own NULL checks. If carried-body handle entity1884!=-1, attempts body drop40C7F0(entity+672,0), plays event2 on false, ALWAYS returnsAL1. Otherwise entity512!=-1 returns0. Monitor predicate EXACT1 exits monitor and returns1. Finds focused object4BB670(entity,&unusedNode); missing returns0; resolves target entity handle44 before use classification. Full11-entry original jump table verified: classes1..4/7/default return0. Class0: non-corpse type36!=7 plays event2,returns1; corpse pickup only in multiplayer byte0 and unobstructed geometry from entity2004 to target60 (flags1,0), calls40C3C0(entity+672,targetHandle), error sound on false,returns1 regardless of pickup
// result. Class5: only multiplayer byte0 and signed player180<0, begins monitor target,returns1. Classes6/9 only multiplayer byte0 invoke respectively speech action or40C650 on resolved target entity+672 and current entity, return1; no resolved-target NULL guard here. Class10 resolves clutter by target UID44, calls415F90 and returns1 if found. Class8 rejects multiplayer EXACT1 (other nonzero values admitted); type2 target with resolved projectile rejects attachment688 resolving to type0 object, and requires projectile owner48==player entity handle20; missing projectile resolution bypasses those checks. If remote-charge inventory present, compares reserve using weapon DWORD36 against signed max DWORD608, incrementing when <=max (so max can become max+1). Otherwise grants weapon with ammo-1 and forces reserve1. Plays positional event12 at target60 and marks target deferred-delete even when
// reserve was above cap; ALWAYS returns0 after this handled pickup, allowing outer general-use path to continue. No own upper index bounds.
char __cdecl rf_player_try_local_special_use_action(int a1, int a2)
{
  char result; // al
  int v3; // [esp+14h] [ebp-18h]
  int v4; // [esp+18h] [ebp-14h]
  int v5; // [esp+1Ch] [ebp-10h]
  int v6; // [esp+20h] [ebp-Ch]
  float *best_use_candidate; // [esp+24h] [ebp-8h]
  int v8; // [esp+28h] [ebp-4h] BYREF

  if ( *(_DWORD *)(a2 + 1884) == -1 )
  {
    if ( *(_DWORD *)(a2 + 512) == -1 )
    {
      if ( rf_player_view_target_is_monitor(a1) )
      {
        rf_player_exit_monitor_view(a1);
        return 1;
      }
      else
      {
        best_use_candidate = rf_entity_find_best_use_candidate((_DWORD *)a2, &v8);
        if ( best_use_candidate )
        {
          v6 = rf_entity_resolve_handle(*((_DWORD *)best_use_candidate + 11));
          switch ( rf_object_get_use_classification(best_use_candidate) )
          {
            case 0:
              if ( *((_DWORD *)best_use_candidate + 9) != 7 )
              {
                rf_gamesound_play_event(2, 0, 0.0, 1.0);
                return 1;
              }
              if ( rf_multiplayer_runtime_mode
                || rf_geometry_segment_is_obstructed((float *)(a2 + 2004), best_use_candidate + 15, 1, nullptr) )
              {
                return 0;
              }
              if ( !rf_ai_try_pick_up_corpse((int *)(a2 + 672), *((_DWORD *)best_use_candidate + 11)) )
                rf_gamesound_play_event(2, 0, 0.0, 1.0);
              result = 1;
              break;
            case 5:
              if ( rf_multiplayer_runtime_mode || *(int *)(a1 + 180) >= 0 )
                return 0;
              rf_player_begin_monitor_target(a1, *((_DWORD *)best_use_candidate + 11));
              return 1;
            case 6:
              if ( rf_multiplayer_runtime_mode )
                return 0;
              rf_ai_mode2_speech_action_update((int *)(v6 + 672), a2);
              return 1;
            case 8:
              if ( rf_multiplayer_runtime_mode == 1 )
                return 0;
              if ( *((_DWORD *)best_use_candidate + 9) == 2 )
              {
                v4 = rf_projectile_resolve_uid_type2(*((_DWORD *)best_use_candidate + 11));
                if ( v4 )
                {
                  v3 = rf_object_resolve_handle(*(_DWORD *)(v4 + 688));
                  if ( v3 )
                  {
                    if ( !*(_DWORD *)(v3 + 36) )
                      return 0;
                  }
                  if ( *(_DWORD *)(v4 + 48) != *(_DWORD *)(a1 + 20) )
                    return 0;
                }
              }
              if ( sub_403D00(a2 + 672, dword_911C78) )
              {
                if ( *(_DWORD *)(a2 + 4 * *((_DWORD *)&rf_weapon_records + 340 * dword_911C78 + 9) + 684) <= *((_DWORD *)&rf_weapon_records + 340 * dword_911C78 + 152) )
                  ++*(_DWORD *)(a2 + 4 * dword_912024[340 * dword_911C78] + 684);
              }
              else
              {
                rf_entity_inventory_grant_weapon((int *)(a2 + 672), dword_911C78, -1);
                *(_DWORD *)(a2 + 4 * dword_912024[340 * dword_911C78] + 684) = 1;
              }
              rf_gamesound_play_positional_event(12, best_use_candidate + 15, 1.0, (int)flt_17F10B0, 0);
              rf_object_mark_for_deferred_delete((int)best_use_candidate);
              return 0;
            case 9:
              if ( rf_multiplayer_runtime_mode )
                return 0;
              rf_ai_begin_use_speech_to_entity((int *)(v6 + 672), a2);
              return 1;
            case 10:
              v5 = rf_clutter_find_by_uid(*((_DWORD *)best_use_candidate + 11));
              if ( !v5 )
                return 0;
              rf_clutter_play_class_use_sound(v5);
              return 1;
            default:
              return 0;
          }
        }
        else
        {
          return 0;
        }
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    if ( !rf_ai_try_drop_carried_corpse((int *)(a2 + 672), 0) )
      rf_gamesound_play_event(2, 0, 0.0, 1.0);
    return 1;
  }
  return result;
}

