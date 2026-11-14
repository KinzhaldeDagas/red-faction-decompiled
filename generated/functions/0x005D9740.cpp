// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D9740 rf_debug_draw_world_line_backend_102
// UNREALRED VERIFIED [item-pickups-20261028]: Constructs two48-byte projected vertex objects, transforms/projects each caller world point via0x5817B0, then delegates to0x5D9620(vertices,packed render state). Returns that helper result. Backend selector check is in wrapper0x57E740.
char __usercall rf_debug_draw_world_line_backend_102@<al>(double a1@<st0>, float *a2, float *a3, int a4)
{
  _BYTE v5[48]; // [esp+0h] [ebp-60h] BYREF
  _BYTE v6[48]; // [esp+30h] [ebp-30h] BYREF

  rf_vector_prefix_construct_noop(v6);
  rf_vector_prefix_construct_noop(v5);
  rf_renderer_transform_world_point_backend_wrapper((int)v6, a2);
  rf_renderer_transform_world_point_backend_wrapper((int)v5, a3);
  return rf_renderer_clip_and_draw_projected_line(a1, (int)v6, (int)v5, a4);
}

