// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005818B0 rf_renderer_project_clip_vertex_backend_wrapper
// UNREALRED VERIFIED [renderer-overlays-20261028]: Backendselector0x187CC9C==102 delegates clipvertex to0x5C5460,returning resulting flagsbyte. Other selectors return0 without changing record. Result is flags,not outcode or normalized success.
char __cdecl rf_renderer_project_clip_vertex_backend_wrapper(int a1)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_project_clip_vertex_cached(a1);
  else
    return 0;
}

