// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB6E0 rf_event_when_countdown_over_update
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Special type75 When_Countdown_Over: require shared dword0x6FC424 mask0x2. Dispatch every authored target as event(-1,-1,1), ELSE mover(id,-1,-1), then clear shared mask0x2 AFTER traversal. Clear occurs even when list empty or no targets resolve; notification is shared rather than one latch per observer. No ordinary-trigger route or direct comparison of remaining countdown seconds here.
int __cdecl rf_event_when_countdown_over_update(int a1)
{
  int result; // eax
  int *v2; // eax
  int *v3; // eax
  int v4; // [esp+0h] [ebp-Ch]
  int *v5; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  result = dword_6FC424 & 2;
  if ( (dword_6FC424 & 2) != 0 )
  {
    for ( i = 0; ; ++i )
    {
      result = rf_receiver_get_first_dword((void *)(a1 + 668));
      if ( i >= result )
        break;
      v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
      v5 = (int *)rf_mission_event_find_by_uid(*v2);
      if ( v5 )
      {
        rf_mission_event_activate(v5, -1, -1, 1);
      }
      else
      {
        v3 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
        v4 = rf_mover_resolve_handle(*v3);
        if ( v4 )
          rf_mover_activate_forward(*(_DWORD *)(v4 + 44), -1, -1);
      }
    }
    dword_6FC424 &= ~2u;
  }
  return result;
}

