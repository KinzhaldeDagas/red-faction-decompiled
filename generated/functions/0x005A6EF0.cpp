// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A6EF0 rf_text_list_find_entry_by_trimmed_exact_text
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall list,C string query. Trims only space/tab/LF at both ends into256-byte local through0x59CBA0 WITHOUT capacity bound,then scans entries in order for case-sensitive strcmp(entry.text+48,trimmed query). Returns first entry pointer or0. Stored entry text not trimmed; no null/length/UTF handling or selection mutation.
int __thiscall rf_text_list_find_entry_by_trimmed_exact_text(_DWORD *this, const char *a2)
{
  char Destination[256]; // [esp+18h] [ebp-108h] BYREF
  int i; // [esp+11Ch] [ebp-4h]

  i = 0;
  rf_cstring_trim_space_tab_lf_copy(Destination, a2);
  for ( i = *(this + 183); (_DWORD *)i != this + 181; i = *(_DWORD *)(i + 8) )
  {
    if ( !strcmp(*(const char **)(i + 48), Destination) )
      return i;
  }
  return 0;
}

