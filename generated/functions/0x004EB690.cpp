// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EB690 rf_player_request_target_lock_scan
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Only local-global equality, no independent NULL guard, then resolve own entity. Resolve selected weapon; reject transition,holstered,custom-action,reload,attached-use-vehicle predicates only when AL EXACT1; additionally require linked UID512 EXACT-1. Obtain camera position196 and camera room; missing room rejects (not admitted as dry). If room contains camera point, underwater weapon flag must be NONZERO. Admit by setting BYTE3996=1 and arming player4008 at0ms. No target acquisition/readiness write, explicit dead/monitor/locking-weapon-flag validation or clearing on rejection. Native return AL is predicate/timer/pointer residue, not success.
char __cdecl rf_player_request_target_lock_scan(int a1)
{
  int room; // eax
  float v3[3]; // [esp+0h] [ebp-18h] BYREF
  int v4; // [esp+Ch] [ebp-Ch]
  unsigned int selected_weapon_and_resolve_mesh; // [esp+10h] [ebp-8h]
  int v6; // [esp+14h] [ebp-4h]

  LOBYTE(room) = a1;
  if ( a1 == rf_local_fpgun_player )
  {
    room = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    v6 = room;
    if ( room )
    {
      selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)a1);
      LOBYTE(room) = rf_fpgun_weapon_transition_blocks_fire(a1);
      if ( (unsigned __int8)room != 1 )
      {
        LOBYTE(room) = rf_entity_weapon_is_holstered_for_actions(v6);
        if ( (unsigned __int8)room != 1 )
        {
          LOBYTE(room) = rf_fpgun_custom_action_busy(a1);
          if ( (unsigned __int8)room != 1 )
          {
            LOBYTE(room) = rf_entity_reload_in_progress(v6);
            if ( (unsigned __int8)room != 1 )
            {
              LOBYTE(room) = rf_entity_has_attached_use_vehicle(v6);
              if ( (unsigned __int8)room != 1 && *(_DWORD *)(v6 + 512) == -1 )
              {
                rf_entity_view_copy_referenced_position(v3, *(_DWORD *)(a1 + 196));
                room = rf_camera_slot_get_room(*(void ***)(a1 + 196));
                v4 = room;
                if ( room )
                {
                  if ( !rf_liquid_room_contains_point(v4, (int)v3)
                    || (LOBYTE(room) = rf_weapon_has_underwater_flag(selected_weapon_and_resolve_mesh), (_BYTE)room) )
                  {
                    *(_BYTE *)(a1 + 3996) = 1;
                    LOBYTE(room) = rf_replicator_arm_milliseconds((int *)(a1 + 4008), 0);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return room;
}

