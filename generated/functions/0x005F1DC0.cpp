// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1DC0 rf_vani_player_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls rf_vani_player_destroy(this);if low bit of flag BYTE set,operator delete(this). Returns original this pointer (possibly freed). No virtual dispatch or NULL guard.
int *__thiscall rf_vani_player_scalar_deleting_destructor(int *this, char a2)
{
  rf_vani_player_destroy(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

