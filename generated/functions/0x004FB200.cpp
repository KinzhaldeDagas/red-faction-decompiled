// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB200 rf_mission_event_forward_targets
// UNREALRED VERIFIED [mission-mover-activation-20261013] Generic forward propagation calls0x4F73F0 with the retained originating trigger/object context. Generic reverse propagation calls0x4F74A0 with final argument1, suppressing mover stopping on that route; do not equate all reverse event chains to Switch target handling.
int __thiscall rf_mission_event_forward_targets(int this, int a2, int a3, char a4)
{
  int result; // eax
  int *v5; // eax
  int *v6; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(this + 668));
    if ( i >= result )
      break;
    if ( a4 == 1 )
    {
      v5 = (int *)sub_552200((_DWORD *)(this + 668), i);
      rf_mission_target_activate_forward_by_uid(*v5, a2, a3);
    }
    else
    {
      v6 = (int *)sub_552200((_DWORD *)(this + 668), i);
      rf_mission_target_activate_reverse_by_uid(*v6, a2, a3, 1);
    }
  }
  return result;
}

