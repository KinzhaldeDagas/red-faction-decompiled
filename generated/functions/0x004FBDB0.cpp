// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FBDB0 rf_event_turn_off_physics_apply_forward
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type62 Turn_Off_Physics. Resolve target as common object; only when common+0x7C bit0x08000000 clear call physics deactivate(owner+0x88). Independently resolve same target as entity, test0x43C910 predicate and, when true, OR entity+0x814 bit0x800. If local player exists and its association+0x200 equals entity id, call detach0x434C80(local player). Second branch is not gated by first common-flag condition.
int __cdecl rf_event_turn_off_physics_apply_forward(int a1)
{
  int result; // eax
  int *v2; // eax
  int *v3; // eax
  int v4; // [esp+0h] [ebp-Ch]
  int v5; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v5 = rf_object_resolve_handle(*v2);
    if ( v5 && (*(_DWORD *)(v5 + 124) & 0x8000000) == 0 )
      rf_physics_state_deactivate(v5 + 136);
    v3 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v4 = rf_entity_resolve_handle(*v3);
    if ( rf_entity_class_flag1000(v4) )
    {
      *(_DWORD *)(v4 + 2068) |= 0x800u;
      if ( dword_681E38 )
      {
        if ( *(_DWORD *)(dword_681E38 + 512) == *(_DWORD *)(v4 + 44) )
          rf_entity_try_detach_with_safe_exit(dword_681E38);
      }
    }
  }
  return result;
}

