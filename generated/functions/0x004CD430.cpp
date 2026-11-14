// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CD430 rf_particle_pool252_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Thiscall 252-byte pool descriptor constructor; invokes rf_particle120_construct_noop on the two embedded 120-byte sentinel slots at +8 and +128, then returns receiver. Does not
// initialize base +0, capacity +4, sentinel links, or active count +248. rf_particle_pools_initialize performs actual list setup later.
void *__thiscall rf_particle_pool252_construct_noop(void *this)
{
  rf_particle120_construct_noop((int)this + 8);
  rf_particle120_construct_noop((int)this + 128);
  return this;
}

