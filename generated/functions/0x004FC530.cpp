// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC530 rf_event_invert_apply_forward
// UNREALRED VERIFIED [mission-invert-20261020] Invert type3 FORWARD input: ordered duplicate-preserving reverse-target calls(uid,event+0x2AC,-1,0). Direct triggers disable, movers stop (suppression=0), ambient disables; nested events receive reverse input and BOTH context slots=-1 via0x4F74A0. No direct-light operation. No later auto-forward.
int __cdecl rf_event_invert_apply_forward(int a1)
{
  int result; // eax
  int *v2; // eax
  int v3; // [esp-Ch] [ebp-10h]
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v3 = *(_DWORD *)(a1 + 684);
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    rf_mission_target_activate_reverse_by_uid(*v2, v3, -1, 0);
  }
  return result;
}

