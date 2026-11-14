// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD330 rf_event_never_leave_vehicle_apply_reverse
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic reverse type80. Resolve entity targets and clear entity+0x814 bit0x80 only. Does not force an exit or modify association id+0x200 directly.
int __cdecl rf_event_never_leave_vehicle_apply_reverse(int a1)
{
  int result; // eax
  int *v2; // eax
  int v3; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v3 = rf_entity_resolve_handle(*v2);
    if ( v3 )
      *(_DWORD *)(v3 + 2068) &= ~0x80u;
  }
  return result;
}

