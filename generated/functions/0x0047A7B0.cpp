// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A7B0 rf_level_browser_apply_typeahead
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Cdecl no arguments. If deadline_has_elapsed_half_period(6FC974) returns AL EXACT1, empties query6FCC98 using NUL Cstring63878F and rearms1000ms. Empty query AL EXACT1 returns.
// Otherwise traverses entry links+8 from head6FCC54 to sentinel6FCC4C, constructs temporary RFString from entry Cstring48 and runs case-insensitive find(query,start0). Only result
// index0 qualifies: selects FIRST prefix match in list order through text list6FC978(entry,1), destroys temporary and returns. Other substring positions and-1 skipped. Destroys every
// temporary including unwind. No trimming, row filtering, cycling or starting after current selection.
void rf_level_browser_apply_typeahead()
{
  char *v0; // eax
  int v1[2]; // [esp+4h] [ebp-18h] BYREF
  int i; // [esp+Ch] [ebp-10h]
  int v3; // [esp+18h] [ebp-4h]

  if ( rf_clock_deadline_has_elapsed_half_period(&dword_6FC974) )
  {
    rf_string_assign_from_cstr(unk_6FCC98, (char *)&byte_63878F);
    rf_clock_deadline_set_wrapped_offset(&dword_6FC974, 1000);
  }
  if ( !rf_string_is_empty(unk_6FCC98) )
  {
    for ( i = unk_6FCC54; (_UNKNOWN *)i != &unk_6FCC4C; i = *(_DWORD *)(i + 8) )
    {
      rf_string_construct_from_cstr(v1, *(char **)(i + 48));
      v3 = 0;
      v0 = (char *)rf_string_object_c_str_or_empty(unk_6FCC98);
      if ( !rf_string_find_case_insensitive(v1, v0, 0) )
      {
        rf_text_list_select_entry_optional_reveal(unk_6FC978, i, 1);
        v3 = -1;
        rf_string_destroy_buffer(v1);
        return;
      }
      v3 = -1;
      rf_string_destroy_buffer(v1);
    }
  }
}

