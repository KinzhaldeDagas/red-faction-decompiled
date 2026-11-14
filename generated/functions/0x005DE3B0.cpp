// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DE3B0 rf_renderer_draw_textured_stretched_diamond
// UNREALRED VERIFIED [renderer-lighting-20261028]: Arguments worldstart,worldend,size,packedstate. If squaredsegmentlength<0.001,dispatches aspectbillboard atstart,angle0,size unchanged. Otherwise uses viewnormal=-camera thirdrow0x18CD4CC,side=normalized cross(viewnormal,normalized(end-start)),longaxis=normalized cross(side,viewnormal). halfsize=size/2. Builds diamondpoints start+longaxis*(dot(longaxis,end-start)+halfsize),start+side*halfsize,start-longaxis*halfsize,start-side*halfsize. UV=(0,0),(1,0),(1,1),(0,1). Calls0x5DE2C0 using currentpendingtexture0x187CCE8,currentRGBA,returns result. No explicit viewparallel/zero-size guard. This is a stretched four-point diamond,not endpointwidth beamquad.
char __cdecl rf_renderer_draw_textured_stretched_diamond(float *rhs, float *lhs, float a3, int a4)
{
  float *v5; // eax
  double v6; // st7
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float v11; // [esp+Ch] [ebp-100h]
  float v12[3]; // [esp+10h] [ebp-FCh] BYREF
  float v13[3]; // [esp+1Ch] [ebp-F0h] BYREF
  float scaled_result[3]; // [esp+28h] [ebp-E4h] BYREF
  int v15[3]; // [esp+34h] [ebp-D8h] BYREF
  float copy_result[3]; // [esp+40h] [ebp-CCh] BYREF
  float v17[3]; // [esp+4Ch] [ebp-C0h] BYREF
  float vector[3]; // [esp+58h] [ebp-B4h] BYREF
  float v19[3]; // [esp+64h] [ebp-A8h] BYREF
  float out_vector[3]; // [esp+70h] [ebp-9Ch] BYREF
  float v21[3]; // [esp+7Ch] [ebp-90h] BYREF
  float v22[3]; // [esp+88h] [ebp-84h] BYREF
  float v23[8]; // [esp+94h] [ebp-78h] BYREF
  float destination[3]; // [esp+B4h] [ebp-58h] BYREF
  float v25[3]; // [esp+C0h] [ebp-4Ch] BYREF
  float scalar; // [esp+CCh] [ebp-40h]
  float v27[12]; // [esp+D0h] [ebp-3Ch] BYREF
  float sum_result[3]; // [esp+100h] [ebp-Ch] BYREF

  rf_vector_subtract(lhs, out_vector, rhs);
  if ( rf_vector_length_squared(out_vector) < 0.001 )
    return rf_renderer_world_billboard_aspect_backend_dispatch(rhs, 0.0, a3, a4);
  rf_vector_negate(&flt_18CD4CC, v22);
  rf_vector3_copy_return_destination(destination, out_vector);
  rf_vector_normalize(destination);
  rf_vector_cross(v22, vector, destination);
  rf_vector_normalize(vector);
  v5 = rf_vector_cross(vector, v17, v22);
  rf_vector_copy(destination, copy_result, v5);
  rf_vector_normalize(destination);
  scalar = a3 * 0.5;
  rf_vector_construct_no_unwind((char *)v27, 0xCu, 4, rf_vector3_default_construct_noop);
  rf_vector_construct_no_unwind((char *)v23, 8u, 4, rf_vector3_default_construct_noop);
  v6 = rf_vector_dot(destination, out_vector);
  v11 = v6 + scalar;
  v7 = rf_vector_scale((float *)v15, v11, destination);
  rf_vector_add(rhs, sum_result, v7);
  v27[0] = sum_result[0];
  v27[1] = sum_result[1];
  v27[2] = sum_result[2];
  v8 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
  rf_vector_add(rhs, v21, v8);
  v27[3] = v21[0];
  v27[4] = v21[1];
  v27[5] = v21[2];
  v9 = rf_vector_multiply_scalar(destination, v13, scalar);
  rf_vector_subtract(rhs, v25, v9);
  v27[6] = v25[0];
  v27[7] = v25[1];
  v27[8] = v25[2];
  v10 = rf_vector_multiply_scalar(vector, v12, scalar);
  rf_vector_subtract(rhs, v19, v10);
  v27[9] = v19[0];
  v27[10] = v19[1];
  v27[11] = v19[2];
  v23[0] = 0.0;
  v23[1] = 0.0;
  v23[2] = 1.0;
  v23[3] = 0.0;
  v23[4] = 1.0;
  v23[5] = 1.0;
  v23[6] = 0.0;
  v23[7] = 1.0;
  return rf_renderer_submit_textured_world_polygon_rgba(
           dword_187CCE8,
           4,
           (int)v27,
           (int)v23,
           a4,
           rf_render_current_red,
           rf_render_current_green,
           rf_render_current_blue,
           rf_render_current_alpha);
}

