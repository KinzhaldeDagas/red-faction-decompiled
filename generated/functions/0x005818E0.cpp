// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005818E0 rf_renderer_plane_faces_camera_backend_wrapper
// UNREALRED VERIFIED [renderer-overlays-20261028]: Returns backendselector0x187CC9C==102 AND0x5C5640(normal,point). Other backends returnfalse. No frustum test or geometry mutation.
bool __cdecl rf_renderer_plane_faces_camera_backend_wrapper(int a1, float *a2)
{
  return dword_187CC9C == 102 && rf_renderer_plane_faces_camera(a1, a2);
}

