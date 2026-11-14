// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7010 rf_string_pool_intern_case_insensitive
// UNREALRED VERIFIED [string-pool-stream-20261028]: Thiscall pool,C string. NULL input returns0. Scans exactly string count DWORD+16 strings from base+0,advancing strlen+1,case-insensitive _stricmp. Returns FIRST equal existing pointer; if no match,appends through0x5E6F50 and returns new pointer. No capacity,used-byte-bound,ownership or base-pointer validation; relies on count and NUL-terminated packed strings. Does not sort or hash entries; preserves original casing of first string.
char *__thiscall rf_string_pool_intern_case_insensitive(char **this, char *String2)
{
  char *String1; // [esp+14h] [ebp-8h]
  char *i; // [esp+18h] [ebp-4h]

  if ( !String2 )
    return nullptr;
  String1 = *this;
  for ( i = nullptr; (int)i < (int)*(this + 4) && _stricmp(String1, String2); ++i )
    String1 += strlen(String1) + 1;
  if ( i == *(this + 4) )
    return (char *)rf_string_pool_copy_c_string(this, String2);
  else
    return String1;
}

