// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041C8D0 rf_model_collision_query_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Thiscall receiver, no stack arguments, plain RET. Calls no-op vector constructors at0,48,60,80,92 and no-op matrix constructor at12, returns receiver EAX. Writes NO query bytes, including position/orientation/start/displacement,radius72,flags76 and scratch vectors; does not initialize identity,zero or safe defaults. Callers must supply scalar bounds/flags separately. No own NULL guard.
char *__thiscall rf_model_collision_query_construct_noop(char *this)
{
  rf_vector3_default_construct_noop(this);
  rf_matrix3_construct(this + 12);
  rf_vector3_default_construct_noop(this + 48);
  rf_vector3_default_construct_noop(this + 60);
  rf_vector3_default_construct_noop(this + 80);
  rf_vector3_default_construct_noop(this + 92);
  return this;
}

