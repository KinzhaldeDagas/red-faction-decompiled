// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043D940 rf_blood_surface_mark_draw_quad
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Compute current half-size node+4: when finite age<growth duration use sin(age*growth rate)*maximum size, otherwise maximum size. Build4 points center+/-orientation row0*size+/-row1*size with full-square UVs. Use RGB bytes node+0x48..0x4A and FORCE alpha255, binding shared0x6E6230 texture loaded as somenewblood_A.tga with rf_particle_standard_billboard_render_state through0x580490. Updates current size during rendering; no age fade/expiration test or saved alpha use.
char __cdecl rf_blood_surface_mark_draw_quad(float *a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *scalar; // [esp+8h] [ebp-150h]
  float *scalara; // [esp+8h] [ebp-150h]
  float *scalarb; // [esp+8h] [ebp-150h]
  float *scalarc; // [esp+8h] [ebp-150h]
  float v18; // [esp+Ch] [ebp-14Ch]
  float v19[3]; // [esp+10h] [ebp-148h] BYREF
  float v20[3]; // [esp+1Ch] [ebp-13Ch] BYREF
  float v21[3]; // [esp+28h] [ebp-130h] BYREF
  float v22[3]; // [esp+34h] [ebp-124h] BYREF
  float v23[3]; // [esp+40h] [ebp-118h] BYREF
  float v24[3]; // [esp+4Ch] [ebp-10Ch] BYREF
  float v25[3]; // [esp+58h] [ebp-100h] BYREF
  float v26[3]; // [esp+64h] [ebp-F4h] BYREF
  float v27[3]; // [esp+70h] [ebp-E8h] BYREF
  float v28[3]; // [esp+7Ch] [ebp-DCh] BYREF
  float v29[3]; // [esp+88h] [ebp-D0h] BYREF
  float v30[3]; // [esp+94h] [ebp-C4h] BYREF
  float v31[3]; // [esp+A0h] [ebp-B8h] BYREF
  float v32[3]; // [esp+ACh] [ebp-ACh] BYREF
  float v33[3]; // [esp+B8h] [ebp-A0h] BYREF
  float copy_result[3]; // [esp+C4h] [ebp-94h] BYREF
  float sum_result[3]; // [esp+D0h] [ebp-88h] BYREF
  float scaled_result[3]; // [esp+DCh] [ebp-7Ch] BYREF
  float out_vector[3]; // [esp+E8h] [ebp-70h] BYREF
  float v38[3]; // [esp+F4h] [ebp-64h] BYREF
  float v39[8]; // [esp+100h] [ebp-58h] BYREF
  float destination[3]; // [esp+120h] [ebp-38h] BYREF
  float v41[3]; // [esp+12Ch] [ebp-2Ch] BYREF
  float v42[3]; // [esp+138h] [ebp-20h] BYREF
  float v43[3]; // [esp+144h] [ebp-14h] BYREF
  char v44[4]; // [esp+150h] [ebp-8h] BYREF
  float *v45; // [esp+154h] [ebp-4h]

  v45 = a1;
  if ( a1[2] > (double)*a1 )
  {
    v18 = *v45 * v45[4];
    v45[1] = rf_sin_float(v18) * v45[3];
  }
  else
  {
    v45[1] = v45[3];
  }
  rf_vector_construct_no_unwind((char *)destination, 0xCu, 4, rf_vector3_default_construct_noop);
  rf_vector_construct_no_unwind((char *)v39, 8u, 4, rf_vector3_default_construct_noop);
  scalar = rf_vector_multiply_scalar(v45 + 11, scaled_result, v45[1]);
  v1 = rf_vector_multiply_scalar(v45 + 8, v38, v45[1]);
  v2 = rf_vector_subtract(v45 + 5, out_vector, v1);
  v3 = rf_vector_add(v2, sum_result, scalar);
  rf_vector_copy(destination, copy_result, v3);
  scalara = rf_vector_multiply_scalar(v45 + 11, v31, v45[1]);
  v4 = rf_vector_multiply_scalar(v45 + 8, v33, v45[1]);
  v5 = rf_vector_add(v45 + 5, v32, v4);
  v6 = rf_vector_add(v5, v30, scalara);
  rf_vector_copy(v41, v29, v6);
  scalarb = rf_vector_multiply_scalar(v45 + 11, v26, v45[1]);
  v7 = rf_vector_multiply_scalar(v45 + 8, v28, v45[1]);
  v8 = rf_vector_add(v45 + 5, v27, v7);
  v9 = rf_vector_subtract(v8, v25, scalarb);
  rf_vector_copy(v42, v24, v9);
  scalarc = rf_vector_multiply_scalar(v45 + 11, v21, v45[1]);
  v10 = rf_vector_multiply_scalar(v45 + 8, v23, v45[1]);
  v11 = rf_vector_subtract(v45 + 5, v22, v10);
  v12 = rf_vector_subtract(v11, v20, scalarc);
  rf_vector_copy(v43, v19, v12);
  v39[0] = 0.0;
  v39[1] = 0.0;
  v39[2] = 1.0;
  v39[3] = 0.0;
  v39[4] = 1.0;
  v39[5] = 1.0;
  v39[6] = 0.0;
  v39[7] = 1.0;
  v44[0] = *((_BYTE *)v45 + 72);
  v44[1] = *((_BYTE *)v45 + 73);
  v44[2] = *((_BYTE *)v45 + 74);
  v44[3] = -1;
  return rf_renderer_submit_textured_world_polygon_color4_dispatch(
           unk_6E6230,
           4,
           (int)destination,
           (int)v39,
           rf_particle_standard_billboard_render_state,
           v44);
}

