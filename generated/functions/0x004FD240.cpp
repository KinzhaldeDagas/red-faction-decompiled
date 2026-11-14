// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD240 rf_event_invert_apply_reverse
// UNREALRED VERIFIED [mission-invert-20261020] Invert type3 REVERSE input: ordered forward-target calls(uid,event+0x2AC,-1). Nested events receive forward input retaining trigger context but object context=-1; triggers enable without activating; movers activate; ambient enables. This is an active reverse handler, not base no-op. No later auto-forward.
int __cdecl rf_event_invert_apply_reverse(int a1)
{
  int result; // eax
  int *v2; // eax
  int v3; // [esp-8h] [ebp-Ch]
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v3 = *(_DWORD *)(a1 + 684);
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    rf_mission_target_activate_forward_by_uid(*v2, v3, -1);
  }
  return result;
}

