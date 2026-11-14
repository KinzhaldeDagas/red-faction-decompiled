// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FEF40 rf_event_cyclic_timer_update
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] Run common delayed/special update first. Then require nonzero enabled+0x2B8, and either nonzero repeat byte+0x2C0 or signed current_count+0x2CC<signed limit+0x2C4, and elapsed deadline+0x2C8==1. For each target, independently activate resolved mission event with(-1,-1,1), then forward resolved mover with(mover id,event+0x2AC,event+0x2A8); this body has no ordinary trigger dispatch. After whole scan increment count once and rearm deadline from NOW with trunc(interval_seconds*1000), using float at event+0x2BC. One cycle per update; no catch-up loop, +0.5 rounding, failure-based count rollback, or automatic enabled-byte clear at limit.
char __thiscall rf_event_cyclic_timer_update(int this)
{
  int v1; // eax
  int *v2; // eax
  int *v3; // eax
  int v6; // [esp+4h] [ebp-Ch]
  int *v7; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  rf_mission_event_update_delayed_and_special((char *)this);
  LOBYTE(v1) = this;
  if ( *(_BYTE *)(this + 696) )
  {
    if ( *(_BYTE *)(this + 704) || (v1 = *(_DWORD *)(this + 716), v1 < *(_DWORD *)(this + 708)) )
    {
      LOBYTE(v1) = rf_replicator_has_elapsed((int *)(this + 712));
      if ( (unsigned __int8)v1 == 1 )
      {
        for ( i = 0; i < rf_receiver_get_first_dword((void *)(this + 668)); ++i )
        {
          v2 = (int *)sub_552200((_DWORD *)(this + 668), i);
          v7 = (int *)rf_mission_event_find_by_uid(*v2);
          if ( v7 )
            rf_mission_event_activate(v7, -1, -1, 1);
          v3 = (int *)sub_552200((_DWORD *)(this + 668), i);
          v6 = rf_mover_resolve_handle(*v3);
          if ( v6 )
            rf_mover_activate_forward(*(_DWORD *)(v6 + 44), *(_DWORD *)(this + 684), *(_DWORD *)(this + 680));
        }
        ++*(_DWORD *)(this + 716);
        LOBYTE(v1) = rf_replicator_arm_milliseconds((int *)(this + 712), (int)(*(float *)(this + 700) * 1000.0));
      }
    }
  }
  return v1;
}

