// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00520FE0 rf_world_reset_portal_visibility_state
// UNREALRED VERIFIED [authored-sky-renderer] Clears the decoded per-portal visibility byte before each world traversal.
int __cdecl rf_world_reset_portal_visibility_state(int a1)
{
  int result; // eax
  int v2; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  result = rf_receiver_get_first_dword((void *)(a1 + 180));
  v2 = result;
  for ( i = 0; i < v2; ++i )
  {
    *(_BYTE *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 180), i) + 36) = 0;
    result = i + 1;
  }
  return result;
}

