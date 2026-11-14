// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EB7D0 rf_player_toggle_scanner_flag
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Only local-global equality, no separate NULL guard, resolves own entity. Reject transition,holstered,custom-action,attached-use-vehicle AL EXACT1 and any linked UID512!=-1. Toggle BYTE4016 as normalized logical NOT(oldbyte): any nonzero becomes0,zero becomes1. No scanner-weapon flag, reload/dead/monitor, underwater or camera-room test. Unsupported weapon can be toggled until updateB600 clears it; time4032 not reset. AL return incidental.
char __cdecl rf_player_toggle_scanner_flag(int a1)
{
  int v1; // eax
  int v3; // [esp+0h] [ebp-4h]

  LOBYTE(v1) = a1;
  if ( a1 == rf_local_fpgun_player )
  {
    v1 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    v3 = v1;
    if ( v1 )
    {
      LOBYTE(v1) = rf_fpgun_weapon_transition_blocks_fire(a1);
      if ( (unsigned __int8)v1 != 1 )
      {
        LOBYTE(v1) = rf_entity_weapon_is_holstered_for_actions(v3);
        if ( (unsigned __int8)v1 != 1 )
        {
          LOBYTE(v1) = rf_fpgun_custom_action_busy(a1);
          if ( (unsigned __int8)v1 != 1 )
          {
            LOBYTE(v1) = rf_entity_has_attached_use_vehicle(v3);
            if ( (unsigned __int8)v1 != 1 && *(_DWORD *)(v3 + 512) == -1 )
            {
              *(_BYTE *)(a1 + 4016) = *(_BYTE *)(a1 + 4016) == 0;
              LOBYTE(v1) = a1;
            }
          }
        }
      }
    }
  }
  return v1;
}

