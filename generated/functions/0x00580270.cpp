// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580270 rf_renderer_submit_mesh_faces
// UNREALRED VERIFIED [reflection-binding-20260903]: Renderer front end for mesh-face submission. It dispatches the mesh instance and 15-Hz render time to the decoded D3D8 mesh path only when backend id 102 is active.
int __cdecl rf_renderer_submit_mesh_faces(_DWORD *a1, float a2)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_d3d8_submit_mesh_faces(a1, a2);
  return result;
}

