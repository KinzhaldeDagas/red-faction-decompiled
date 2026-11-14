// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004042E0 sub_4042E0
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Numeric dispatch case10 calls406130; case17 calls404F90. Each admitted mode update then408D20 common action helper. Do not treat mode10 as panic random routing or let a newly represented mode10 fall through generic host combat navigation.
char __cdecl sub_4042E0(float *Character)
{
  char result; // al

  result = byte_6663D1;
  if ( byte_6663D1 != 1 )
  {
    switch ( *((_DWORD *)Character + 160) )
    {
      case 1:
        rf_ai_update_noop();
        break;
      case 2:
        rf_ai_numeric_mode2_update(Character);
        break;
      case 3:
        rf_ai_numeric_mode3_update(Character);
        break;
      case 4:
        rf_ai_mode4_route_and_target_scan_update((int *)Character);
        break;
      case 5:
        rf_ai_mode5_secondary_dispatch((int *)Character);
        break;
      case 6:
        rf_ai_mode6_route_to_stored_destination((int *)Character);
        break;
      case 7:
        rf_ai_mode7_route_and_target_update(Character);
        break;
      case 8:
        rf_ai_mode8_face_auxiliary_target(Character);
        break;
      case 9:
        rf_ai_mode9_face_and_fire_auxiliary_target((int *)Character);
        break;
      case 0xA:
        sub_406130((int *)Character);
        break;
      case 0xB:
        rf_ai_mode11_secondary_dispatch(Character);
        break;
      case 0xC:
        rf_ai_mode12_target_geometry_and_reload_update(Character);
        break;
      case 0xD:
        rf_ai_mode13_inherit_attached_entity_target((int *)Character);
        break;
      case 0xE:
        rf_ai_transfer_budget_to_retained_entity_health((int)Character);
        break;
      case 0xF:
        rf_ai_mode15_acquire_or_track_target(Character);
        break;
      case 0x10:
        rf_ai_mode16_secondary_route_or_alarm_dispatch((int *)Character);
        break;
      case 0x11:
        sub_404F90((int *)Character);
        break;
      default:
        rf_ai_numeric_mode_write(Character, 1, -1, -1);
        break;
    }
    return rf_ai_refresh_active_weapon_body_action((unsigned int *)Character);
  }
  return result;
}

