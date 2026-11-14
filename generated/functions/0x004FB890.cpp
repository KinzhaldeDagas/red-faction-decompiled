// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB890 rf_event_when_try_exit_vehicle_update
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Special type78 vehicle notification update. Require global player entity0x681E38 and local player flags+0x10 mask0x800; clear that mask BEFORE dispatch. Then scan authored targets as event(-1,-1,1), ELSE mover(id,-1,-1). Shared player notification is consumed even with no valid targets, so later observers do not independently receive same flag. Does not inspect actual mounted association, dispatch ordinary triggers, or test event delay in this helper.
void __cdecl rf_event_when_try_exit_vehicle_update(int a1)
{
  int *v1; // eax
  int *v2; // eax
  int v3; // [esp+0h] [ebp-10h]
  int *v4; // [esp+4h] [ebp-Ch]
  int i; // [esp+8h] [ebp-8h]
  char v6; // [esp+Fh] [ebp-1h]

  v6 = 0;
  if ( dword_681E38 && (*(_DWORD *)(rf_local_fpgun_player + 16) & 0x800) != 0 )
  {
    *(_DWORD *)(rf_local_fpgun_player + 16) &= ~0x800u;
    v6 = 1;
  }
  if ( v6 )
  {
    for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 668)); ++i )
    {
      v1 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
      v4 = (int *)rf_mission_event_find_by_uid(*v1);
      if ( v4 )
      {
        rf_mission_event_activate(v4, -1, -1, 1);
      }
      else
      {
        v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
        v3 = rf_mover_resolve_handle(*v2);
        if ( v3 )
          rf_mover_activate_forward(*(_DWORD *)(v3 + 44), -1, -1);
      }
    }
  }
}

