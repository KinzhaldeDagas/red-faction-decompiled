// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CDA20 rf_particle_emitter344_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Thiscall 344-byte runtime emitter constructor; returns receiver. No-op vectors at +8,+20,+164, no-op 76-byte descriptor at +80, and no-op particle120 sentinel constructor at +176.
// Timestamp constructor writes -1 at +340. Does not otherwise initialize parent/index +4, cached room +76, enabled +320, alternate timing +316/+324, particle links, or emitter list
// links +328/+332. Runtime initialize and system startup supply their own fields later.
int *__thiscall rf_particle_emitter344_construct(int *this)
{
  rf_vector3_default_construct_noop(this + 2);
  rf_vector3_default_construct_noop(this + 5);
  rf_particle_descriptor76_construct_noop((int)(this + 20));
  rf_vector3_default_construct_noop(this + 41);
  rf_particle120_construct_noop((int)(this + 44));
  rf_timestamp4_construct_invalid(this + 85);
  return this;
}

