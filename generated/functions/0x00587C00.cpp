// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587C00 rf_character_override_record_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Constructor calls no-op rf_matrix3_construct on receiver+4 then returns receiver. Consequently no record bytes are initialized here: leadingDWORD, nine-float matrix, active flag and weight remain unchanged. Used for48-byte instance override records; separate instance initialization supplies flags/weights.
char *__thiscall rf_character_override_record_construct(char *this)
{
  rf_matrix3_construct(this + 4);
  return this;
}

