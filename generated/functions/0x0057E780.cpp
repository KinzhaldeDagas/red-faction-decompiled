// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E780 rf_renderer_submit_immediate_polygon
// UNREALRED VERIFIED [reflection-binding-20260903]: Renderer front end for immediate polygon submission. It forwards vertex count/list, vertex-format flags, packed state, override-depth flag, and depth to the D3D8 backend only when backend id 102 is active.
char __cdecl rf_renderer_submit_immediate_polygon(int a1, int a2, int a3, int a4, char a5, float a6)
{
  if ( dword_187CC9C == 102 )
    return rf_d3d8_submit_immediate_polygon(a1, a2, a3, a4, a5, a6);
  else
    return 0;
}

