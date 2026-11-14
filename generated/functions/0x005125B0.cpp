// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005125B0 rf_projectile_object_construct_embedded_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Thiscall ECX projectile storage,no stack arguments,returns receiver EAX despite saved SDK destructor/void type. Delegates common-object construction4129A0; NO-WRITE vector+692,matrix+704,vector+764,+776 constructors; timestamp+748 initializes invalid(-1). Unwind callback destroys constructed common-object members. No normal-path destruction/free, list insertion, runtime projectile scalar/weapon/voice/light initialization or identity matrix write. Static callback62D540 invokes on projectile sentinel911CE8 and registers cleanup62F510. Corrected application constructor classification and false SDK destructor identity.
void *__thiscall rf_projectile_object_construct_embedded_members(void *self)
{
  rf_common_object_construct_members((char *)self);
  rf_vector3_default_construct_noop((char *)self + 692);
  rf_matrix3_construct((char *)self + 704);
  rf_timestamp4_construct_invalid((int *)self + 187);
  rf_vector3_default_construct_noop((char *)self + 764);
  rf_vector3_default_construct_noop((char *)self + 776);
  return self;
}

