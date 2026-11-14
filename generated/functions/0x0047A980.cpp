// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A980 rf_level_browser_populate_pack_names
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Cdecl no arguments. Calls VPACK member-name enumeration with extension filter Cstring 'rfl' at6387E0, output Block/count and NULL optional argument. Ignores status/count and walks
// returned NUL-separated names until empty string; adds each to text list6FC978 with(-1,0,0,0), advances strlen+1, then frees Block. No local Block NULL check, list clear, sort,
// deduplication or loose-file enumeration.
void rf_level_browser_populate_pack_names()
{
  int v0; // [esp+10h] [ebp-Ch] BYREF
  const char *i; // [esp+14h] [ebp-8h]
  void *Block; // [esp+18h] [ebp-4h] BYREF

  rf_vpackfile_enumerate_member_names_by_extensions((char *)&off_6387E0, &Block, &v0, nullptr);
  for ( i = (const char *)Block; *i; i += strlen(i) + 1 )
    rf_text_list_add_text_entry(unk_6FC978, (int)i, -1, 0, 0, 0);
  free(Block);
}

