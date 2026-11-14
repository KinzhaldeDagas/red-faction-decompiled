// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF4D0 rf_undercover_exit_replace_player_entity
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] If shared active byte0x87FC01 false, return. Clear active BEFORE testing player entity presence; absent player returns without replacement/alarm clear. Otherwise stop firing/teardown, mark current entity deferred-delete and create replacement from shared baseline definition0x87FC14. Transfer position/view context and life; conditionally field+0x75C. Restore weapon through baseline0x911CBC and0/300ms holster deadline. Armor becomes definition maximum+0x48, entity+0x810 bit0x40 set, +0x7D0 bit0x10000 cleared, weapon bitmasks+0x1428/+0x142C zeroed, then shared alarm disabled. This is not an exact saved-armor/inventory restore.
int rf_undercover_exit_replace_player_entity()
{
  int result; // eax
  int first_dword; // eax
  int v2; // eax
  float copy_result[3]; // [esp+0h] [ebp-14h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  result = byte_87FC01[0];
  if ( byte_87FC01[0] )
  {
    byte_87FC01[0] = 0;
    if ( dword_681E38 )
    {
      rf_entity_stop_weapon_firing(*(_DWORD *)(dword_681E38 + 44), *(_DWORD *)(dword_681E38 + 676));
      if ( *(_DWORD *)(rf_local_fpgun_player + 52) )
        rf_model_handle_reset_actions_adapter(*(_DWORD *)(rf_local_fpgun_player + 52));
      rf_undercover_cancel_local_pending_fpgun_transition();
      rf_player_weapon_reset_noop();
      v5 = dword_681E38;
      rf_object_mark_for_deferred_delete(dword_681E38);
      rf_multiplayer_player_entity_create(rf_local_fpgun_player, unk_87FC14, (float *)(v5 + 60), (float *)(v5 + 72), -1);
      first_dword = rf_receiver_get_first_dword((void *)v5);
      rf_object_set_room_and_cache_position((float *)dword_681E38, first_dword);
      v2 = rf_receiver_get_first_dword((void *)v5);
      rf_object_set_room_and_cache_position(**(float ***)(rf_local_fpgun_player + 196), v2);
      rf_matrix3_copy((float *)(dword_681E38 + 2016), (const float *)(v5 + 2016));
      rf_vector_copy((float *)(dword_681E38 + 2004), copy_result, (const float *)(v5 + 2004));
      *(float *)(dword_681E38 + 52) = *(float *)(v5 + 52);
      if ( rf_corpse_resolve_handle_type7(*(_DWORD *)(v5 + 1884)) )
      {
        *(_DWORD *)(dword_681E38 + 1884) = *(_DWORD *)(v5 + 1884);
        sub_4344D0(dword_681E38, 0);
        rf_entity_try_set_holster_and_stop_primary((_DWORD *)dword_681E38);
      }
      if ( rf_entity_weapon_is_holstered_for_actions(v5) )
      {
        rf_player_apply_weapon_selection_by_class(rf_local_fpgun_player, dword_911CBC);
        rf_replicator_arm_milliseconds((int *)(*(_DWORD *)(dword_681E38 + 5168) + 4152), 0);
      }
      else
      {
        rf_player_request_weapon_switch(rf_local_fpgun_player, dword_911CBC, 0, 1);
        rf_replicator_arm_milliseconds((int *)(*(_DWORD *)(dword_681E38 + 5168) + 4152), 300);
      }
      *(float *)(dword_681E38 + 56) = *(float *)(*(_DWORD *)(dword_681E38 + 660) + 72);
      *(_DWORD *)(dword_681E38 + 2064) |= 0x40u;
      *(_DWORD *)(dword_681E38 + 2000) &= ~0x10000u;
      *(_DWORD *)(dword_681E38 + 5160) = 0;
      *(_DWORD *)(dword_681E38 + 5164) = 0;
      return rf_alarm_disable_shared();
    }
  }
  return result;
}

