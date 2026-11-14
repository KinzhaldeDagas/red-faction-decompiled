// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EAC30 rf_player_get_visible_muzzle_flash_parameters
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Local-global equality required; no independent NULL guard if bothNULL. Resolve own UID20, require timer entity4972 armed(nonzero) and elapsed result!=EXACT1. Reject runtime flags2064 mask0x2000, then selected weapon via0440; per-weapon bit predicate4387A0(entity,index)==EXACT1 rejects. Require muzzle transform B9E0(player,outPosition,NULL) NONZERO. Then write weapon DWORD+100 to outTexture and F32+104 to outSize; returnAL1 iff written texture!=-1. Thus final AL0 can still have position,texture,size writes. Earlier failures leave caller outputs untouched. No selected index/output-pointer bounds check or camera/finite validation.
bool __cdecl rf_player_get_visible_muzzle_flash_parameters(
        _DWORD *player,
        float *muzzle_position,
        _DWORD *a3,
        float *a4)
{
  unsigned int selected_weapon_and_resolve_mesh; // [esp+4h] [ebp-8h]
  int v6; // [esp+8h] [ebp-4h]

  if ( player != (_DWORD *)rf_local_fpgun_player )
    return 0;
  v6 = rf_entity_resolve_handle(player[5]);
  if ( !v6 )
    return 0;
  if ( !rf_replicator_is_armed((_DWORD *)(v6 + 4972)) || rf_replicator_has_elapsed((int *)(v6 + 4972)) )
    return 0;
  if ( (*(_DWORD *)(v6 + 2064) & 0x2000) != 0 )
    return 0;
  selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh(player);
  if ( rf_entity_custom_mask142C_has_index(v6, selected_weapon_and_resolve_mesh) )
    return 0;
  if ( !rf_player_compose_fpgun_muzzle_world_transform(player, muzzle_position, nullptr) )
    return 0;
  *a3 = *((_DWORD *)&rf_weapon_records + 340 * selected_weapon_and_resolve_mesh + 25);
  *a4 = *((float *)&rf_weapon_records + 340 * selected_weapon_and_resolve_mesh + 26);
  return *a3 != -1;
}

