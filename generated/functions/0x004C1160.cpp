// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1160 rf_bolt_emitter_enable
// UNREALRED VERIFIED [world-uid-ownership]: Sets bolt-emitter enabled byte +0x58 to one and resets the embedded runtime deadline/replicator at +0x180.
int __thiscall rf_bolt_emitter_enable(int this)
{
  *(_BYTE *)(this + 88) = 1;
  return rf_replicator_arm_milliseconds((int *)(this + 384), 0);
}

