// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566290 rf_model_handle_get_lod_group_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Tag1 returns SIGNED IDIV(collection DWORD72,collection DWORD80), no zero-divisor guard. Tag2 returns definition DWORD6588 LOD count. Tag3 returns1,unknown tags0. Does not clamp result, allocate or evaluate scene meshes.
int __cdecl rf_model_handle_get_lod_group_count(int *a1)
{
  int v2; // [esp+0h] [ebp-8h]

  v2 = *a1;
  if ( *a1 == 1 )
    return *(_DWORD *)(a1[1] + 72) / *(_DWORD *)(a1[1] + 80);
  if ( v2 == 2 )
    return *(_DWORD *)(a1[2] + 6588);
  return v2 == 3;
}

