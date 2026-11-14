// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF180 rf_undercover_enter_replace_player_entity
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] Require global player entity and shared active byte0x87FC01==0. Stop entity weapon firing, invoke teardown helpers, mark old entity deferred-delete, then create player replacement using definition0x87FC04 for nonzero input or0x87FC10 for zero. Store raw input0x87FC0C. Transfer position/view context, life, field+0x1450 and conditionally field+0x75C through observed copy/setup calls. Optional weapon0x87FC1C!=-1 installs/switches equipment, publishes weapon bitmasks, arms player-owned deadline0 or300ms depending prior holster state. Set new armor0, clear new entity+0x810 bit0x40, set+0x7D0 bit0x10000, publish shared active1 last. Not a model-only swap; broader complete player-state equivalence is not established.
void __cdecl rf_undercover_enter_replace_player_entity(int a1)
{
  int first_dword; // eax
  int v2; // eax
  float copy_result[3]; // [esp+0h] [ebp-18h] BYREF
  int v4; // [esp+Ch] [ebp-Ch]
  int v6; // [esp+14h] [ebp-4h]

  if ( dword_681E38 && !unk_87FC01 )
  {
    rf_entity_stop_weapon_firing(*(_DWORD *)(dword_681E38 + 44), *(_DWORD *)(dword_681E38 + 676));
    sub_43C0B0(dword_681E38);
    if ( *(_DWORD *)(rf_local_fpgun_player + 52) )
      rf_model_handle_reset_actions_adapter(*(_DWORD *)(rf_local_fpgun_player + 52));
    rf_undercover_cancel_local_pending_fpgun_transition();
    rf_player_weapon_reset_noop();
    v6 = dword_681E38;
    rf_object_mark_for_deferred_delete(dword_681E38);
    if ( a1 )
      v4 = unk_87FC04;
    else
      v4 = unk_87FC10;
    unk_87FC0C = a1;
    rf_multiplayer_player_entity_create(rf_local_fpgun_player, v4, (float *)(v6 + 60), (float *)(v6 + 72), -1);
    first_dword = rf_receiver_get_first_dword((void *)v6);
    rf_object_set_room_and_cache_position((float *)dword_681E38, first_dword);
    v2 = rf_receiver_get_first_dword((void *)v6);
    rf_object_set_room_and_cache_position(**(float ***)(rf_local_fpgun_player + 196), v2);
    rf_matrix3_copy((float *)(dword_681E38 + 2016), (const float *)(v6 + 2016));
    rf_vector_copy((float *)(dword_681E38 + 2004), copy_result, (const float *)(v6 + 2004));
    *(float *)(dword_681E38 + 52) = *(float *)(v6 + 52);
    *(_DWORD *)(dword_681E38 + 5200) = *(_DWORD *)(v6 + 5200);
    if ( rf_corpse_resolve_handle_type7(*(_DWORD *)(v6 + 1884)) )
    {
      *(_DWORD *)(dword_681E38 + 1884) = *(_DWORD *)(v6 + 1884);
      sub_4344D0(dword_681E38, 0);
      rf_entity_try_set_holster_and_stop_primary((_DWORD *)dword_681E38);
    }
    if ( dword_87FC1C != -1 )
    {
      unk_87FC08 = *(_DWORD *)(v6 + 676);
      rf_player_grant_weapon_and_set_reserve_and_clip(
        rf_local_fpgun_player,
        dword_87FC1C,
        unk_912088[340 * dword_87FC1C]);
      if ( rf_entity_weapon_is_holstered_for_actions(v6) )
      {
        rf_player_apply_weapon_selection_by_class(rf_local_fpgun_player, dword_87FC1C);
        rf_undercover_apply_local_weapon_skin_profile();
        rf_replicator_arm_milliseconds((int *)(*(_DWORD *)(dword_681E38 + 5168) + 4152), 0);
      }
      else
      {
        rf_player_request_weapon_switch(rf_local_fpgun_player, dword_87FC1C, 0, 1);
        rf_replicator_arm_milliseconds((int *)(*(_DWORD *)(dword_681E38 + 5168) + 4152), 300);
      }
      *(_DWORD *)(dword_681E38 + 5160) |= 1 << dword_87FC1C;
      *(_DWORD *)(dword_681E38 + 5164) |= 1 << dword_87FC1C;
    }
    *(float *)(dword_681E38 + 56) = 0.0;
    *(_DWORD *)(dword_681E38 + 2064) &= ~0x40u;
    *(_DWORD *)(dword_681E38 + 2000) |= 0x10000u;
    unk_87FC01 = 1;
  }
}

