// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DADC0 rf_renderer_draw_wire_cylinder_16_segments
// UNREALRED VERIFIED [renderer-mesh-20261028]: Arguments worldcenter,orientationmatrix,radius,fullheight,packedstate. Builds two16-point rings in localXZ with y=+/-height/2,angles0..15*pi/8. Rotates each point bymatrix,addscenter,transforms to48-byte clipvertices. Draws16 upperringedges,16 lowerringedges and16 axialedges through0x57E710. Returns1 regardless individualdraw/clippingresults. No caps/fill or dimension/matrix validation; uses currentglobalcolor.
char __cdecl rf_renderer_draw_wire_cylinder_16_segments(float *rhs, float *a2, float a3, float a4, int a5)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float v10[3]; // [esp+4h] [ebp-684h] BYREF
  float v11[3]; // [esp+10h] [ebp-678h] BYREF
  float v12[3]; // [esp+1Ch] [ebp-66Ch] BYREF
  float copy_result[3]; // [esp+28h] [ebp-660h] BYREF
  float sum_result[3]; // [esp+34h] [ebp-654h] BYREF
  float v15[3]; // [esp+40h] [ebp-648h] BYREF
  int v16; // [esp+4Ch] [ebp-63Ch]
  float v17; // [esp+50h] [ebp-638h]
  float v18[3]; // [esp+54h] [ebp-634h] BYREF
  float destination[3]; // [esp+60h] [ebp-628h] BYREF
  float v20; // [esp+6Ch] [ebp-61Ch]
  float v21; // [esp+70h] [ebp-618h]
  float v22; // [esp+74h] [ebp-614h]
  char v23[772]; // [esp+78h] [ebp-610h] BYREF
  int i; // [esp+37Ch] [ebp-30Ch]
  char v25[772]; // [esp+380h] [ebp-308h] BYREF
  float v26; // [esp+684h] [ebp-4h]

  rf_vector_construct_no_unwind(v23, 0x30u, 16, rf_vector_prefix_construct_noop);
  rf_vector_construct_no_unwind(v25, 0x30u, 16, rf_vector_prefix_construct_noop);
  v26 = 0.0;
  v22 = 0.39269909;
  for ( i = 0; i < 16; ++i )
  {
    rf_vector3_default_construct_noop(destination);
    rf_vector3_default_construct_noop(v18);
    v20 = rf_cos_float(v26) * a3;
    v21 = a4 * 0.5;
    v17 = rf_sin_float(v26) * a3;
    destination[0] = v20;
    destination[1] = v21;
    destination[2] = v17;
    v18[0] = v20;
    v18[1] = -v21;
    v18[2] = v17;
    v5 = rf_matrix3_rotate_vector(destination, v15, a2);
    v6 = rf_vector_add(v5, sum_result, rhs);
    rf_vector_copy(destination, copy_result, v6);
    v7 = rf_matrix3_rotate_vector(v18, v12, a2);
    v8 = rf_vector_add(v7, v11, rhs);
    rf_vector_copy(v18, v10, v8);
    rf_renderer_transform_world_point_backend_wrapper((int)&v23[48 * i], destination);
    rf_renderer_transform_world_point_backend_wrapper((int)&v25[48 * i], v18);
    v26 = v26 + v22;
  }
  for ( i = 0; i < 16; ++i )
  {
    v16 = i + 1;
    if ( i == 15 )
      v16 = 0;
    rf_renderer_draw_projected_line_backend_wrapper((int)&v23[48 * i], (int)&v23[48 * v16], a5);
    rf_renderer_draw_projected_line_backend_wrapper((int)&v25[48 * i], (int)&v25[48 * v16], a5);
    rf_renderer_draw_projected_line_backend_wrapper((int)&v23[48 * i], (int)&v25[48 * i], a5);
  }
  return 1;
}

