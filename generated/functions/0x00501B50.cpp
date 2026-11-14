// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501B50 rf_event_when_armor_reaches_update
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_when_armor_reaches update, vtable0x63E424 slot+0xC. Same one-shot ANY-target admission as life variant, using armor float entity+0x38<=signed integer threshold event+0x2BC. Latch+0x2B8 is set before dispatch to all authored event/mover/ordinary-trigger targets with anonymous(-1,-1) context. Nonzero latch suppresses later evaluation. No dead-entity filter, common delayed update, or latch reset in this body.
int __fastcall rf_event_when_armor_reaches_update(int a1)
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
      if ( v10 && *(float *)(v10 + 56) <= (double)*(int *)(a1 + 700) )
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

