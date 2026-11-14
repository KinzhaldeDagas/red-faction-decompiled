// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00477B40 rf_level_set_logical_name
// UNREALRED VERIFIED [level-lifecycle-20261028]: Compares caller C string to current RF level-name string0x6FC31C with stricmp; if different clears dword0x6FC3A8. Always assigns supplied name to RF string0x6FC31C. No null input check or path normalization; changing case only does not clear auxiliary global.
_DWORD *__cdecl rf_level_set_logical_name(char *String1)
{
  const char *v1; // eax

  v1 = rf_string_object_c_str_or_empty(unk_6FC31C);
  if ( _stricmp(String1, v1) )
    dword_6FC3A8 = 0;
  return rf_string_assign_from_cstr(unk_6FC31C, String1);
}

