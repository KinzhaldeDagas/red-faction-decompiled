// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DE2C0 rf_renderer_submit_textured_world_polygon_rgba
// UNREALRED VERIFIED [renderer-lighting-20261028]: Ninearguments bitmap,count,contiguous12-byteXYZarray,contiguous8-byteUVarray,packedstate,RGBAbytes. Sets pendingtexture(bitmap,-1) and currentcolorRGBA,constructs48 local48-byte vertices,transforms each worldpoint via backend1020x582180,sets UV+28/+32,and submits via rf_d3d8_submit_immediate_polygon mask1,no depthoverride. No count<=48,inputpointer or backendselector guard; returns submissionresult. Leaves pendingtexture/currentcolor changed.
char __cdecl rf_renderer_submit_textured_world_polygon_rgba(
        int a1,
        int a2,
        int a3,
        int a4,
        unsigned int a5,
        unsigned __int8 a6,
        unsigned __int8 a7,
        unsigned __int8 a8,
        unsigned __int8 a9)
{
  char v10[2304]; // [esp+4h] [ebp-9C8h] BYREF
  int v11[49]; // [esp+904h] [ebp-C8h] BYREF
  int i; // [esp+9C8h] [ebp-4h]

  rf_renderer_set_pending_texture_handles(a1, -1);
  rf_render_color_set_rgba8(a6, a7, a8, a9);
  rf_vector_construct_no_unwind(v10, 0x30u, 48, rf_vector_prefix_construct_noop);
  for ( i = 0; i < a2; ++i )
  {
    rf_renderer_transform_world_point_to_clip_vertex((int)&v10[48 * i], (float *)(a3 + 12 * i));
    v11[i] = (int)&v10[48 * i];
    *(float *)(v11[i] + 28) = *(float *)(a4 + 8 * i);
    *(float *)(v11[i] + 32) = *(float *)(a4 + 8 * i + 4);
  }
  return rf_d3d8_submit_immediate_polygon(a2, (int)v11, 1u, a5, 0, 0.0);
}

