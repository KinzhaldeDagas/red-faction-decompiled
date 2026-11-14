// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DB080 rf_renderer_draw_wire_cone_16_segments
// UNREALRED VERIFIED [renderer-mesh-20261028]: Arguments worldapex,orientationmatrix,radius,localZoffset,packedstate. Transforms apex once. Builds16 localcirclepoints(radius*cosangle,radius*sinangle,Zoffset),rotates/translates via0x55A4A0,transforms toclipvertices. Draws16 apexspokes and16 closedringedges via0x57E710,returns1 regardless results. Localcircle isXY plane,unlike cylinder helperXZ rings. No dimension/degeneracy checks.
char __cdecl rf_renderer_draw_wire_cone_16_segments(float *a1, float *a2, float a3, float a4, int a5)
{
  int v6; // [esp+4h] [ebp-34Ch]
  float v7[3]; // [esp+8h] [ebp-348h] BYREF
  _BYTE v8[48]; // [esp+14h] [ebp-33Ch] BYREF
  float v9; // [esp+44h] [ebp-30Ch]
  char v10[768]; // [esp+48h] [ebp-308h] BYREF
  int i; // [esp+348h] [ebp-8h]
  float v12; // [esp+34Ch] [ebp-4h]

  rf_vector_construct_no_unwind(v10, 0x30u, 16, rf_vector_prefix_construct_noop);
  rf_vector_prefix_construct_noop(v8);
  rf_renderer_transform_world_point_backend_wrapper((int)v8, a1);
  v12 = 0.0;
  v9 = 0.39269909;
  for ( i = 0; i < 16; ++i )
  {
    rf_vector3_default_construct_noop(v7);
    v7[0] = rf_cos_float(v12) * a3;
    v7[1] = rf_sin_float(v12) * a3;
    v7[2] = a4;
    rf_vector_rotate_translate_in_place(v7, a1, a2);
    rf_renderer_transform_world_point_backend_wrapper((int)&v10[48 * i], v7);
    v12 = v12 + v9;
  }
  for ( i = 0; i < 16; ++i )
  {
    v6 = i + 1;
    if ( i == 15 )
      v6 = 0;
    rf_renderer_draw_projected_line_backend_wrapper((int)v8, (int)&v10[48 * i], a5);
    rf_renderer_draw_projected_line_backend_wrapper((int)&v10[48 * i], (int)&v10[48 * v6], a5);
  }
  return 1;
}

