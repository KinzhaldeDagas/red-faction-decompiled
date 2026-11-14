// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517D20 rf_solid_aux_scalar_deleting_destructor_517d20
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall object,flags low BYTE,RET4. Calls existing portal-member no-op initializer/destructor helper;flags&1 scalar-deletes receiver. Returns original pointer even when freed. No array/cookie handling or independent member traversal. Called for solid auxiliary pointer array180;does not establish additional object fields or resource ownership.
void *__thiscall rf_solid_aux_scalar_deleting_destructor_517d20(void *this, char a2)
{
  rf_portal_member_noop_initializer();
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

