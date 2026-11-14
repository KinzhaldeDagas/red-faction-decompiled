// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041C9B0 rf_solid_collision_result_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Thiscall receiver,no stack arguments. Calls no-op vector constructors at8(point),20(normal),returns receiver. Writes NO bytes: count0,fraction4,edge metadata32,face36 and vectors remain as supplied. Solid sweep delegate resets count/edge/face separately; initializeByte controls whether it resets fraction. No allocation,zeroing or pointer guard.
int __thiscall rf_solid_collision_result_construct_noop(int this)
{
  rf_vector3_default_construct_noop((void *)(this + 8));
  rf_vector3_default_construct_noop((void *)(this + 20));
  return this;
}

