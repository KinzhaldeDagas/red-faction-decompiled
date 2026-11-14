// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417E00 rf_monitor_update_registry
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Visit circular monitor list. Clear each record flags+0x38 bit2; resolve monitor clutter by id+0xC, restoring bit2 iff clutter common flags+0x7C bit0x10 is set. Only when clutter resolves, elapsed deadline+0x24 cycles selection via0x417EC0 and rearms with trunc(interval_seconds*1000+0.5), using interval at record+0x28. Missing clutter leaves record linked with bit2 cleared. Selection failure does not suppress rearming, and no render-dirty flag is cleared here.
char rf_monitor_update_registry()
{
  int v0; // eax
  int i; // [esp+0h] [ebp-8h]

  LOBYTE(v0) = dword_6807E4;
  for ( i = dword_6807E4; (_DWORD *)i != &dword_6807E4; i = *(_DWORD *)i )
  {
    *(_DWORD *)(i + 56) &= ~2u;
    v0 = rf_clutter_find_by_uid(*(_DWORD *)(i + 12));
    if ( v0 )
    {
      if ( (*(_DWORD *)(v0 + 124) & 0x10) != 0 )
        *(_DWORD *)(i + 56) |= 2u;
      LOBYTE(v0) = rf_replicator_has_elapsed((int *)(i + 36));
      if ( (unsigned __int8)v0 == 1 )
      {
        rf_monitor_cycle_selected_entity(i);
        LOBYTE(v0) = rf_replicator_arm_milliseconds((int *)(i + 36), (int)(*(float *)(i + 40) * 1000.0 + 0.5));
      }
    }
  }
  return v0;
}

