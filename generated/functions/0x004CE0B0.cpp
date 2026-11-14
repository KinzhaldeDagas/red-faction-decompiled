// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CE0B0 rf_particle_emitter_disable
// UNREALRED VERIFIED [world-uid-ownership]: Clears emitter enabled byte +0x140 without destroying the runtime emitter record.
_BYTE *__thiscall rf_particle_emitter_disable(_BYTE *this)
{
  *(this + 320) = 0;
  return this;
}

