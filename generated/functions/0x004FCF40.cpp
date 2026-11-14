// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FCF40 rf_event_headlamp_state_apply_reverse
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic reverse type53 Headlamp_State. Resolve each entity target then call recursive disable0x436FC0. This is not the neighboring ambient-gain update0x4371C0.
int __cdecl rf_event_headlamp_state_apply_reverse(int a1)
{
  int result; // eax
  int *v2; // eax
  _DWORD *v3; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v3 = (_DWORD *)rf_entity_resolve_handle(*v2);
    if ( v3 )
      rf_entity_disable_headlamp_recursive(v3);
  }
  return result;
}

