// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BDB20 rf_common_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Thiscall receiver, one flags DWORD,RET4. Always destroys inherited common members through412580; then operator-delete(receiver) only when flags mask1 set. Returns original receiver bits, even freed. Other bits ignored; no vector-cookie mode, class-specific string/array/scene cleanup or pointer nulling here.
void *__thiscall rf_common_scalar_deleting_destructor(void *this, char a2)
{
  rf_common_object_destroy_embedded_members((int)this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

