// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E04F0 rf_player_dispatch_movement_state_action
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Assumes player nonNULL; resolve own entity+20; missing returns AL0. If 438050 or 437F00 returns nonzero, call435640(entity). Otherwise only437F60 AL==1 attempts435900(two output vectors,entity,F321000), then on its nonzero result calls4356E0(entity). Output vectors are not used afterward. Dependencies test movement-class IDs, not an established jump/crouch input. Return AL is raw helper/pointer residue, not a reliable success BOOL; caller442260 forwards it under single-player global input gate.
char __cdecl rf_player_dispatch_movement_state_action(int a1)
{
  int v1; // eax
  int v3[3]; // [esp+4h] [ebp-1Ch] BYREF
  int v4[3]; // [esp+10h] [ebp-10h] BYREF
  int v5; // [esp+1Ch] [ebp-4h]

  v1 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v5 = v1;
  if ( v1 )
  {
    if ( rf_entity_movement_is_index1_or2(v5) || rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)v5) )
    {
      LOBYTE(v1) = rf_entity_select_movement13_after_uncrouch(v5);
    }
    else
    {
      LOBYTE(v1) = rf_entity_descriptor_mode_is_12_15_13_11_or9(v5);
      if ( (unsigned __int8)v1 == 1 )
      {
        rf_vector3_default_construct_noop(v3);
        rf_vector3_default_construct_noop(v4);
        LOBYTE(v1) = rf_entity_vertical_sweep_contact_vectors((float *)v3, (float *)v4, v5, 1000.0);
        if ( (_BYTE)v1 )
          LOBYTE(v1) = (unsigned __int8)rf_entity_select_fall_movement_descriptor((_DWORD *)v5);
      }
    }
  }
  return v1;
}

