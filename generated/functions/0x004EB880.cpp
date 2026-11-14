// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EB880 rf_player_toggle_alt_zoom
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Only local-global equality, no separate NULL guard; own entity must resolve. Reject transition,holstered,custom-action,reload,attached-use-vehicle AL EXACT1 and linked UID512!=-1. NO own dead/monitor/alt-zoom-weapon flag admission. If3988==EXACT1 set3988=0,3989=1; otherwise set3988=1,3989=0 (including when outflag==1). Factor3992 unchanged. Then resolve selected weapon; any nonnegative index plays weapon sound DWORD596(0,0.0,1.0), replacing global voice662FB0 without first stopping old handle. Negative index leaves prior voice untouched despite toggled flags. Return AL is helper/pointer residue, not canonical zoom state/success. Later update supplies alive/monitor/weapon checks.
char __cdecl rf_player_toggle_alt_zoom(int a1)
{
  int selected_weapon_and_resolve_mesh; // eax
  int v3; // [esp+10h] [ebp-4h]

  LOBYTE(selected_weapon_and_resolve_mesh) = a1;
  if ( a1 == rf_local_fpgun_player )
  {
    selected_weapon_and_resolve_mesh = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    v3 = selected_weapon_and_resolve_mesh;
    if ( selected_weapon_and_resolve_mesh )
    {
      LOBYTE(selected_weapon_and_resolve_mesh) = rf_fpgun_weapon_transition_blocks_fire(a1);
      if ( (unsigned __int8)selected_weapon_and_resolve_mesh != 1 )
      {
        LOBYTE(selected_weapon_and_resolve_mesh) = rf_entity_weapon_is_holstered_for_actions(v3);
        if ( (unsigned __int8)selected_weapon_and_resolve_mesh != 1 )
        {
          LOBYTE(selected_weapon_and_resolve_mesh) = rf_fpgun_custom_action_busy(a1);
          if ( (unsigned __int8)selected_weapon_and_resolve_mesh != 1 )
          {
            LOBYTE(selected_weapon_and_resolve_mesh) = rf_entity_reload_in_progress(v3);
            if ( (unsigned __int8)selected_weapon_and_resolve_mesh != 1 )
            {
              LOBYTE(selected_weapon_and_resolve_mesh) = rf_entity_has_attached_use_vehicle(v3);
              if ( (unsigned __int8)selected_weapon_and_resolve_mesh != 1 && *(_DWORD *)(v3 + 512) == -1 )
              {
                if ( *(_BYTE *)(a1 + 3988) == 1 )
                {
                  *(_BYTE *)(a1 + 3989) = 1;
                  *(_BYTE *)(a1 + 3988) = 0;
                }
                else
                {
                  *(_BYTE *)(a1 + 3988) = 1;
                  *(_BYTE *)(a1 + 3989) = 0;
                }
                selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)a1);
                if ( selected_weapon_and_resolve_mesh >= 0 )
                {
                  selected_weapon_and_resolve_mesh = rf_gamesound_play_event(
                                                       unk_912254[340 * selected_weapon_and_resolve_mesh],
                                                       0,
                                                       0.0,
                                                       1.0);
                  dword_662FB0 = selected_weapon_and_resolve_mesh;
                }
              }
            }
          }
        }
      }
    }
  }
  return selected_weapon_and_resolve_mesh;
}

