// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CE330 rf_particle_emitter_definition_find_name
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Cdecl name pointer. Signed loop i=0 while i<globalCount867904; exact null-aware case-insensitive RFString comparison at867A60+8*i, returns FIRST matching source-order index or-1.
// No sort/hash/duplicate merge, count clamp, emitter allocation, mutation or pointer table867800 lookup. Matching semantics delegated to string comparator; no independent empty/NULL
// rejection here.
int __cdecl rf_particle_emitter_definition_find_name(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < unk_867904; ++i )
  {
    if ( rf_string_equals_case_insensitive(8 * i + 8813152, String2) )
      return i;
  }
  return -1;
}

