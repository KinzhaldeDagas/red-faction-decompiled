// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041C920 rf_model_collision_result_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Thiscall receiver,no stack arguments. Calls no-op vector constructors at+4(hit point),+16(normal), returns receiver. Writes NO result bytes; fraction0 and extra28 remain as supplied/uninitialized. Backend initializeByte1 separately seeds fraction1/extra0; this constructor does not. No allocation,zeroing or pointer guard.
int __thiscall rf_model_collision_result_construct_noop(int this)
{
  rf_vector3_default_construct_noop((void *)(this + 4));
  rf_vector3_default_construct_noop((void *)(this + 16));
  return this;
}

