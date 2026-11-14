// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004867A0 rf_material_name_to_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl one argument is pointer to an 8-byte RFString OBJECT (extent0,buffer4), not a direct C string. Native helper5609B0 dereferences those object fields; parser callers pass
// address of their RFString locals. Corrected former const char* prototype to const void* while retaining ABI and name; no new local type introduced. Scans ten canonical C-string
// pointers at0x66283C with exact null-aware case-insensitive RFString/CString equality. IDs:0 Default,1 Rock,2 Metal,3 Flesh,4 Water,5 Lava,6 Solid,7 Sand,8 Ice,9 Glass. First match
// returned; unknown/empty object returns0. No trim, prefix matching, table-row-order mapping or diagnostics. No NULL OBJECT pointer guard.
int __cdecl rf_material_name_to_index(const void *name)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 10; ++i )
  {
    if ( rf_string_equals_case_insensitive((int)name, (char *)rf_material_names[i]) )
      return i;
  }
  return 0;
}

