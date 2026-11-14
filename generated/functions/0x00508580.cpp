// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00508580 rf_rail_trail_record80_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Thiscall record storage: invokes no-op vector constructors at0/12 and no-op matrix constructor at24, returns receiver. No component/age/speed/UID/link writes, zero/identity initialization or allocation. Actual ring setup/allocation are507D50/5080E0.
char *__thiscall rf_rail_trail_record80_construct_noop(char *this)
{
  rf_vector3_default_construct_noop(this);
  rf_vector3_default_construct_noop(this + 12);
  rf_matrix3_construct(this + 24);
  return this;
}

