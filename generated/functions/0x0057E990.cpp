// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E990 rf_renderer_world_billboard_aspect_backend_dispatch
// UNREALRED VERIFIED [renderer-lighting-20261028]: If backendselector0x187CC9C==102,forwards worldcenter,angle,size,packedstate to rf_renderer_draw_world_billboard_aspect0x5DA290. Otherwise returns0 without drawing. Current pendingtexture/color used.
char __cdecl rf_renderer_world_billboard_aspect_backend_dispatch(float *a1, float a2, float a3, int a4)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_world_billboard_aspect(a1, a2, a3, a4);
  else
    return 0;
}

