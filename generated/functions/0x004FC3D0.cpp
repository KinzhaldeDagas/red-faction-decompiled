// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC3D0 rf_event_teleport_player_apply
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type63 Teleport_Player. Require global local entity; if its associated entity resolves, exact case-insensitive level L20S2.rfl instead teleports that associated entity; other levels call detach0x434C80 and retain local player as destination owner. Publish event position through predicted+0xF0 and0x4BC330 setter, invoke four event-orientation copies and update entity view angles+0x864. The0x4D98A0 continuation additionally requires predicate0x438010 and(multiplayer_mode!=1 OR server_authority). Does not iterate target vector or assign AI mode2 as generic Teleport does.
void __cdecl rf_event_teleport_player_apply(int a1)
{
  float v1; // [esp+0h] [ebp-2Ch]
  float copy_result[3]; // [esp+Ch] [ebp-20h] BYREF
  float v3; // [esp+18h] [ebp-14h] BYREF
  float v4; // [esp+1Ch] [ebp-10h] BYREF
  float v5; // [esp+20h] [ebp-Ch] BYREF
  float *v6; // [esp+24h] [ebp-8h]
  float *v7; // [esp+28h] [ebp-4h]

  if ( dword_681E38 )
  {
    v7 = (float *)dword_681E38;
    v6 = (float *)rf_entity_resolve_handle(*(_DWORD *)(dword_681E38 + 512));
    if ( v6 )
    {
      if ( rf_string_equals_case_insensitive((int)unk_6FC31C, "L20S2.rfl") )
        v7 = v6;
      else
        rf_entity_try_detach_with_safe_exit((int)v7);
    }
    rf_vector_copy(v7 + 60, copy_result, (const float *)(a1 + 64));
    rf_object_publish_position_and_bounds((int)v7, (float *)(a1 + 64));
    rf_matrix3_copy(v7 + 18, (const float *)(a1 + 76));
    rf_matrix3_copy(v7 + 63, (const float *)(a1 + 76));
    rf_matrix3_copy(v7 + 72, (const float *)(a1 + 76));
    rf_matrix3_copy(v7 + 504, (const float *)(a1 + 76));
    rf_vector3_default_construct_noop(&v3);
    rf_matrix3_extract_euler_angles_retail(v7 + 18, &v3, &v5, &v4);
    v1 = -v3;
    rf_vector3_set_components_thiscall(v7 + 537, v1, v4, v5);
    if ( (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority) && sub_438010((int)v7) )
      rf_object_snap_down_using_physics_shape_sweep((int)v7);
  }
}

