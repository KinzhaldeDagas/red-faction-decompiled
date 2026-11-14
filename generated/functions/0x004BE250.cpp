// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BE250 rf_embedded_vector4_matrix16_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Thiscall receiver, no stack arguments, returns receiver. Calls no-write vec3 default at+4 and no-write matrix default at+16. Writes NO payload bytes, including first DWORD0 and all vector/matrix components; no identity/zero initialization or allocation.
char *__thiscall rf_embedded_vector4_matrix16_construct_noop(char *this)
{
  rf_vector3_default_construct_noop(this + 4);
  rf_matrix3_construct(this + 16);
  return this;
}

