// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FE940 rf_event_when_dead_update
// UNREALRED VERIFIED [mission-when-dead-20261013] After ordinary delayed upkeep, an unarmed and unfired event scans the SAME ordered target array it later forwards. Condition is ALL targets fail rf_object_blocks_when_dead, OR option byte nonzero AND ANY target fails common handle resolution. Empty list satisfies ALL. Latches +0x2B8 BEFORE forwarding each target (including duplicates): type6 event forward activation with -1/-1 context, type8 mover activation, type5 trigger forward enable. The automatic branch bypasses this event own authored delay. An explicitly armed delay postpones the monitor; its expiry can forward and then monitor-forward again in this same update. Existing event targets resolve and are nonblocking, not missing.
// UNREALRED VERIFIED [mission-when-dead-targets-20261013] Common type4 clutter blocks exactly like type0 entities while its source handle resolves with flag 0x00400000, even with life <=0 or a pending corpse timer. The corpse allocated after 75ms owns a NEW handle. Type5 trigger targets are present/nonblocking and are forward-enabled on firing, including authored disabled targets. Source RF trigger flags and per-trigger limits/timers are separate owners.
int __thiscall rf_event_when_dead_update(char *this)
{
  int result; // eax
  int *v2; // eax
  int *v3; // eax
  int *v4; // eax
  int *v5; // eax
  int v7; // [esp+4h] [ebp-18h]
  int v8; // [esp+8h] [ebp-14h]
  int *v9; // [esp+Ch] [ebp-10h]
  int v10; // [esp+10h] [ebp-Ch]
  char v11; // [esp+16h] [ebp-6h]
  char v12; // [esp+17h] [ebp-5h]
  int i; // [esp+18h] [ebp-4h]
  int j; // [esp+18h] [ebp-4h]

  rf_mission_event_update_delayed_and_special(this);
  result = rf_replicator_is_armed((_DWORD *)this + 166);
  if ( !(_BYTE)result && *(this + 696) != 1 )
  {
    v12 = 1;
    v11 = 0;
    for ( i = 0; i < rf_receiver_get_first_dword(this + 668); ++i )
    {
      v2 = (int *)sub_552200((_DWORD *)this + 167, i);
      v10 = rf_object_resolve_handle(*v2);
      if ( !v10 )
        v11 = 1;
      if ( rf_object_blocks_when_dead(v10) )
        v12 = 0;
    }
    if ( v12 == 1 || (result = (int)this, *(this + 697)) && v11 )
    {
      *(this + 696) = 1;
      for ( j = 0; ; ++j )
      {
        result = rf_receiver_get_first_dword(this + 668);
        if ( j >= result )
          break;
        v3 = (int *)sub_552200((_DWORD *)this + 167, j);
        v9 = (int *)rf_mission_event_find_by_uid(*v3);
        if ( v9 )
          rf_mission_event_activate(v9, -1, -1, 1);
        v4 = (int *)sub_552200((_DWORD *)this + 167, j);
        v8 = rf_mover_resolve_handle(*v4);
        if ( v8 )
          rf_mover_activate_forward(*(_DWORD *)(v8 + 44), -1, -1);
        v5 = (int *)sub_552200((_DWORD *)this + 167, j);
        v7 = rf_trigger_find_by_uid(*v5);
        if ( v7 )
          rf_trigger_set_forward_enabled(v7);
      }
    }
  }
  return result;
}

