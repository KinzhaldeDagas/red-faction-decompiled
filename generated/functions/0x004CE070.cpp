// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CE070 rf_particle_emitter_enable
// UNREALRED VERIFIED [world-uid-ownership]: Transitions emitter enabled byte +0x140 to one and resets its embedded spawn deadline only when it was previously disabled.
int __thiscall rf_particle_emitter_enable(int this)
{
  int result; // eax

  result = this;
  if ( *(_BYTE *)(this + 320) != 1 )
  {
    *(_BYTE *)(this + 320) = 1;
    return rf_replicator_arm_milliseconds((int *)(this + 340), 0);
  }
  return result;
}

