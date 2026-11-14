// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419510 rf_solid_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Thiscall scalar deleting destructor: always calls verified owned-member destructor0x519480, then operator-delete(receiver) iff flags DWORD low bit0 is set. RET4; returns original receiver bits even if freed. Does not null caller pointer or implement vector/cookie deletion. Other flag bits do not affect outer allocation ownership.
char *__thiscall rf_solid_destroy(char *this, char a2)
{
  rf_solid888_destruct_owned_members(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

