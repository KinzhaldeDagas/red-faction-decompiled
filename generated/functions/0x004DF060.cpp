// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DF060 rf_player_apply_weapon_selection_by_class
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): Cdecl player,weapon index. Player is USED throughout; prior unused_player formal label was misleading. NULL player or missing resolved inventory returns. If422270(entity handle20,current inventory4) AL EXACT1, stops current weapon firing. If model52 nonNULL and cached weapon4224 differs from request, calls EMPTY release hook (no resource release). Reads weapon DWORD168 (1360-byte stride) without index validation: class0 writes inventory4 (entity676), optionally updates fpgun state when player flags16 mask0x10 predicate AL EXACT1, preloads selected animation files(player,new selected,index), applies entity weapon animation-profile overlay438DE0(inventory DWORD0,index), clears screen byte4228=0.
// Class1 writes ONLY inventory8 (entity680) after shared stop/hook preamble; other nonzero classes make no selection write. Does not check inventory ownership/ammo, request!=-1, update cached4224 or clear old model itself. All eight original native call sites pass two DWORDs and pop8; seven are in identified functions, one remains orphan code. Return void; signature update only clarifies parameter labels, retaining ABI.
void __cdecl rf_player_apply_weapon_selection_by_class(int player, unsigned int weapon_index)
{
  int *v2; // [esp+0h] [ebp-4h]

  if ( player )
  {
    v2 = (int *)rf_player_resolve_entity_inventory(player);
    if ( v2 )
    {
      if ( rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(player + 20), v2[1]) )
        rf_entity_stop_weapon_firing(*(_DWORD *)(player + 20), v2[1]);
      if ( *(_DWORD *)(player + 52) && *(_DWORD *)(player + 4224) != weapon_index )
        rf_fpgun_player_release_hook_noop(player);
      if ( unk_9120A8[340 * weapon_index] )
      {
        if ( unk_9120A8[340 * weapon_index] == 1 )
          v2[2] = weapon_index;
      }
      else
      {
        v2[1] = weapon_index;
        if ( rf_player_has_flags16_mask10(player) )
          rf_fpgun_update_state_transition(player, weapon_index);
        rf_player_preload_selected_weapon_animation_files((_DWORD *)player, v2[1], weapon_index);
        rf_entity_restore_action_tables_and_apply_weapon_overrides(*v2, weapon_index);
        *(_BYTE *)(player + 4228) = 0;
      }
    }
  }
}

