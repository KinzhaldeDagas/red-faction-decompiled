// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057FE00 rf_renderer_draw_debug_rgb_basis
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Copies origin and saves current RGBA bytes. Draws three endpoint-arrow primitives through57FDA0:origin to origin+matrixRow0*length in opaque red,then row1 green,then row2 blue. Matrix rows contiguous3f at0,12,24. Sets global RGBA before each draw;restores original RGBA afterward even unsupported backend skips actual arrows. No normalizing axes,orthogonalizing matrix or skipping zero length. Returns color-setter byte result,not arrow count.
char __cdecl rf_renderer_draw_debug_rgb_basis(float *a1, float *vector, float scalar)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float v10[3]; // [esp+24h] [ebp-88h] BYREF
  float v11[3]; // [esp+30h] [ebp-7Ch] BYREF
  float v12[3]; // [esp+3Ch] [ebp-70h] BYREF
  float v13[3]; // [esp+48h] [ebp-64h] BYREF
  float v14[3]; // [esp+54h] [ebp-58h] BYREF
  float v15[3]; // [esp+60h] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+6Ch] [ebp-40h] BYREF
  float sum_result[3]; // [esp+78h] [ebp-34h] BYREF
  float scaled_result[3]; // [esp+84h] [ebp-28h] BYREF
  float destination; // [esp+90h] [ebp-1Ch] BYREF
  float v20; // [esp+94h] [ebp-18h]
  float v21; // [esp+98h] [ebp-14h]
  unsigned __int8 v22; // [esp+9Ch] [ebp-10h]
  unsigned __int8 v23; // [esp+9Dh] [ebp-Fh]
  unsigned __int8 v24; // [esp+9Eh] [ebp-Eh]
  unsigned __int8 v25; // [esp+9Fh] [ebp-Dh]
  float lhs; // [esp+A0h] [ebp-Ch] BYREF
  float v27; // [esp+A4h] [ebp-8h]
  float v28; // [esp+A8h] [ebp-4h]

  rf_vector3_copy_return_destination(&lhs, a1);
  rf_vector3_default_construct_noop(&destination);
  v23 = rf_render_current_red;
  v22 = rf_render_current_green;
  v24 = rf_render_current_blue;
  v25 = rf_render_current_alpha;
  v3 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
  v4 = rf_vector_add(&lhs, sum_result, v3);
  rf_vector_copy(&destination, copy_result, v4);
  rf_render_color_set_rgba8(255, 0, 0, 255);
  rf_renderer_debug_endpoint_arrow_backend_wrapper(
    lhs,
    v27,
    v28,
    destination,
    v20,
    v21,
    rf_render_current_red,
    rf_render_current_green,
    rf_render_current_blue);
  v5 = rf_vector_multiply_scalar(vector + 3, v15, scalar);
  v6 = rf_vector_add(&lhs, v14, v5);
  rf_vector_copy(&destination, v13, v6);
  rf_render_color_set_rgba8(0, 255, 0, 255);
  rf_renderer_debug_endpoint_arrow_backend_wrapper(
    lhs,
    v27,
    v28,
    destination,
    v20,
    v21,
    rf_render_current_red,
    rf_render_current_green,
    rf_render_current_blue);
  v7 = rf_vector_multiply_scalar(vector + 6, v12, scalar);
  v8 = rf_vector_add(&lhs, v11, v7);
  rf_vector_copy(&destination, v10, v8);
  rf_render_color_set_rgba8(0, 0, 255, 255);
  rf_renderer_debug_endpoint_arrow_backend_wrapper(
    lhs,
    v27,
    v28,
    destination,
    v20,
    v21,
    rf_render_current_red,
    rf_render_current_green,
    rf_render_current_blue);
  return rf_render_color_set_rgba8(v23, v22, v24, v25);
}

