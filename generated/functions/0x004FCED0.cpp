// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FCED0 rf_event_item_pickup_state_apply_reverse
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic reverse type54 Item_Pickup_State. Resolve item targets and OR item+0x2BC mask0x1. Forward/reverse change pickup-state bit, not common visibility or resource lifetime.
int __cdecl rf_event_item_pickup_state_apply_reverse(int a1)
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
    v3 = rf_item_resolve_handle(*v2);
    if ( v3 )
      *(_DWORD *)(v3 + 700) |= 1u;
  }
  return result;
}

