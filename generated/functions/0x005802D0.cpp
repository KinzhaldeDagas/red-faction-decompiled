// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005802D0 rf_renderer_glow_billboard_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Backend102 forwards pointer to verified instance-glow billboard renderer;otherwise no draw and returns backend value. Does not create glow data or check visibility itself.
int __cdecl rf_renderer_glow_billboard_backend_wrapper(float *a1)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_instance_glow_billboard(a1);
  return result;
}

