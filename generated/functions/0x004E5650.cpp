// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E5650 rf_player_apply_loaded_render_options
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): Assumes player nonNULL. Copy bytes3906->projected-shadows global,3907->663F04; zero-extend3908 into renderer category-light allow setter; DWORD3924->global1C99890. Reduction mode from DWORD3920 EXACT1->1,EXACT2->2,all other values->0. Player BYTE3912 NONZERO selects mip-filter backend argument0, zero selects1. Return final backend EAX. No gamma application here (restore helper handles it), option-record validation, device rebuild or rollback.
int __cdecl rf_player_apply_loaded_render_options(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  rf_projected_shadows_enabled = *(_BYTE *)(a1 + 3906);
  byte_663F04 = *(_BYTE *)(a1 + 3907);
  rf_renderer_set_category_light_allow_byte(*(_BYTE *)(a1 + 3908));
  unk_1C99890 = *(_DWORD *)(a1 + 3924);
  v2 = *(_DWORD *)(a1 + 3920);
  if ( v2 == 1 )
  {
    rf_bitmap_set_global_reduction_mode(1);
  }
  else if ( v2 == 2 )
  {
    rf_bitmap_set_global_reduction_mode(2);
  }
  else
  {
    rf_bitmap_set_global_reduction_mode(0);
  }
  if ( *(_BYTE *)(a1 + 3912) )
    return rf_renderer_set_mip_filter_backend_dispatch(0);
  else
    return rf_renderer_set_mip_filter_backend_dispatch(1);
}

