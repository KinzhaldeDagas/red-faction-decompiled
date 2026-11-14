// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E0DF0 sub_4E0DF0
// UNREALRED VERIFIED [early-respawn-20260930] Local input owner reaches sampled action dispatch 0x441B60 unconditionally at its tail, without a death-action-completion gate. That dispatcher samples actions while unpaused and passes them to 0x4E1060, whose dead primary/alternate path tests the shared one-second manual event. This manual route is distinct from forced respawn in completed death transition 0x4E1D70.
void __cdecl sub_4E0DF0(int a1)
{
  int v1; // [esp+0h] [ebp-10h]
  float *v2; // [esp+4h] [ebp-Ch]
  _DWORD *v3; // [esp+8h] [ebp-8h]

  v3 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v2 = nullptr;
  if ( v3 )
    v2 = (float *)(v3 + 450);
  if ( rf_view_wrapper_get_dword8(*(_DWORD *)(a1 + 196)) == 2 )
  {
    rf_player_build_referenced_object_controls(a1);
  }
  else if ( rf_view_wrapper_get_dword8(*(_DWORD *)(a1 + 196)) == 4 )
  {
    v2 = (float *)(**(_DWORD **)(a1 + 196) + 1800);
    rf_player_build_controls_unpaused_unblocked(a1, (int)v2);
  }
  else
  {
    if ( v3 && (int)v3[128] > -1 )
    {
      v1 = rf_entity_resolve_handle(v3[128]);
      if ( rf_entity_has_attached_use_vehicle((int)v3) )
      {
        *(_DWORD *)(a1 + 332) = 1;
        *(_DWORD *)(a1 + 360) = 1;
      }
      if ( !rf_entity_is_parent_jeep_relation1((int)v3) )
        v2 = (float *)(v1 + 1800);
    }
    else
    {
      if ( v3 && (v3[516] & 0x2000) != 0 || rf_entity_movement_descriptor_kind_is2((int)v3) )
        *(_DWORD *)(a1 + 332) = 1;
      if ( rf_entity_movement_is_index4_or7((int)v3) || rf_entity_movement_descriptor_kind_is2((int)v3) )
        *(_DWORD *)(a1 + 360) = 1;
    }
    rf_player_build_controls_unpaused_unblocked(a1, (int)v2);
  }
  *(_DWORD *)(a1 + 332) = 0;
  if ( *(_BYTE *)(a1 + 3896) )
    *(_DWORD *)(a1 + 360) = 0;
  else
    *(_DWORD *)(a1 + 360) = 1;
  if ( (*(_DWORD *)(a1 + 16) & 8) != 0 && v2 )
    rf_player_control_clear_vectors_and_fields1C20(v2);
  if ( v3 )
  {
    if ( rf_entity_is_parent_jeep_relation1((int)v3) )
    {
      rf_vector3_zero_return_destination(v2 + 3);
      v3[31] |= 0x100u;
    }
    else
    {
      v3[31] &= ~0x100u;
    }
  }
  rf_player_apply_input_stance_dispatch_and_fire_release(a1, v2);
}

