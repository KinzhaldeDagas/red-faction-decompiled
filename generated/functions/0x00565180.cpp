// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565180 rf_model_handle_get_runtime_pointer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl handle. If tag1,2or3 returns DWORD4;otherwiseNULL. No cache definition8 return, type-specific conversion, null-handle guard or allocation. Definition-only tag2/3 handles can returnNULL.
int __cdecl rf_model_handle_get_runtime_pointer(int *a1)
{
  int v2; // [esp+0h] [ebp-8h]

  v2 = *a1;
  if ( *a1 == 1 )
    return a1[1];
  if ( v2 == 2 )
    return a1[1];
  if ( v2 == 3 )
    return a1[1];
  return 0;
}

