// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041BA30 rf_glare_definition_find_name_case_sensitive
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl C string. Scans signed indices from0 to retained globalCount0x680AE0, RFString at table0x680DD8+52*i. Uses strcmp equality, returns FIRST matching index or -1. Case-sensitive; does not normalize, allocate, mutate table, clamp count64 or guard null input.
int __cdecl rf_glare_definition_find_name_case_sensitive(const char *a1)
{
  int i; // [esp+14h] [ebp-4h]

  for ( i = 0; i < dword_680AE0; ++i )
  {
    if ( !strcmp(a1, rf_string_object_c_str_or_empty(&byte_680DD8[52 * i])) )
      return i;
  }
  return -1;
}

