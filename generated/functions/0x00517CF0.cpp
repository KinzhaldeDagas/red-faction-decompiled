// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517CF0 rf_room460_scalar_deleting_destructor_517cf0
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall room,flags low BYTE,RET4. Invokes room destructor515D90,then scalar-deletes receiver when flags&1;returns original receiver even if freed. No vector cookie/count handling or own room registration;member/ownership cleanup delegated to body. Solid888 destructor calls withflags1 for rooms144.
void *__thiscall rf_room460_scalar_deleting_destructor_517cf0(void *this, char a2)
{
  rf_room460_destroy_members((int)this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

