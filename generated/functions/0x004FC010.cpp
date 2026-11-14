// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC010 rf_event_make_fly_apply_forward
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type26 Make_Fly. Iterate entity targets and call0x435500(entity,0). The zero argument differs from other callers requesting extra flags; does not directly assign AI mode or target.
int __cdecl rf_event_make_fly_apply_forward(int a1)
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
      sub_435500(v4, 0);
  }
  return result;
}

