// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EB600 rf_player_update_scanner_flag_and_elapsed_time
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Returns player pointer EAX. Only equal global and nonNULL player proceeds. Missing own entity clears scanner byte4016 and skips time increment. Existing entity: resolve selected weapon; absent scanner flag clears4016, then ALWAYS F32 time4032+=frame delta, even when scanner off/unsupported. No activation, time reset/wrap, dead/monitor/transition check or bitmap rendering here.
int __cdecl rf_player_update_scanner_flag_and_elapsed_time(int a1)
{
  int result; // eax
  unsigned int selected_weapon_and_resolve_mesh; // [esp+0h] [ebp-8h]

  result = a1;
  if ( a1 == rf_local_fpgun_player && a1 )
  {
    if ( rf_entity_resolve_handle(*(_DWORD *)(a1 + 20)) )
    {
      selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)a1);
      if ( !rf_weapon_has_scanner_flag(selected_weapon_and_resolve_mesh) )
        *(_BYTE *)(a1 + 4016) = 0;
      *(float *)(a1 + 4032) = *(float *)(a1 + 4032) + rf_frame_delta_seconds;
      return a1;
    }
    else
    {
      *(_BYTE *)(a1 + 4016) = 0;
      return a1;
    }
  }
  return result;
}

