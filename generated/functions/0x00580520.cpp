// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580520 rf_renderer_transformed_solid_faces_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Backend102 forwards solid DWORD,position vector pointer,orientation/context DWORD and unsigned byte to verified transformed-solid face renderer. Unsupported backend no call,nominal EAX backend value;no validation or copy of geometry.
int __cdecl rf_renderer_transformed_solid_faces_backend_wrapper(int a1, float *a2, int a3, unsigned __int8 a4)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_transformed_solid_faces(a1, a2, a3, a4);
  return result;
}

