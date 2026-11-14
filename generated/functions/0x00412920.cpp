// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412920 rf_object_setup152_construct_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Thiscall152-byte setup receiver. Invokes no-write matrix constructor at+24/+72 and no-write vector constructors at+60/+108/+120. Only effective payload initialization is array24 header at+136: count/capacity/base=0 via capacity0 constructor. Returns receiver; scalar/model/flags/mass/radius and all vector/matrix component bytes remain as supplied. No memset, identity initialization, allocation on capacity0 or outer object creation.
char *__thiscall rf_object_setup152_construct_members(char *this)
{
  rf_matrix3_construct(this + 24);
  rf_vector3_default_construct_noop(this + 60);
  rf_matrix3_construct(this + 72);
  rf_vector3_default_construct_noop(this + 108);
  rf_vector3_default_construct_noop(this + 120);
  rf_array24_construct_capacity(this + 136, 0);
  return this;
}

