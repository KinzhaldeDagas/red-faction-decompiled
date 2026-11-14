// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483940 rf_cstring_find_first_character
// UNREALRED VERIFIED [transfer-scene-20261028]: Arguments C string,character value. Direct wrapper of CRT strchr; returns pointer to first matching byte or null. No null guard or allocation. Scene parent-name parser uses this to locate the first hyphen.
char *__cdecl rf_cstring_find_first_character(char *Str, int Val)
{
  return strchr(Str, Val);
}

