// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005817B0 rf_renderer_transform_world_point_backend_wrapper
// UNREALRED VERIFIED [renderer-overlays-20261028]: Backendselector0x187CC9C==102 delegates output clipvertex and worldpoint to0x582180,returning outcode byte. Other selectors return0 without initializing output. No projection or temporary allocation in wrapper.
char __cdecl rf_renderer_transform_world_point_backend_wrapper(int a1, float *a2)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_transform_world_point_to_clip_vertex(a1, a2);
  else
    return 0;
}

