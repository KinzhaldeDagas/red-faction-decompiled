// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2E90 rf_player_update_attached_cockpit_private_materials
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): First enable/get private material count and200-byte table for supplied model handle, BEFORE resolving player entity. Missing own entity exits. Resolve linked entity; NULL-safe class predicates choose: class flag1828 mask0x200 OR0x800 ->2F40 APC/fighter material update, else mask0x400 ->3E70 submarine update. No explicit linked NULL guard needed by predicates. Caller ignores EAX; raw return is helper/update residue, not success or material count. No table/handle/index validity check added here.
int __cdecl rf_player_update_attached_cockpit_private_materials(int a1, int a2)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-10h]
  int v4; // [esp+4h] [ebp-Ch] BYREF
  int v5; // [esp+8h] [ebp-8h] BYREF
  int v6; // [esp+Ch] [ebp-4h]

  rf_model_handle_enable_private_materials_get_table(a2, &v5, &v4);
  result = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v6 = result;
  if ( result )
  {
    v3 = rf_entity_resolve_handle(*(_DWORD *)(v6 + 512));
    if ( rf_entity_class_has_contact_geomod_flag200(v3) || rf_entity_class_flags724_has_mask800(v3) )
    {
      return rf_vehicle_update_apc_fighter_cockpit_materials(v3, v5, v4);
    }
    else
    {
      result = rf_entity_class_has_contact_geomod_flag400(v3);
      if ( (_BYTE)result )
        return rf_vehicle_update_submarine_cockpit_materials(v3, v5, v4);
    }
  }
  return result;
}

