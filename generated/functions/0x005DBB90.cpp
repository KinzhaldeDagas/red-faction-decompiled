// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DBB90 rf_renderer_draw_debug_midpoint_arrow
// UNREALRED VERIFIED [renderer-mesh-20261028]: Arguments twoXYZ endpoints and RGBintegers. Rejects length<0.00001. Draws mainline using state0x182ABA0,currentcolor suppliedRGB/alpha255. Sideaxis=normalized cross(globalvector0x18CD7F8,end-start). Arrow tip is midpoint+normalizeddirection*(length/8),two wingends midpoint +/- side*(length/16); draws two winglines. Does not place tip at endpoint. No explicit parallel-side guard or state/color restoration; drawresults ignored.
void __cdecl rf_renderer_draw_debug_midpoint_arrow(
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
  float *v14; // eax
  float *v15; // eax
  float v16[3]; // [esp+Ch] [ebp-134h] BYREF
  float v17[3]; // [esp+18h] [ebp-128h] BYREF
  float v18[3]; // [esp+24h] [ebp-11Ch] BYREF
  float v19[3]; // [esp+30h] [ebp-110h] BYREF
  float v20[3]; // [esp+3Ch] [ebp-104h] BYREF
  float v21[3]; // [esp+48h] [ebp-F8h] BYREF
  float copy_result[3]; // [esp+54h] [ebp-ECh] BYREF
  float v23[3]; // [esp+60h] [ebp-E0h] BYREF
  float v24[3]; // [esp+6Ch] [ebp-D4h] BYREF
  float scaled_result[3]; // [esp+78h] [ebp-C8h] BYREF
  float scalar; // [esp+84h] [ebp-BCh]
  float sum_result[3]; // [esp+88h] [ebp-B8h] BYREF
  _BYTE v28[48]; // [esp+94h] [ebp-ACh] BYREF
  float v29; // [esp+C4h] [ebp-7Ch]
  float vector[3]; // [esp+C8h] [ebp-78h] BYREF
  float destination[3]; // [esp+D4h] [ebp-6Ch] BYREF
  float lhs[3]; // [esp+E0h] [ebp-60h] BYREF
  float v33[3]; // [esp+ECh] [ebp-54h] BYREF
  float rhs[3]; // [esp+F8h] [ebp-48h] BYREF
  _BYTE v35[48]; // [esp+104h] [ebp-3Ch] BYREF
  float out_vector[3]; // [esp+134h] [ebp-Ch] BYREF

  rf_vector3_set_components_return_destination(rhs, a1, a2, a3);
  rf_vector3_set_components_return_destination(lhs, a4, a5, a6);
  rf_vector_subtract(lhs, out_vector, rhs);
  if ( rf_vector3_length(out_vector) >= 0.000009999999747378752 )
  {
    v9 = rf_vector_multiply_scalar(out_vector, scaled_result, 0.5);
    rf_vector_add(rhs, sum_result, v9);
    rf_vector_cross(&flt_18CD7F8, vector, out_vector);
    rf_vector_normalize(vector);
    rf_vector_prefix_construct_noop(v35);
    rf_vector_prefix_construct_noop(v28);
    rf_renderer_transform_world_point_backend_wrapper((int)v35, rhs);
    rf_renderer_transform_world_point_backend_wrapper((int)v28, lhs);
    rf_render_color_set_rgba8(a7, a8, a9, 255);
    rf_renderer_draw_projected_line_backend_wrapper((int)v35, (int)v28, dword_182ABA0);
    rf_vector3_default_construct_noop(v33);
    rf_vector3_default_construct_noop(destination);
    scalar = rf_vector3_length(out_vector) / 8.0;
    v29 = scalar / 2.0;
    rf_vector_normalize(out_vector);
    v10 = rf_vector_multiply_scalar(out_vector, v24, scalar);
    v11 = rf_vector_add(sum_result, v23, v10);
    rf_vector_copy(destination, copy_result, v11);
    v12 = rf_vector_multiply_scalar(vector, v21, v29);
    v13 = rf_vector_add(sum_result, v20, v12);
    rf_vector_copy(v33, v19, v13);
    rf_renderer_transform_world_point_backend_wrapper((int)v35, destination);
    rf_renderer_transform_world_point_backend_wrapper((int)v28, v33);
    rf_render_color_set_rgba8(a7, a8, a9, 255);
    rf_renderer_draw_projected_line_backend_wrapper((int)v35, (int)v28, dword_182ABA0);
    v14 = rf_vector_multiply_scalar(vector, v18, v29);
    v15 = rf_vector_subtract(sum_result, v17, v14);
    rf_vector_copy(v33, v16, v15);
    rf_renderer_transform_world_point_backend_wrapper((int)v28, v33);
    rf_render_color_set_rgba8(a7, a8, a9, 255);
    rf_renderer_draw_projected_line_backend_wrapper((int)v35, (int)v28, dword_182ABA0);
  }
}

