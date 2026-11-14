// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005810A0 rf_volume136_construct_members_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Calls no-op vector/matrix constructors on center8,orientation24,dimensions60,offset76,bounds92/104,cameraLocal124;returns receiver. Used for136-byte sphere/box volume allocation. Does not initialize tag,RGB,strength,radius,caches or set identity;creator explicitly writes required fields later.
char *__thiscall rf_volume136_construct_members_noop(char *this)
{
  rf_vector3_default_construct_noop(this + 8);
  rf_matrix3_construct(this + 24);
  rf_vector3_default_construct_noop(this + 60);
  rf_vector3_default_construct_noop(this + 76);
  rf_vector3_default_construct_noop(this + 92);
  rf_vector3_default_construct_noop(this + 104);
  rf_vector3_default_construct_noop(this + 124);
  return this;
}

