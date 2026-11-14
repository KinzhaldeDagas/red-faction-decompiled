// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581780 rf_clip_extended_vertex_update_outcode_backend
// UNREALRED VERIFIED [extended-clip-20261028]: If backend selector0x187CC9C equals102,delegates vertex to0x582160,which recomputes byte24 from camera-space position and returns it. Otherwise returns0 without changing vertex outcode. No projection or UV interpolation in wrapper.
char __cdecl rf_clip_extended_vertex_update_outcode_backend(int a1)
{
  if ( dword_187CC9C == 102 )
    return rf_clip_vertex_update_camera_outcode(a1);
  else
    return 0;
}

