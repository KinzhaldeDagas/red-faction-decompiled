// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CD3E0 rf_particle120_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Thiscall 120-byte particle constructor, returns receiver. Calls no-op vector constructors at +12,+24,+108 and no-op RGBA constructors at +40,+44,+48. Consequently performs no
// particle payload initialization: list links, owner, age/life, colors, radius, bitmap/frame count, flags, pool index, room, and emitter pointer retain their previous bytes. List and
// runtime initialization occur elsewhere.
int __thiscall rf_particle120_construct_noop(int this)
{
  rf_vector3_default_construct_noop((void *)(this + 12));
  rf_vector3_default_construct_noop((void *)(this + 24));
  rf_rgba8_default_construct_noop((void *)(this + 40));
  rf_rgba8_default_construct_noop((void *)(this + 44));
  rf_rgba8_default_construct_noop((void *)(this + 48));
  rf_vector3_default_construct_noop((void *)(this + 108));
  return this;
}

