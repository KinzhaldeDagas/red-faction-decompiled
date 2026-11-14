// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417EC0 rf_monitor_cycle_selected_entity
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Only vectors with count>1 cycle. Scan for first vector entry equal to selected identifier+0x10; choose next entry or wrap to first, store it, then resolve that new entity. If raw mode+8==2 and entity resolves, change mode to0. Does not skip invalid entries, change selection when current id is absent from vector, clear rendered flag4, or rearm timer.
int __cdecl rf_monitor_cycle_selected_entity(_DWORD *a1)
{
  int result; // eax
  _DWORD *v2; // eax
  int i; // [esp+4h] [ebp-4h]

  result = rf_receiver_get_first_dword(a1 + 6);
  if ( result > 1 )
  {
    for ( i = 0; ; ++i )
    {
      result = rf_receiver_get_first_dword(a1 + 6);
      if ( i >= result )
        break;
      if ( a1[4] == *(_DWORD *)sub_552200(a1 + 6, i) )
      {
        if ( i >= rf_receiver_get_first_dword(a1 + 6) - 1 )
          v2 = (_DWORD *)sub_552200(a1 + 6, 0);
        else
          v2 = (_DWORD *)sub_552200(a1 + 6, i + 1);
        a1[4] = *v2;
        result = rf_entity_resolve_handle(a1[4]);
        if ( a1[2] == 2 )
        {
          if ( result )
          {
            result = (int)a1;
            a1[2] = 0;
          }
        }
        return result;
      }
    }
  }
  return result;
}

