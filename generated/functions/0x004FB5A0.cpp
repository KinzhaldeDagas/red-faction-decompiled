// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB5A0 rf_event_when_hit_update
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Special type52 When_Hit update. If shared delayed-activation deadline event+0x298 is armed, return without polling. Otherwise ANY common target with common flags+0x7C mask0x00200000 admits a scan of complete target vector. For each target activate resolved event(-1,-1,1), ELSE resolve/activate mover(id,-1,-1); ordinary triggers not handled. No local latch, hit-flag clear or timer rearm in this body, so retained hit bits can trigger on later updates. The watched targets and output targets are same authored vector.
int __cdecl rf_event_when_hit_update(int a1)
{
  int result; // eax
  int *v2; // eax
  int *v3; // eax
  int *v4; // eax
  int v5; // [esp+0h] [ebp-14h]
  int *v6; // [esp+4h] [ebp-10h]
  int v7; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]
  int j; // [esp+Ch] [ebp-8h]
  unsigned __int8 v10; // [esp+13h] [ebp-1h]

  result = rf_replicator_is_armed((_DWORD *)(a1 + 664));
  if ( !(_BYTE)result )
  {
    v10 = 0;
    for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 668)); ++i )
    {
      v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
      v7 = rf_object_resolve_handle(*v2);
      if ( v7 && (*(_DWORD *)(v7 + 124) & 0x200000) != 0 )
      {
        v10 = 1;
        break;
      }
    }
    result = v10;
    if ( v10 == 1 )
    {
      for ( j = 0; ; ++j )
      {
        result = rf_receiver_get_first_dword((void *)(a1 + 668));
        if ( j >= result )
          break;
        v3 = (int *)sub_552200((_DWORD *)(a1 + 668), j);
        v6 = (int *)rf_mission_event_find_by_uid(*v3);
        if ( v6 )
        {
          rf_mission_event_activate(v6, -1, -1, 1);
        }
        else
        {
          v4 = (int *)sub_552200((_DWORD *)(a1 + 668), j);
          v5 = rf_mover_resolve_handle(*v4);
          if ( v5 )
            rf_mover_activate_forward(*(_DWORD *)(v5 + 44), -1, -1);
        }
      }
    }
  }
  return result;
}

