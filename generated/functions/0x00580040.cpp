// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580040 rf_renderer_draw_face_batch_backend_dispatch
// UNREALRED VERIFIED [impact-callbacks-20261028]: If global enable0x663F2C nonzero AND renderer selector0x187CC9C==102, delegates six input arguments to0x5EACA0. Other selector returns selector value; disabled return EAX uninitialized/incidental. No stable bool/count return contract or face-array validation.
int __cdecl rf_renderer_draw_face_batch_backend_dispatch(int a1, int a2, int a3, int a4, char a5, char a6)
{
  int result; // eax

  if ( dword_663F2C )
  {
    result = dword_187CC9C;
    if ( dword_187CC9C == 102 )
      return rf_renderer_draw_face_batch_backend_102(a1, a2, a3, a4, a5, a6);
  }
  return result;
}

