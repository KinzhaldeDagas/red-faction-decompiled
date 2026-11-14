// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004124C0 rf_entity_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Thiscall ECX entity pointer plus one stack flags DWORD, RET4, EAX original entity pointer even after deletion. Always calls
// member destructor4124F0 first; iff flags bit0 is set calls scalar operator delete on the original pointer. Other flag bits ignored. No NULL guard, array-delete count, pool-slot
// removal or game-level destroy lifecycle. Does not use returned EAX of member cleanup as a success predicate.
void *__thiscall rf_entity_scalar_deleting_destructor(void *this, char a2)
{
  rf_entity_destroy_members(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

