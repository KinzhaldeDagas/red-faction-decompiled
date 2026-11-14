// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005609B0 rf_string_equals_case_insensitive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): cdecl(RFString,cstr). If stored extent==0 and incoming pointerNULL OR incoming byte0NUL, returns true without inspecting object buffer. Otherwise requires nonzero extent and incoming pointer nonnull, then _stricmp(object.buffer,cstr)==0. Nonzero extent with null buffer can fault; stale extent0 with nonempty buffer is treated empty for null/empty input. Negative extent counts as nonzero. No locale-independent normalization or extent-vs-strlen repair.
// UNREALRED VERIFIED [combat-reaction-literal-names-20261111]: RFL none/glock tests use this whole RFString/CString comparison;5609E8 calls _stricmp on original buffers with no trim. Whitespace padding changes those reserved-word decisions even though ASCII letter case does not. Keep quoted/binary string payload separate from source-text trivia skipping.
bool __cdecl rf_string_equals_case_insensitive(int a1, char *String2)
{
  if ( !*(_DWORD *)a1 && (!String2 || !*String2) )
    return 1;
  if ( *(_DWORD *)a1 && String2 )
    return _stricmp(*(const char **)(a1 + 4), String2) == 0;
  return 0;
}

