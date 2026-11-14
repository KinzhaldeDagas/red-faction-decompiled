// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC080 rf_event_make_walk_apply_forward
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type25 Make_Walk. Iterate authored target identifiers, resolve only entities, and call0x435640 for each. Does not directly write locomotion mode, route, or velocity; helper owns its admission and action-profile changes.
int __cdecl rf_event_make_walk_apply_forward(int a1)
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
    v4 = rf_entity_resolve_handle(*v2);
    if ( v4 )
      rf_entity_select_movement13_after_uncrouch(v4);
  }
  return result;
}

