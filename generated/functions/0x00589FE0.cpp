// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589FE0 rf_character_record_construct_members
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Constructor for6744-byte base-character record. Runs50 primary-bone constructors at+76,stride76;32 auxiliary-binding constructors at+4796,stride56; one148-byte V3C descriptor constructor/destructor pair at+6592. Returns this. Does not reset name, flags, counters or animation-handle list; separate header reset does that.
char *__thiscall rf_character_record_construct_members(char *this)
{
  rf_vector_construct_no_unwind(
    this + 76,
    0x4Cu,
    50,
    (void *(__thiscall *)(void *))rf_character_primary_bone_record_construct);
  rf_vector_construct_no_unwind(
    this + 4796,
    0x38u,
    32,
    (void *(__thiscall *)(void *))rf_character_aux_binding_record_construct);
  `eh vector constructor iterator'(this + 6592, 0x94u, 1, rf_v3c_asset148_construct_base, rf_v3c_asset148_destroy_base);
  return this;
}

