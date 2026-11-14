// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580090 rf_renderer_draw_face_batch_alternate_dispatch
// UNREALRED VERIFIED [impact-callbacks-20261028]: If global enable0x663F2C nonzero AND selector0x187CC9C==102 delegates six arguments to0x5DEC70. Otherwise no draw; AL is branch-dependent selector/uninitialized value. Alternate path selected by world modebit2; do not infer wireframe from this wrapper alone.
char __cdecl rf_renderer_draw_face_batch_alternate_dispatch(int a1, int a2, int a3, int a4, char a5, char a6)
{
  char result; // al

  if ( dword_663F2C )
  {
    result = dword_187CC9C;
    if ( dword_187CC9C == 102 )
      return rf_renderer_draw_face_batch_alternate_backend_102(a1, a2, a3, a4, a5, a6);
  }
  return result;
}

