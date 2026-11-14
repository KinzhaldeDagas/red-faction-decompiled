// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005019E0 rf_event_when_life_reaches_update
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_when_life_reaches update, vtable0x63E410 slot+0xC. If latch byte+0x2B8 nonzero, return. Otherwise scan target vector for ANY resolving entity whose finite life float+0x34<=signed integer threshold+0x2BC (FILD integer, not a float reinterpretation). Set latch1 before target dispatch. On first admission, scan same complete target list, independently activating mission events(-1,-1,1), movers(id,-1,-1), and enabling ordinary triggers. Does not require all entities below threshold, filter dead entities, or call common delayed/special update in this body. No latch reset here.
int __fastcall rf_event_when_life_reaches_update(int a1)
{
  int result; // eax
  int *v2; // eax
  int *v3; // eax
  int *v4; // eax
  int *v5; // eax
  int v7; // [esp+4h] [ebp-14h]
  int v8; // [esp+8h] [ebp-10h]
  int *v9; // [esp+Ch] [ebp-Ch]
  int v10; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]
  int j; // [esp+14h] [ebp-4h]

  result = a1;
  if ( !*(_BYTE *)(a1 + 696) )
  {
    for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 668)); ++i )
    {
      v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
      v10 = rf_entity_resolve_handle(*v2);
      if ( v10 && *(float *)(v10 + 52) <= (double)*(int *)(a1 + 700) )
      {
        *(_BYTE *)(a1 + 696) = 1;
        break;
      }
    }
    result = *(unsigned __int8 *)(a1 + 696);
    if ( *(_BYTE *)(a1 + 696) )
    {
      for ( j = 0; ; ++j )
      {
        result = rf_receiver_get_first_dword((void *)(a1 + 668));
        if ( j >= result )
          break;
        v3 = (int *)sub_552200((_DWORD *)(a1 + 668), j);
        v9 = (int *)rf_mission_event_find_by_uid(*v3);
        if ( v9 )
          rf_mission_event_activate(v9, -1, -1, 1);
        v4 = (int *)sub_552200((_DWORD *)(a1 + 668), j);
        v8 = rf_mover_resolve_handle(*v4);
        if ( v8 )
          rf_mover_activate_forward(*(_DWORD *)(v8 + 44), -1, -1);
        v5 = (int *)sub_552200((_DWORD *)(a1 + 668), j);
        v7 = rf_trigger_find_by_uid(*v5);
        if ( v7 )
          rf_trigger_set_forward_enabled(v7);
      }
    }
  }
  return result;
}

