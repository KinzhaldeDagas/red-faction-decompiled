// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CD30 rf_corpse_refresh_vmesh_geometry
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Cdecl corpse. Reads named-sphere count from model+128; for each index uses UNCHECKED array24 element in corpse+388 as destination of named-sphere adapter, with returned radius written to a separate local and discarded. Does not resize array or check count against array capacity. Recomputes physics radius/axis bounds for state+136, then copies outer radius+384 into common radius+120. Returns bounds-helper EAX, not a normalized success code; no model/null/index/finite guard.
int __cdecl rf_corpse_refresh_vmesh_geometry(int a1)
{
  float *element_address_unchecked; // eax
  int result; // eax
  int v3; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  float v5; // [esp+8h] [ebp-4h] BYREF

  v3 = rf_model_handle_named_sphere_count_adapter(*(_DWORD **)(a1 + 128));
  for ( i = 0; i < v3; ++i )
  {
    element_address_unchecked = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i);
    rf_model_handle_get_named_sphere_adapter(*(_DWORD **)(a1 + 128), i, element_address_unchecked, &v5);
  }
  result = rf_physics_shape_recompute_radius_and_axis_bounds(a1 + 136);
  *(float *)(a1 + 120) = *(float *)(a1 + 384);
  return result;
}

