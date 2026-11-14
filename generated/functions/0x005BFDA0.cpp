// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BFDA0 rf_particle_instance_draw_one
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Thin thiscall wrapper forwards receiver,particle index,material-time float to580300. That dispatches only renderer selector187CC9C==102 to the decoded billboard/triangle renderer. No update,age change or particle validation here.
void __thiscall rf_particle_instance_draw_one(float *this, int a2, float a3)
{
  rf_particle_draw_one_backend_dispatch(this, a2, a3);
}

