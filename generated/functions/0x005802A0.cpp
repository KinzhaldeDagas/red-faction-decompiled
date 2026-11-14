// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005802A0 rf_renderer_material_billboard_or_beam_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Backend102 forwards material/instance pointer and float to verified billboard-or-beam renderer;otherwise no draw and returns backend value. No local geometry/state handling.
int __cdecl rf_renderer_material_billboard_or_beam_backend_wrapper(float *a1, float a2)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_instance_material_billboard_or_beam(a1, a2);
  return result;
}

