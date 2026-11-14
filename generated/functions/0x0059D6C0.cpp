// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059D6C0 rf_cstring_lowercase_in_place
// UNREALRED VERIFIED [string-pool-stream-20261028]: Measures strlen once,then replaces each byte with CRT tolower result,returns input pointer. MODIFIES input despite misleading const char pointer in existing decompiler prototype. Does not change terminator,allocate memory,check null or cast characters through unsigned char before CRT call.
const char *__cdecl rf_cstring_lowercase_in_place(const char *a1)
{
  signed int v1; // kr00_4
  signed int i; // [esp+14h] [ebp-4h]

  v1 = strlen(a1);
  for ( i = 0; i < v1; ++i )
    a1[i] = tolower(a1[i]);
  return a1;
}

