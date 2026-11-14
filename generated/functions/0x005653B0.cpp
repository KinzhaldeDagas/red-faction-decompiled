// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005653B0 rf_model_handle_private_material_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Tag1 returns first hierarchy-referenced mesh material count132 ONLY if collection DWORD80<=1; otherwise0. Tag2 sums material counts from every148byte character LOD container at definition6592,count6588. Tag3 returns scene definition136. Other tags0. No output allocation, null/count guard or uniform handling of multiple static LODs.
int __cdecl rf_model_handle_private_material_count(int *a1)
{
  int v2; // [esp+0h] [ebp-18h]
  int v3; // [esp+8h] [ebp-10h] BYREF
  int v4; // [esp+Ch] [ebp-Ch] BYREF
  int i; // [esp+10h] [ebp-8h]
  int v6; // [esp+14h] [ebp-4h]

  v6 = 0;
  v2 = *a1;
  if ( *a1 == 1 )
  {
    if ( *(int *)(a1[1] + 80) <= 1 )
      return *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1[1] + 84) + 4) + 132);
  }
  else if ( v2 == 2 )
  {
    v6 = 0;
    for ( i = 0; i < *(_DWORD *)(a1[2] + 6588); ++i )
    {
      rf_model_container_get_reference_mesh_materials((_DWORD *)(a1[2] + 148 * i + 6592), &v4, &v3);
      v6 += v4;
    }
  }
  else if ( v2 == 3 )
  {
    return *(_DWORD *)(a1[2] + 136);
  }
  return v6;
}

