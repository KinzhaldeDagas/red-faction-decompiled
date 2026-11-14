// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A070 rf_character_record_destroy_members
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Destroys the single148-byte embedded descriptor at+6592 through vector-destructor helper. Does not traverse animation-handle list, reset cache header or free the containing6744-byte object.
void __thiscall rf_character_record_destroy_members(char *this)
{
  `eh vector destructor iterator'(this + 6592, 0x94u, 1, rf_v3c_asset148_destroy_base);
}

