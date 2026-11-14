// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00549F80 rf_pointer_array_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Calls51E930 pointer-array backing destructor on receiver;if flags byte&01 operator-deletes receiver,returns original receiver value (possibly freed). Ignores other flag bits,no array cookie/vector iteration here. Pointed elements not freed and array header not reset by lower destructor.
void **__thiscall rf_pointer_array_scalar_deleting_destructor(void **this, char a2)
{
  rf_pointer_array_destroy_backing_wrapper(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

