// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FCFB0 rf_event_push_region_state_apply_reverse
// UNREALRED VERIFIED [combat-push-region-state-20261104]: Type51 local reverse handler iterates authored target UIDs, first-matches via0x478880 and writes enabled byte+0x68=0. Missing UID is a local no-op; raw state/boolean fields are not read. Generic completion still forwards reverse afterward, with0x4FB200 supplying mover suppression=1 to0x4F74A0. Preserve direction through ordinary deferred event resumption.
int __cdecl rf_event_push_region_state_apply_reverse(int a1)
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
    v3 = rf_push_region_find_by_uid(*v2);
    if ( v3 )
      *(_BYTE *)(v3 + 104) = 0;
  }
  return result;
}

