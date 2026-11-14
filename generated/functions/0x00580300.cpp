// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580300 rf_particle_draw_one_backend_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Cdecl(instance,particle index,material time). Only if global renderer selector187CC9C equals102 forwards to rf_renderer_draw_particle_age_shaped_billboard_or_triangle(5DC0D0). Other selectors perform no draw. No particle-index or instance validation,state restoration or alternate backend path here.
void __cdecl rf_particle_draw_one_backend_dispatch(float *a1, int a2, float a3)
{
  if ( dword_187CC9C == 102 )
    rf_renderer_draw_particle_age_shaped_billboard_or_triangle(a1, a2, a3);
}

