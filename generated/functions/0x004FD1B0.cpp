// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD1B0 rf_event_shoot_at_apply_reverse
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic reverse type8. Resolve entity targets; restore AI through0x40A2A0(entity+0x2A0), stop weapon firing(entity id,entity+0x2A4), then set entity+0x578=-1. No direct field write to guarded AI target+0x560 in this body.
int __cdecl rf_event_shoot_at_apply_reverse(int a1)
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
    {
      sub_40A2A0(v3 + 168);
      rf_entity_stop_weapon_firing(v3[11], v3[169]);
      v3[350] = -1;
    }
  }
  return result;
}

