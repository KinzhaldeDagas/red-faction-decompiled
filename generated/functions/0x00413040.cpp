// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413040 rf_physics_hit_record_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Thiscall receiver,no stack arguments. Calls no-op vector constructors at0(point),12(normal),36(velocity),returns receiver. Writes NO hit-record bytes, including fraction24,material28,scalar32,UID48,raw material52,liquid56,face60,extra64. No default fraction1,zero normal,invalid UID,allocation or pointer guard; callers seed needed fields.
char *__thiscall rf_physics_hit_record_construct_noop(char *this)
{
  rf_vector3_default_construct_noop(this);
  rf_vector3_default_construct_noop(this + 12);
  rf_vector3_default_construct_noop(this + 36);
  return this;
}

