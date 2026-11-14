// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC7B0 rf_event_force_monitor_update_apply
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type60 Force_Monitor_Update. Resolve targets as clutter; require descriptor+0x74 bit8, then pass clutter common id+0x2C to0x418160. Does not invoke monitor renderer or cycle selected camera immediately.
int __cdecl rf_event_force_monitor_update_apply(int a1)
{
  int result; // eax
  int *v2; // eax
  int i; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v4 = rf_clutter_find_by_uid(*v2);
    if ( v4 )
    {
      if ( (*(_DWORD *)(*(_DWORD *)(v4 + 660) + 116) & 8) != 0 )
        rf_monitor_invalidate_rendered_flag(*(_DWORD *)(v4 + 44));
    }
  }
  return result;
}

