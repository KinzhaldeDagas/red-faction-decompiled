// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580430 rf_renderer_debug_tetrahedron_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Backend102 forwards four vector pointers to translucent debug-tetrahedron renderer;unsupported backend returns low byte of backend integer without drawing. No vertex validation or primitive generation here.
char __cdecl rf_renderer_debug_tetrahedron_backend_wrapper(float *a1, float *a2, float *a3, float *a4)
{
  char result; // al

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_debug_translucent_tetrahedron(a1, a2, a3, a4);
  return result;
}

