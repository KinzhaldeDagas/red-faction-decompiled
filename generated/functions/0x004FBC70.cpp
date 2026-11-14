// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FBC70 rf_event_item_pickup_state_apply_forward
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type54 Item_Pickup_State. Resolve each target through item-only helper0x473FE0; clear item raw dword+0x2BC mask0x1. Does not collect item, transfer inventory, hide it, or modify other bits in this body.
int __cdecl rf_event_item_pickup_state_apply_forward(int a1)
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
      *(_DWORD *)(v3 + 700) &= ~1u;
  }
  return result;
}

