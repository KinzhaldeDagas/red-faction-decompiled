// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD010 rf_event_turn_off_physics_apply_reverse
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic reverse type62. Resolve common-object targets and call0x40D5B0. That helper ORs owner+0x1A8 with0x80000000 and common flags+0x7C with0x06000000; it does NOT call physics_state_deactivate inverse directly, clear entity+0x814 bit0x800, or reattach the player.
int __cdecl rf_event_turn_off_physics_apply_reverse(int a1)
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
    v3 = rf_object_resolve_handle(*v2);
    if ( v3 )
      rf_object_request_physics_reactivation_flags(v3);
  }
  return result;
}

