// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CE0D0 rf_particle_emitter_has_nonnegative_parent_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Thiscall emitter, returns full EAX Boolean 0 or 1 for signed DWORD [emitter+4]>=0 via SETNL. This is the parent/index value copied from the first argument of emitter runtime
// initialization. No owner resolution, liveness, room, enabled, or timestamp check. Particle update uses it to gate emitter extent accumulation at +160 relative to origin +164.
BOOL __thiscall rf_particle_emitter_has_nonnegative_parent_index(_DWORD *this)
{
  return *(this + 1) >= 0;
}

