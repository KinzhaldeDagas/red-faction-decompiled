// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A0A0 rf_character_aux_binding_record_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): For56-byte binding record, calls no-op affine constructor at+4 and returns this. Does not initialize source pointer+0, affine bytes or trailing DWORD+52.
char *__thiscall rf_character_aux_binding_record_construct(char *this)
{
  rf_affine3x4_default_construct_noop(this + 4);
  return this;
}

