// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566C00 rf_character_instance_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Calls585940 to clear actions/unlink instance; if low flag bit1 set calls operator delete on receiver. Returns original receiver bits even if freed. Other flag bits have no effect. Does not itself free base-character cache/clip pools; cleanup early-out on NULL base pointer is preserved.
int *__thiscall rf_character_instance_scalar_deleting_destructor(int *this, char a2)
{
  rf_character_instance_unlink_and_clear_actions(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

