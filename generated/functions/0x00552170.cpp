// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00552170 rf_pointer_array_scalar_deleting_destructor_552170
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall array-header receiver,one stack flags DWORD(low BYTE tested),RET4. Always destroys backing storage through existing pointer-array destructor;if flags&1 then scalar operator delete(receiver). Returns original receiver even if freed. No vector cookie/count handling or element-object destruction in this adapter. Distinct body/address from other shared array deleting-destructor adapters;existing library/function classification retained.
void **__thiscall rf_pointer_array_scalar_deleting_destructor_552170(void **this, char a2)
{
  rf_pointer_array_destroy_backing_storage(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

