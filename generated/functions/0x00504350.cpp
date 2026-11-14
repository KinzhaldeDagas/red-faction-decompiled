// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00504350 rf_trigger_global_lifecycle_update
// UNREALRED VERIFIED [mission-unhide-20261020] Attached-trigger lifecycle distinguishes owner inactivity from trigger inactivity: owner+768 inactivity toggles forward-disabled flag0x10 through enable/disable; trigger own inactivity suppresses following the owner pose. Pending activation/reset timers are not globally skipped just because trigger common is inactive. Full attached-trigger ownership is not implemented by the UnHide pass.
// UNREALRED VERIFIED [trigger-attachment-20261020] Attachment block504589..504654 resolves trigger+0x300 as a full runtime handle. Owner inactive sets disabled0x10 only when clear; active owner clears it when set. Trigger own inactive suppresses pose copy only. Owner common flag2 queues trigger deferred deletion regardless of trigger inactivity. Missing owner has no effect. This block follows trigger reset/delayed activation work; it is not a blanket timer gate. UnrealRed observes queued owner removal across UE destruction callbacks, retires attached triggers, and routes current poses into interaction, HUD and mover containment consumers.
// UNREALRED VERIFIED [trigger-airlock-20261022] Delayed airlock lifecycle: after clutter reset and same-frame-bit clear, elapsed cycle+0x2E0 arms pressure timer+0x2E8 for50ms at CURRENT time and continues, skipping attachment for that trigger on that frame. A later elapsed pressure timer toggles room byte+68, resets pressure timer, computes5041E0 suppression, calls505360 with saved activator+0x2E4, resets cycle and saved handle=-1. Does not rerun geometry, InsideTime, life, cooldown, or forward-disable admission. Pressure changes even if commit fails. UnrealRed implements these stages; per-trigger native lifecycle ordering, cached moving-room membership, and rebuilt GeoMod room topology remain fidelity work.
// UNREALRED VERIFIED [trigger-lifecycle-20261026] Runtime trigger list traversal interleaves clutter reset, same-frame flag0x40 clear, delayed airlock work, then attachment for EACH trigger before the next. An earlier attachment can disable a trigger before a later delayed activation enables it. Bulk all-airlocks then all-attachments changes this result. UnrealRed now visits these stages in serialized creation order, with level-generation guards after callback-capable stages; the pressure-timer arm continues past attachment for that trigger only. This supersedes the per-trigger ordering limitation recorded by trigger-airlock-20261022. Cached room membership and rebuilt GeoMod room topology remain open.
char rf_trigger_global_lifecycle_update()
{
  int v0; // eax
  int first_dword; // eax
  int *v2; // eax
  float copy_result[3]; // [esp+0h] [ebp-30h] BYREF
  int v5; // [esp+Ch] [ebp-24h]
  float v6[3]; // [esp+10h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-14h]
  int j; // [esp+20h] [ebp-10h]
  int v9; // [esp+24h] [ebp-Ch]
  int i; // [esp+28h] [ebp-8h]
  char v11; // [esp+2Fh] [ebp-1h]

  v11 = 0;
  LOBYTE(v0) = rf_trigger_runtime_list_head;
  for ( i = rf_trigger_runtime_list_head; (_UNKNOWN *)i != &unk_90B510; i = *(_DWORD *)(i + 652) )
  {
    if ( rf_replicator_is_armed((_DWORD *)(i + 756)) && rf_replicator_has_elapsed((int *)(i + 756)) )
    {
      rf_replicator_reset((_DWORD *)(i + 756));
      for ( j = 0; ; ++j )
      {
        first_dword = rf_receiver_get_first_dword((void *)(i + 724));
        if ( j >= first_dword )
          break;
        v2 = (int *)sub_552200((_DWORD *)(i + 724), j);
        v7 = rf_clutter_find_by_uid(*v2);
        if ( v7 )
          rf_clutter_toggle_first_two_skins(*(_DWORD *)(v7 + 44));
      }
    }
    *(_DWORD *)(i + 688) &= ~0x40u;
    v11 = 0;
    LOBYTE(v0) = rf_replicator_is_armed((_DWORD *)(i + 736));
    if ( (unsigned __int8)v0 != 1 )
      goto LABEL_23;
    LOBYTE(v0) = rf_replicator_has_elapsed((int *)(i + 736));
    if ( (unsigned __int8)v0 != 1 )
      goto LABEL_23;
    if ( rf_multiplayer_runtime_mode || *(_DWORD *)(i + 704) == -1 )
      goto LABEL_22;
    if ( !rf_replicator_is_armed((_DWORD *)(i + 744)) )
    {
      rf_vector3_copy_return_destination(v6, (float *)(dword_681E38 + 60));
      LOBYTE(v0) = rf_replicator_arm_milliseconds((int *)(i + 744), 50);
      continue;
    }
    LOBYTE(v0) = rf_replicator_has_elapsed((int *)(i + 744));
    if ( (unsigned __int8)v0 == 1 )
    {
      v5 = sub_479EC0(*(_DWORD *)(i + 704));
      *(_BYTE *)(v5 + 68) = *(_BYTE *)(v5 + 68) == 0;
      rf_replicator_reset((_DWORD *)(i + 744));
      if ( rf_trigger_has_direct_load_to_different_level(i) )
        v11 = 1;
LABEL_22:
      rf_trigger_commit_activation(i, *(_DWORD *)(i + 740), v11, 0);
      rf_replicator_reset((_DWORD *)(i + 736));
      LOBYTE(v0) = i;
      *(_DWORD *)(i + 740) = -1;
LABEL_23:
      if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
      {
        v0 = rf_object_resolve_handle(*(_DWORD *)(i + 768));
        v9 = v0;
        if ( v0 )
        {
          if ( !rf_object_has_respawn_inactive_flag(v9) || (*(_DWORD *)(i + 688) & 0x10) != 0 )
          {
            if ( !rf_object_has_respawn_inactive_flag(v9) && (*(_DWORD *)(i + 688) & 0x10) != 0 )
              rf_trigger_set_forward_enabled(i);
          }
          else
          {
            rf_trigger_set_reverse_disabled(i);
          }
          if ( !rf_object_has_respawn_inactive_flag(i) )
          {
            rf_vector_copy((float *)(i + 60), copy_result, (const float *)(v9 + 60));
            rf_matrix3_copy((float *)(i + 72), (const float *)(v9 + 72));
          }
          v0 = *(_DWORD *)(v9 + 124) & 2;
          if ( v0 )
            LOBYTE(v0) = rf_object_mark_for_deferred_delete(i);
        }
      }
      continue;
    }
  }
  return v0;
}

