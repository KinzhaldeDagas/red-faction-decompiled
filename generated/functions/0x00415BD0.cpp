// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00415BD0 rf_clutter_class_find_index_by_name
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Cdecl CString. Scans signed index0..<globalcount666B60,compares full argument against RFString at667000+232*i case-insensitively;returns FIRST matching index or-1. Negative/zero count skips scan. No inputNULL,registry-capacity or duplicate validation;no allocation/mutation.
int __cdecl rf_clutter_class_find_index_by_name(char *String1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < unk_666B60; ++i )
  {
    if ( rf_cstring_equals_rf_string_case_insensitive(String1, (int)&byte_667000[232 * i]) )
      return i;
  }
  return -1;
}

