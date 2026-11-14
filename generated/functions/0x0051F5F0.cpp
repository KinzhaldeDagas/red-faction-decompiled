// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051F5F0 rf_world_render_sky_room_camera_centered
// UNREALRED VERIFIED [authored-sky-renderer] Renders one authored sky room as a background shell: computes the room-bounds center, translates that center to the current camera position, installs the inverse of the optional sky rotation matrix, draws the sky room first, and restores render state.
int __cdecl rf_world_render_sky_room_camera_centered(int a1, int a2, int a3)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  const float *v6; // eax
  _BYTE v8[36]; // [esp+4h] [ebp-90h] BYREF
  float v9[3]; // [esp+28h] [ebp-6Ch] BYREF
  float out_vector[3]; // [esp+34h] [ebp-60h] BYREF
  float copy_result[3]; // [esp+40h] [ebp-54h] BYREF
  float scaled_result[3]; // [esp+4Ch] [ebp-48h] BYREF
  float sum_result[3]; // [esp+58h] [ebp-3Ch] BYREF
  float lhs[3]; // [esp+64h] [ebp-30h] BYREF
  float v15[9]; // [esp+70h] [ebp-24h] BYREF

  unk_930A38 = 1;
  rf_vector3_default_construct_noop(lhs);
  rf_matrix3_construct((char *)v15);
  rf_renderer_copy_current_view_transform(lhs, v15);
  v3 = rf_vector_add((const float *)(a2 + 8), sum_result, (const float *)(a2 + 20));
  v4 = rf_vector_multiply_scalar(v3, scaled_result, 0.5);
  rf_vector_copy(&flt_A420BC, copy_result, v4);
  v5 = rf_vector_subtract(lhs, out_vector, &flt_A420BC);
  rf_vector_copy(&flt_A5A0EC, v9, v5);
  *(_DWORD *)&byte_98967F[756197] = a3;
  if ( a3 )
  {
    v6 = (const float *)rf_matrix3_inverse_to_output(*(const void **)&byte_98967F[756197], (int)v8);
    rf_matrix3_copy(&flt_A5A0C8, v6);
  }
  rf_renderer_draw_sorted_translucent_faces_view_scope(a2);
  rf_world_submit_room_effect_callbacks(0, a2, 1);
  rf_world_draw_sorted_callbacks_around_liquid(a2, a1, 0, 0);
  unk_930A38 = 0;
  rf_vector3_zero_return_destination(&flt_A5A0EC);
  *(_DWORD *)&byte_98967F[756197] = 0;
  return rf_renderer_set_depth_clear_enabled(1u);
}

