// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC8D0 rf_event_never_leave_vehicle_apply_forward
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type80 Never_Leave_Vehicle. Resolve entity targets and OR entity+0x814 bit0x80 only. Does not resolve, mount, or detach a vehicle directly.
int __cdecl rf_event_never_leave_vehicle_apply_forward(int a1)
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
      *(_DWORD *)(v3 + 2068) |= 0x80u;
  }
  return result;
}

