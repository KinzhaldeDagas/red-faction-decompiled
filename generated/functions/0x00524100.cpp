// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00524100 rf_world_decal_remove_spatial_links_and_recycle
// UNREALRED VERIFIED [resource-pools-20261028]: If decal+64 owner is nonnull, removes pointer from owner array+156 and all owner neighbors (array+108), then does same for nonnull second owner+68. Otherwise if decal+72 nonnull removes from its array+240. Delegates final recycle to0x524210. Does not itself free record; assumes valid spatial ownership arrays.
int __cdecl rf_world_decal_remove_spatial_links_and_recycle(_DWORD *a1)
{
  int v1; // eax
  int v2; // eax
  int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]

  if ( a1[16] )
  {
    rf_inline_pointer_array_remove_first((_DWORD *)(a1[16] + 156), (int)a1);
    for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1[16] + 108)); ++i )
    {
      v1 = sub_552200((_DWORD *)(a1[16] + 108), i);
      rf_inline_pointer_array_remove_first((_DWORD *)(*(_DWORD *)v1 + 156), (int)a1);
    }
    if ( a1[17] )
    {
      rf_inline_pointer_array_remove_first((_DWORD *)(a1[17] + 156), (int)a1);
      for ( j = 0; j < rf_receiver_get_first_dword((void *)(a1[17] + 108)); ++j )
      {
        v2 = sub_552200((_DWORD *)(a1[17] + 108), j);
        rf_inline_pointer_array_remove_first((_DWORD *)(*(_DWORD *)v2 + 156), (int)a1);
      }
    }
  }
  else if ( a1[18] )
  {
    rf_inline_pointer_array_remove_first((_DWORD *)(a1[18] + 240), (int)a1);
  }
  return rf_world_decal_recycle_record(a1);
}

