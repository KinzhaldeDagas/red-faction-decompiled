// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ED6B0 rf_fpgun_release_cycle_slot_model_cache
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): If ready byte87C6E6 is zero, returns with no changes. Otherwise scans32 slots, only signed weapon IDs>=0: unconditionally calls release-asset-then-destroy on main model, then zeros it; releases and zeros secondary model only if nonzero. Main release helper is not NULL-safe. Invalid-weapon slots are untouched. Clears model52 only for nonNULL global local player; sets cache character/team662F6C/70=-1 and ready=0. EAX is incidental loop/helper residue, not a success status.
int rf_fpgun_release_cycle_slot_model_cache()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = byte_87C6E6[0];
  if ( byte_87C6E6[0] )
  {
    for ( i = 0; i < 32; ++i )
    {
      result = 16 * i;
      if ( rf_weapon_cycle_slots_weapon_index[4 * i] > -1 )
      {
        rf_model_handle_release_asset_then_destroy((int *)rf_weapon_cycle_slots_runtime_icon[4 * i]);
        result = 16 * i;
        rf_weapon_cycle_slots_runtime_icon[4 * i] = 0;
        if ( unk_87C118[4 * i] )
        {
          result = rf_model_handle_release_asset_then_destroy((int *)unk_87C118[4 * i]);
          unk_87C118[4 * i] = 0;
        }
      }
    }
    if ( rf_local_fpgun_player )
      *(_DWORD *)(rf_local_fpgun_player + 52) = 0;
    dword_662F6C = -1;
    dword_662F70 = -1;
    byte_87C6E6[0] = 0;
  }
  return result;
}

