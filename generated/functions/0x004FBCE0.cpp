// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FBCE0 rf_event_headlamp_state_apply_forward
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type53 Headlamp_State. Resolve each target as entity and call recursive headlamp enable0x4370C0. Generic reverse routes separately to0x4FCF40; leaf does not explicitly propagate mission targets.
int __cdecl rf_event_headlamp_state_apply_forward(int a1)
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
      rf_entity_enable_headlamp_recursive(v3);
  }
  return result;
}

