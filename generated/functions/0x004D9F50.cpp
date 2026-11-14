// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D9F50 rf_physics_shape_recompute_radius_and_axis_bounds
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl physics-shape pointer. Sets float248=0; loops signed element count from collection252, re-reading count each iteration. Element accessor uses24-byte stride; each record first three floats are sphere offset, float12 radius. Computes float(length(offset)+radius), applies native rf_float_maximum_two_values to current extent, stores float248 each time. Builds endpoints center92 minus/plus that scalar in all components, then axis bounds264/276 through rf_segment_bounds_build, forwarding its EAX. Empty/nonpositive count leaves extent0 and point bounds. No own pointer, element, finite or sphere-radius validation.
float *__cdecl rf_physics_shape_recompute_radius_and_axis_bounds(int a1)
{
  float *element_address_unchecked; // eax
  double v3; // [esp+8h] [ebp-28h]
  float v4; // [esp+10h] [ebp-20h]
  int v5[3]; // [esp+14h] [ebp-1Ch] BYREF
  int v6[3]; // [esp+20h] [ebp-10h] BYREF
  int i; // [esp+2Ch] [ebp-4h]

  *(float *)(a1 + 248) = 0.0;
  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 252)); ++i )
  {
    element_address_unchecked = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 252), i);
    v3 = rf_vector3_length(element_address_unchecked);
    v4 = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 252), i) + 12) + v3;
    *(float *)(a1 + 248) = rf_float_maximum_two_values(*(float *)(a1 + 248), v4);
  }
  rf_vector3_subtract_scalar_from_components((float *)(a1 + 92), (float *)v6, *(float *)(a1 + 248));
  rf_vector3_add_scalar_to_components((float *)(a1 + 92), (float *)v5, *(float *)(a1 + 248));
  return rf_segment_bounds_build((float *)(a1 + 264), (float *)(a1 + 276), (float *)v6, (float *)v5);
}

