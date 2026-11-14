// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DBE40 rf_renderer_draw_debug_endpoint_arrow
// UNREALRED VERIFIED [renderer-mesh-20261028]: Arguments twoXYZ endpoints and RGBintegers. Rejects length<0.00001. Arrowbase=start+0.9*(end-start),sideaxis=normalized cross(globalcamera thirdrow0x18CD4CC,end-start). Transforms endpoints and rejects if cameraX AND cameraY exactlyequal,regardless differingZ. Draws shaft and two winglines endpoint->base +/- side*(length/16),state0x182ABA0 and suppliedRGB/alpha255. No explicit degeneratecross guard or state/color restoration; drawresults ignored.
void __cdecl rf_renderer_draw_debug_endpoint_arrow(
        float a1,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6,
        int a7,
        int a8,
        int a9)
{
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float v14[3]; // [esp+Ch] [ebp-110h] BYREF
  float v15[3]; // [esp+18h] [ebp-104h] BYREF
  float v16[3]; // [esp+24h] [ebp-F8h] BYREF
  float copy_result[3]; // [esp+30h] [ebp-ECh] BYREF
  float v18[3]; // [esp+3Ch] [ebp-E0h] BYREF
  float v19[3]; // [esp+48h] [ebp-D4h] BYREF
  float scaled_result[3]; // [esp+54h] [ebp-C8h] BYREF
  float v21; // [esp+60h] [ebp-BCh]
  float v22[12]; // [esp+64h] [ebp-B8h] BYREF
  float scalar; // [esp+94h] [ebp-88h]
  float vector[3]; // [esp+98h] [ebp-84h] BYREF
  _BYTE v25[12]; // [esp+A4h] [ebp-78h] BYREF
  float sum_result[3]; // [esp+B0h] [ebp-6Ch] BYREF
  float lhs[3]; // [esp+BCh] [ebp-60h] BYREF
  float destination[3]; // [esp+C8h] [ebp-54h] BYREF
  float rhs[3]; // [esp+D4h] [ebp-48h] BYREF
  float v30[12]; // [esp+E0h] [ebp-3Ch] BYREF
  float out_vector[3]; // [esp+110h] [ebp-Ch] BYREF

  rf_vector3_set_components_return_destination(rhs, a1, a2, a3);
  rf_vector3_set_components_return_destination(lhs, a4, a5, a6);
  rf_vector_subtract(lhs, out_vector, rhs);
  if ( rf_vector3_length(out_vector) >= 0.000009999999747378752 )
  {
    v9 = rf_vector_multiply_scalar(out_vector, scaled_result, 0.89999998);
    rf_vector_add(rhs, sum_result, v9);
    rf_vector_cross(&flt_18CD4CC, vector, out_vector);
    rf_vector_normalize(vector);
    rf_vector_prefix_construct_noop(v30);
    rf_vector_prefix_construct_noop(v22);
    rf_renderer_transform_world_point_backend_wrapper((int)v30, rhs);
    rf_renderer_transform_world_point_backend_wrapper((int)v22, lhs);
    if ( v22[0] != v30[0] || v22[1] != v30[1] )
    {
      rf_render_color_set_rgba8(a7, a8, a9, 255);
      rf_renderer_draw_projected_line_backend_wrapper((int)v30, (int)v22, dword_182ABA0);
      rf_vector3_default_construct_noop(destination);
      rf_vector3_default_construct_noop(v25);
      v21 = rf_vector3_length(out_vector) / 8.0;
      scalar = v21 * 0.5;
      rf_vector_normalize(out_vector);
      v10 = rf_vector_multiply_scalar(vector, v19, scalar);
      v11 = rf_vector_add(sum_result, v18, v10);
      rf_vector_copy(destination, copy_result, v11);
      rf_renderer_transform_world_point_backend_wrapper((int)v30, destination);
      rf_render_color_set_rgba8(a7, a8, a9, 255);
      rf_renderer_draw_projected_line_backend_wrapper((int)v30, (int)v22, dword_182ABA0);
      v12 = rf_vector_multiply_scalar(vector, v16, scalar);
      v13 = rf_vector_subtract(sum_result, v15, v12);
      rf_vector_copy(destination, v14, v13);
      rf_renderer_transform_world_point_backend_wrapper((int)v30, destination);
      rf_render_color_set_rgba8(a7, a8, a9, 255);
      rf_renderer_draw_projected_line_backend_wrapper((int)v30, (int)v22, dword_182ABA0);
    }
  }
}

