// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BDFD0 rf_particle_definition_destroy_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Invokes verified no-op base callback4580D0 and returns. Does not release material/texture keys,channel definitions or key array; those are shared scene-owned pools. Does not delete containing definition.
void __thiscall rf_particle_definition_destroy_noop(void *this)
{
  rf_shared_noop_destructor_4580d0();
}

