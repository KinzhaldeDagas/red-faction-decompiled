// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC0F0 rf_event_shoot_at_apply_forward
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type8 Shoot_At. Resolve entity targets, request guarded AI target clear(-1), assign numeric mode9(-1,-1), then copy raw event+0x30 into entity+0x578. No direct weapon fire here; numeric mode writes do not guarantee a shot or bypass downstream AI gates.
int __cdecl rf_event_shoot_at_apply_forward(int a1)
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
      sub_40BA80((int *)(v3 + 672), -1);
      rf_ai_numeric_mode_write((_DWORD *)(v3 + 672), 9, -1, -1);
      *(_DWORD *)(v3 + 1400) = *(_DWORD *)(a1 + 48);
    }
  }
  return result;
}

