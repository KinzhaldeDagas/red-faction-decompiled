// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DD990 rf_renderer_draw_debug_translucent_tetrahedron
// UNREALRED VERIFIED [renderer-lighting-20261028]: Fourworldpointarguments. Transforms four48-byte clipvertices; all RGB=(255,255,127),firstthreealpha63,fourthalpha0. Sets pendingtextures-1/-1 and currentcolor0,0,0,0; submits fourtriangles(0,1,2),(0,1,3),(0,2,3),(1,2,3),mask12,state0x187CC64,no depthoverride. Returns lastsubmission result only. No geometryorientation/degeneracy checks or restoration ofglobalcolor/textures.
char __cdecl rf_renderer_draw_debug_translucent_tetrahedron(float *a1, float *a2, float *a3, float *a4)
{
  int v5; // [esp+4h] [ebp-CCh] BYREF
  _BYTE *v6; // [esp+8h] [ebp-C8h]
  _BYTE *v7; // [esp+Ch] [ebp-C4h]
  char v8[48]; // [esp+10h] [ebp-C0h] BYREF
  _BYTE v9[48]; // [esp+40h] [ebp-90h] BYREF
  _BYTE v10[48]; // [esp+70h] [ebp-60h] BYREF
  _BYTE v11[48]; // [esp+A0h] [ebp-30h] BYREF

  rf_vector_construct_no_unwind(v8, 0x30u, 4, rf_vector_prefix_construct_noop);
  rf_renderer_transform_world_point_backend_wrapper((int)v8, a1);
  rf_renderer_transform_world_point_backend_wrapper((int)v9, a2);
  rf_renderer_transform_world_point_backend_wrapper((int)v10, a3);
  rf_renderer_transform_world_point_backend_wrapper((int)v11, a4);
  v8[44] = -1;
  v8[45] = -1;
  v8[46] = 127;
  v8[47] = 63;
  v9[44] = -1;
  v9[45] = -1;
  v9[46] = 127;
  v9[47] = 63;
  v10[44] = -1;
  v10[45] = -1;
  v10[46] = 127;
  v10[47] = 63;
  v11[44] = -1;
  v11[45] = -1;
  v11[46] = 127;
  v11[47] = 0;
  rf_renderer_set_pending_texture_handles(-1, -1);
  rf_render_color_set_rgba8(0, 0, 0, 0);
  v5 = (int)v8;
  v6 = v9;
  v7 = v10;
  rf_renderer_submit_immediate_polygon(3, (int)&v5, 12, unk_187CC64, 0, 0.0);
  v5 = (int)v8;
  v6 = v9;
  v7 = v11;
  rf_renderer_submit_immediate_polygon(3, (int)&v5, 12, unk_187CC64, 0, 0.0);
  v5 = (int)v8;
  v6 = v10;
  v7 = v11;
  rf_renderer_submit_immediate_polygon(3, (int)&v5, 12, unk_187CC64, 0, 0.0);
  v5 = (int)v9;
  v6 = v10;
  v7 = v11;
  return rf_renderer_submit_immediate_polygon(3, (int)&v5, 12, unk_187CC64, 0, 0.0);
}

