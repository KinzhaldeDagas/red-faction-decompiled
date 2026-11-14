// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501140 rf_event_unhide_update_pending
// UNREALRED VERIFIED [mission-protection-20261020] UnHide frame owner: shared deadline+0x2B8 gates pending show, then pending hide. Each admitted pass rearms500ms. Show reactivates non-entities, no-player cases, field+504==2, masako_fighter/capek/gryphon, globalgate0x476D00, or geometry-obstructed player+2004->target+60 segments(mask3). Other entities keep pending-show set for retry. Hide unconditionally calls0x4BC7D0 on resolved commons and clears pending-hide. Show checked first can postpone hide by500ms; missing IDs do not block completion.
// UNREALRED VERIFIED [mission-visibility-20261020] Pending-show retries re-run every eligible link, including duplicates and already-reactivated targets, while any ordinary entity remains in unobstructed view. Missing handles are skipped without retaining the request. Show pass always rearms500ms before visiting links, even for an empty list, and can indefinitely postpone pending-hide. Setters do not reset this deadline or cancel the opposite byte. Common type0 is the entity case; target+0x1F8==2 is the loader-authored friendliness exception.
// UNREALRED VERIFIED [mission-unhide-20261020] Live standalone UnrealRed dispatch now retains independent pending-show/hide requests, uses the shared game-clock poll deadline, and visits authored links in order. Eye-to-entity-foot query uses retained current world/moving geometry with source face admission. Global sequence-owner bypass remains unimplemented; streaming suspension and UE capsule-foot mapping are host adaptations, not RF structures.
char __fastcall rf_event_unhide_update_pending(int a1)
{
  int first_dword; // eax
  int *v2; // eax
  int *v3; // eax
  char v6; // [esp+7h] [ebp-9h]
  int v7; // [esp+8h] [ebp-8h]
  int v8; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]
  int j; // [esp+Ch] [ebp-4h]

  LOBYTE(first_dword) = a1;
  if ( *(_BYTE *)(a1 + 700) == 1 )
  {
    LOBYTE(first_dword) = rf_replicator_has_elapsed((int *)(a1 + 696));
    if ( (unsigned __int8)first_dword == 1 )
    {
      rf_replicator_arm_milliseconds((int *)(a1 + 696), 500);
      v6 = 1;
      for ( i = 0; ; ++i )
      {
        first_dword = rf_receiver_get_first_dword((void *)(a1 + 668));
        if ( i >= first_dword )
          break;
        v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
        v7 = rf_object_resolve_handle(*v2);
        if ( v7 )
        {
          if ( !dword_681E38
            || *(_DWORD *)(v7 + 36)
            || *(_DWORD *)(v7 + 504) == 2
            || rf_string_equals_case_insensitive(v7 + 24, "masako_fighter")
            || rf_string_equals_case_insensitive(v7 + 24, "capek")
            || rf_string_equals_case_insensitive(v7 + 24, "gryphon")
            || rf_unhide_global_owner_present()
            || rf_geometry_segment_is_obstructed((float *)(dword_681E38 + 2004), (float *)(v7 + 60), 3, nullptr) )
          {
            rf_object_reactivate_from_respawn((_DWORD *)v7);
          }
          else
          {
            v6 = 0;
          }
        }
      }
      if ( v6 == 1 )
      {
        LOBYTE(first_dword) = a1;
        *(_BYTE *)(a1 + 700) = 0;
      }
    }
  }
  if ( *(_BYTE *)(a1 + 701) == 1 )
  {
    LOBYTE(first_dword) = rf_replicator_has_elapsed((int *)(a1 + 696));
    if ( (unsigned __int8)first_dword == 1 )
    {
      rf_replicator_arm_milliseconds((int *)(a1 + 696), 500);
      for ( j = 0; j < rf_receiver_get_first_dword((void *)(a1 + 668)); ++j )
      {
        v3 = (int *)sub_552200((_DWORD *)(a1 + 668), j);
        v8 = rf_object_resolve_handle(*v3);
        if ( v8 )
        {
          if ( dword_681E38 )
            rf_object_mark_hidden_inactive(v8);
          else
            rf_object_mark_hidden_inactive(v8);
        }
      }
      *(_BYTE *)(a1 + 701) = 0;
      LOBYTE(first_dword) = 1;
    }
  }
  return first_dword;
}

