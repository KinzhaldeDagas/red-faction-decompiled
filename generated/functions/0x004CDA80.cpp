// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CDA80 rf_particle_emitter344_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Thiscall emitter destructor delegates only to rf_particle_emitter_detach_live_particles at 0x4CDE00. That helper walks embedded sentinel +176 when its head is nonnull, clears each
// particle's emitter owner +104, and moves the particle to global detached list 0x867C60, leaving it alive to finish naturally; restores emitter sentinel links afterward. Destructor
// itself does not delete emitter allocation/definitions, unlink emitter +328/+332 from active/free lists, or recycle particles to free pools.
void __thiscall rf_particle_emitter344_destroy(int *this)
{
  rf_particle_emitter_detach_live_particles(this);
}

