// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BE850 rf_trigger_collision_pair_update
// UNREALRED VERIFIED [trigger-geometry-20261020] CORRECTION to the old duplicate-occupant comment: the list check here is numeric NPC policy2 requiring the activating handle in trigger links. It is not an enter/exit deduplication table. Accepted trigger/entity pairs call504B30 with mode0; returned admission does not cause a per-occupant permanent latch.
// UNREALRED VERIFIED [trigger-inside-time-20261021] NPC policy2 linked-handle rejection occurs BEFORE504B30. An unlinked physical candidate therefore does not reset another actor's InsideTime interval; an explicit scan does reach common eligibility and can reset it. Trigger collision pair processing has no stored InsideTime activator.
char __cdecl rf_trigger_collision_pair_update(int a1)
{
  int v2; // [esp+0h] [ebp-Ch]
  int v3; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  if ( *(_DWORD *)(*(_DWORD *)(a1 + 4) + 36) == 5 )
  {
    v2 = *(_DWORD *)(a1 + 4);
    v3 = *(_DWORD *)(a1 + 8);
  }
  else
  {
    if ( *(_DWORD *)(*(_DWORD *)(a1 + 8) + 36) != 5 )
      return 0;
    v2 = *(_DWORD *)(a1 + 8);
    v3 = *(_DWORD *)(a1 + 4);
  }
  if ( *(_DWORD *)(v2 + 708) != 2 )
    goto LABEL_13;
  for ( i = 0;
        i < rf_receiver_get_first_dword((void *)(v2 + 724))
     && *(_DWORD *)sub_552200((_DWORD *)(v2 + 724), i) != *(_DWORD *)(v3 + 44);
        ++i )
  {
    ;
  }
  if ( i == rf_receiver_get_first_dword((void *)(v2 + 724)) )
    return 0;
LABEL_13:
  rf_trigger_test_entity_activation(v2, v3, 0);
  return 1;
}

