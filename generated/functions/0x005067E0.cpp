// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005067E0 rf_vclip_effect_destroy_runtime_record
// UNREALRED VERIFIED [resource-pools-20261028]: Releases VFX/model descriptor at record+8 through unknown_libname_26, clears pointer and active byte+60, unlinks circular-list links next+0/prev+4 and clears both. Does not free72-byte pool record. Returns record address; requires valid links.
int __cdecl rf_vclip_effect_destroy_runtime_record(int a1)
{
  rf_model_handle_destroy_cdecl_adapter(*(_DWORD **)(a1 + 8));
  *(_DWORD *)(a1 + 8) = 0;
  *(_BYTE *)(a1 + 60) = 0;
  **(_DWORD **)(a1 + 4) = *(_DWORD *)a1;
  *(_DWORD *)(*(_DWORD *)a1 + 4) = *(_DWORD *)(a1 + 4);
  *(_DWORD *)a1 = 0;
  *(_DWORD *)(a1 + 4) = 0;
  return a1;
}

