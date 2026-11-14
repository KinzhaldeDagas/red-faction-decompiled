// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FBD50 rf_event_push_region_state_apply_forward
// UNREALRED VERIFIED [combat-push-region-state-20261104]: Type51 local forward handler iterates every authored target UID at event+0x29C, finds first push-region record via0x478880 and writes enabled byte+0x68=1. Missing UID is a local no-op. Raw state/boolean parameters are not consumed. Afterward generic completion0x4FB3C0 admits type51, so0x4FB200 still routes the same target list through general UID owners; region and event domains must not be treated as mutually exclusive.
int __cdecl rf_event_push_region_state_apply_forward(int a1)
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
      *(_BYTE *)(v3 + 104) = 1;
  }
  return result;
}

