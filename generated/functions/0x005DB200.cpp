// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DB200 rf_debug_draw_wire_sphere_backend_102
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Applies packed render state, projects center and estimates subdivision count, clamps via0x40D6A0 to5..32. Draws three principal-axis great-circle loops of caller radius plus three axis diameter segments using projected line helper0x57E710. Uses angle step2*pi/count; loop begins at0 then closes to initial point. Returns1; no public input radius validation here.
char __cdecl rf_debug_draw_wire_sphere_backend_102(float *lhs, float a2, int a3)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  double v6; // st7
  double v7; // st7
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  double v11; // st7
  double v12; // st7
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  float *v19; // eax
  float *scalar; // [esp+8h] [ebp-21Ch]
  float *scalara; // [esp+8h] [ebp-21Ch]
  float v23[3]; // [esp+10h] [ebp-214h] BYREF
  float out_vector[3]; // [esp+1Ch] [ebp-208h] BYREF
  float v25[3]; // [esp+28h] [ebp-1FCh] BYREF
  float v26[3]; // [esp+34h] [ebp-1F0h] BYREF
  float v27[3]; // [esp+40h] [ebp-1E4h] BYREF
  float v28[3]; // [esp+4Ch] [ebp-1D8h] BYREF
  float v29[3]; // [esp+58h] [ebp-1CCh] BYREF
  float v30[3]; // [esp+64h] [ebp-1C0h] BYREF
  float v31[3]; // [esp+70h] [ebp-1B4h] BYREF
  float v32[3]; // [esp+7Ch] [ebp-1A8h] BYREF
  float v33[3]; // [esp+88h] [ebp-19Ch] BYREF
  float copy_result[3]; // [esp+94h] [ebp-190h] BYREF
  float v35[3]; // [esp+A0h] [ebp-184h] BYREF
  float scaled_result[3]; // [esp+ACh] [ebp-178h] BYREF
  float sum_result[3]; // [esp+B8h] [ebp-16Ch] BYREF
  float v38[3]; // [esp+C4h] [ebp-160h] BYREF
  float v39[3]; // [esp+D0h] [ebp-154h] BYREF
  float v40[3]; // [esp+DCh] [ebp-148h] BYREF
  float v41[3]; // [esp+E8h] [ebp-13Ch] BYREF
  float v42; // [esp+F4h] [ebp-130h]
  float v43; // [esp+F8h] [ebp-12Ch]
  float v44; // [esp+FCh] [ebp-128h]
  float v45; // [esp+100h] [ebp-124h]
  float v46[3]; // [esp+104h] [ebp-120h] BYREF
  float vector[3]; // [esp+110h] [ebp-114h] BYREF
  float v48[3]; // [esp+11Ch] [ebp-108h] BYREF
  int i; // [esp+128h] [ebp-FCh]
  float destination[3]; // [esp+12Ch] [ebp-F8h] BYREF
  int v51; // [esp+138h] [ebp-ECh] BYREF
  _BYTE v52[48]; // [esp+13Ch] [ebp-E8h] BYREF
  _BYTE v53[48]; // [esp+16Ch] [ebp-B8h] BYREF
  float v54[9]; // [esp+19Ch] [ebp-88h] BYREF
  _BYTE v55[48]; // [esp+1C0h] [ebp-64h] BYREF
  _BYTE v56[48]; // [esp+1F0h] [ebp-34h] BYREF
  int j; // [esp+220h] [ebp-4h]

  rf_renderer_apply_packed_render_state(a3);
  rf_vector3_default_construct_noop(destination);
  rf_vector_prefix_construct_noop(v55);
  rf_vector_prefix_construct_noop(v52);
  rf_vector_prefix_construct_noop(v53);
  rf_vector_prefix_construct_noop(v56);
  rf_matrix3_construct((char *)v46);
  rf_matrix3_construct((char *)v54);
  rf_matrix3_copy(v46, unk_18CD398);
  rf_matrix3_copy(v54, unk_18CD398);
  rf_renderer_transform_world_point_backend_wrapper((int)v55, lhs);
  v51 = (int)rf_renderer_project_world_width_to_pixels((int)v55, &a2);
  rf_integer_clamp_in_place(&v51, 5, 32);
  for ( i = 0; i < 3; ++i )
  {
    if ( i )
    {
      if ( i == 1 )
      {
        v4 = rf_vector3_set_components_return_destination(v40, 0.0, 1.0, 0.0);
        rf_orientation_matrix_from_direction(v46, v4);
      }
      else if ( i == 2 )
      {
        v5 = rf_vector3_set_components_return_destination(v39, 0.0, 0.0, 1.0);
        rf_orientation_matrix_from_direction(v46, v5);
      }
    }
    else
    {
      v3 = rf_vector3_set_components_return_destination(v41, 1.0, 0.0, 0.0);
      rf_orientation_matrix_from_direction(v46, v3);
    }
    v45 = 0.0;
    v42 = 6.283185482025146 / (double)v51;
    v6 = rf_sin_float(0.0);
    v43 = v6 * a2;
    v7 = rf_cos_float(v45);
    v44 = v7 * a2;
    scalar = rf_vector_multiply_scalar(vector, scaled_result, v44);
    v8 = rf_vector_multiply_scalar(v46, v38, v43);
    v9 = rf_vector_add(lhs, sum_result, v8);
    v10 = rf_vector_add(v9, v35, scalar);
    rf_vector_copy(destination, copy_result, v10);
    rf_renderer_transform_world_point_backend_wrapper((int)v55, destination);
    rf_clip_vertex48_copy_return_destination((int)v52, (int)v55);
    for ( j = 0; j < v51; ++j )
    {
      v11 = rf_sin_float(v45);
      v43 = v11 * a2;
      v12 = rf_cos_float(v45);
      v44 = v12 * a2;
      scalara = rf_vector_multiply_scalar(vector, v31, v44);
      v13 = rf_vector_multiply_scalar(v46, v33, v43);
      v14 = rf_vector_add(lhs, v32, v13);
      v15 = rf_vector_add(v14, v30, scalara);
      rf_vector_copy(destination, v29, v15);
      rf_renderer_transform_world_point_backend_wrapper((int)v53, destination);
      rf_renderer_draw_projected_line_backend_wrapper((int)v52, (int)v53, a3);
      rf_clip_vertex48_copy_return_destination((int)v56, (int)v52);
      rf_clip_vertex48_copy_return_destination((int)v52, (int)v53);
      rf_clip_vertex48_copy_return_destination((int)v53, (int)v56);
      v45 = v45 + v42;
    }
    rf_renderer_draw_projected_line_backend_wrapper((int)v52, (int)v55, a3);
    v16 = rf_vector_multiply_scalar(v48, v28, a2);
    v17 = rf_vector_add(lhs, v27, v16);
    rf_vector_copy(destination, v26, v17);
    rf_renderer_transform_world_point_backend_wrapper((int)v55, destination);
    v18 = rf_vector_multiply_scalar(v48, v25, a2);
    v19 = rf_vector_subtract(lhs, out_vector, v18);
    rf_vector_copy(destination, v23, v19);
    rf_renderer_transform_world_point_backend_wrapper((int)v52, destination);
    rf_renderer_draw_projected_line_backend_wrapper((int)v55, (int)v52, a3);
  }
  return 1;
}

