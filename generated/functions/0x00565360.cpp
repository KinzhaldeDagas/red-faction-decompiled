// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565360 rf_model_handle_enable_private_materials_get_table
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): If handle material80NULL, calls allocator565480. Then UNCONDITIONALLY sets active byte84=1, outputs count from5653B0 and pointer80, returns output-pointer address. Unsupported allocation cases can leave pointerNULL while active flag set; existing pointer not validated against recomputed count. No cloning when pointer already present, failure status or ownership transfer.
_DWORD *__cdecl rf_model_handle_enable_private_materials_get_table(int a1, int *a2, _DWORD *a3)
{
  if ( !*(_DWORD *)(a1 + 80) )
    rf_model_handle_allocate_private_materials((int *)a1);
  *(_BYTE *)(a1 + 84) = 1;
  *a2 = rf_model_handle_private_material_count((int *)a1);
  *a3 = *(_DWORD *)(a1 + 80);
  return a3;
}

