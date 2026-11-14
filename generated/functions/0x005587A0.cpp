// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005587A0 rf_debug_draw_linked_cylinder_nodes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX pointer-array of node records. Draws node cylinder at XYZ0 with identity orientation, shape fields28/32, cyan if DWORD64 nonzero else green. For each neighbor pointer in node array40, tests reciprocal membership in neighbor40; draws each reciprocal edge only if node address<=neighbor, otherwise draws directed edge. Edge box center midpoint, orientation from normalized direction(node-neighbor), dimensions(2*min(field28),min(field32),Euclidean distance). Nonreciprocal edge gets dark-green midpoint arrow. Draws blue sphere radius0.2 at node+12 after edges. Pointer ordering deduplicates reciprocal links; no graph/record/null/zero-distance checks. Does not mutate graph.
void __thiscall rf_debug_draw_linked_cylinder_nodes(const void *this)
{
  int i; // eax
  float *v2; // eax
  int first_dword; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  double v7; // st7
  float *v8; // [esp+1Ch] [ebp-D4h]
  float *scalar; // [esp+20h] [ebp-D0h]
  float out_vector[3]; // [esp+28h] [ebp-C8h] BYREF
  float copy_result[3]; // [esp+34h] [ebp-BCh] BYREF
  float scaled_result[3]; // [esp+40h] [ebp-B0h] BYREF
  float sum_result[3]; // [esp+4Ch] [ebp-A4h] BYREF
  float v15[3]; // [esp+58h] [ebp-98h] BYREF
  float v16[3]; // [esp+64h] [ebp-8Ch] BYREF
  float v17[3]; // [esp+70h] [ebp-80h] BYREF
  float *rhs; // [esp+7Ch] [ebp-74h]
  float v19[9]; // [esp+80h] [ebp-70h] BYREF
  float v20[3]; // [esp+A4h] [ebp-4Ch] BYREF
  bool v21; // [esp+B3h] [ebp-3Dh]
  float destination[3]; // [esp+B4h] [ebp-3Ch] BYREF
  _BYTE v23[36]; // [esp+C0h] [ebp-30h] BYREF
  float *lhs; // [esp+E4h] [ebp-Ch]
  int j; // [esp+E8h] [ebp-8h]
  int v26; // [esp+ECh] [ebp-4h]

  v26 = 0;
  for ( i = rf_receiver_get_first_dword((void *)this); v26 < i; i = rf_receiver_get_first_dword((void *)this) )
  {
    lhs = *(float **)sub_552200(this, v26);
    if ( *((_DWORD *)lhs + 16) )
      rf_render_color_set_rgba8(0, 255, 255, 255);
    else
      rf_render_color_set_rgba8(0, 255, 0, 255);
    scalar = rf_vector3_set_components_return_destination(v17, 0.0, 0.0, 1.0);
    v8 = rf_vector3_set_components_return_destination(v16, 0.0, 1.0, 0.0);
    v2 = rf_vector3_set_components_return_destination(v15, 1.0, 0.0, 0.0);
    rf_matrix3_construct_from_three_rows((int)v23, v2, v8, scalar);
    rf_renderer_wire_cylinder_backend_wrapper((int)lhs, (int)v23, lhs[7], lhs[8], dword_182ABA0);
    for ( j = 0; ; ++j )
    {
      first_dword = rf_receiver_get_first_dword(lhs + 10);
      if ( j >= first_dword )
        break;
      rhs = *(float **)sub_552200((_DWORD *)lhs + 10, j);
      v21 = rf_pointer_array_find_index((_DWORD *)rhs + 10, (int)lhs) > -1;
      if ( !v21 || lhs <= rhs )
      {
        rf_vector3_default_construct_noop(destination);
        v4 = rf_vector_add(lhs, sum_result, rhs);
        v5 = rf_vector_multiply_scalar(v4, scaled_result, 0.5);
        rf_vector_copy(destination, copy_result, v5);
        rf_matrix3_construct((char *)v19);
        v6 = rf_vector_subtract(lhs, out_vector, rhs);
        rf_orientation_matrix_from_normalized_direction(v19, v6);
        rf_vector3_default_construct_noop(v20);
        v7 = rf_float_minimum_two_values(lhs[7], rhs[7]);
        v20[0] = v7 + v7;
        v20[1] = rf_float_minimum_two_values(lhs[8], rhs[8]);
        v20[2] = rf_vector_distance(lhs, rhs);
        rf_debug_draw_oriented_wire_box((int)destination, (int)v19, (int)v20, dword_182ABA0);
        if ( !v21 )
          rf_renderer_midpoint_arrow_backend_wrapper(*lhs, lhs[1], lhs[2], *rhs, rhs[1], rhs[2], 0, 128, 0);
      }
    }
    rf_render_color_set_rgba8(0, 0, 255, 255);
    rf_debug_draw_wire_sphere_backend_dispatch((int)(lhs + 3), 0.2, dword_187CC5C);
    ++v26;
  }
}

