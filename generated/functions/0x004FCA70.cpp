// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FCA70 rf_event_ignite_entity_apply
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type82 Ignite_Entity. For entity targets only when stored field entity+0x13D8==0, call0x43E970(entity id,-1) and store return at+0x13D8, including failure0. Existing nonzero fire-owner field suppresses creation; no current-fire liveness check or automatic retry within this call.
// UNREALRED VERIFIED [combat-burn-owner-20261104]: Ignite_Entity type82 traverses stored targets in order, resolves ENTITY only, skips nonzero fire association, otherwise stores43E970(entityHandle,-1) return including0. This explicit route does not use automatic fire-hit armor/player/source gates and does not itself invoke post-hit panic.
int __cdecl rf_event_ignite_entity_apply(int a1)
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
    {
      if ( !*(_DWORD *)(v3 + 5080) )
        *(_DWORD *)(v3 + 5080) = sub_43E970(*(_DWORD *)(v3 + 44), -1);
    }
  }
  return result;
}

