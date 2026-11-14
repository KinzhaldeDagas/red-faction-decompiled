// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A500 rf_geomod_cutter_registry_find_name
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl C-string name; signed ascending scan i<count of12-byte records6EDEE0. Exact null-aware case-insensitive RFString/CString comparison; returns FIRST matching index without
// inspecting solid pointer, or-1 if none. Does not append unknown names, trim/strip extension, create solid or retry cached NULL. Unlike find_or_append it cannot grow registry. NULL
// input may match stored empty RFString through shared equality semantics; no separate NULL guard.
int __cdecl rf_geomod_cutter_registry_find_name(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_6EDEDC; ++i )
  {
    if ( rf_string_equals_case_insensitive((int)&byte_6EDEE0[12 * i], String2) )
      return i;
  }
  return -1;
}

