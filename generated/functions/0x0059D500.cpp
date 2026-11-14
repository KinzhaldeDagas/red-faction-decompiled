// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059D500 rf_cstring_find_first_substring_case_insensitive
// UNREALRED VERIFIED [string-pool-stream-20261028]: Arguments haystack,needle. Lowercases each into separate fixed stack arrays using CRT tolower,adds terminators,uses case-sensitive strstr helper0x41F140 on folded copies,translates found offset back into ORIGINAL haystack pointer. No match returnsNULL; empty needle returns haystack. Does not modify originals. No length bounds (haystack temporary512 bytes),allocation,null checks or unsigned-char conversion before tolower; signed character inputs are passed directly.
const char *__cdecl rf_cstring_find_first_substring_case_insensitive(const char *a1, const char *a2)
{
  char Str[512]; // [esp+20h] [ebp-418h] BYREF
  char *first_substring; // [esp+220h] [ebp-218h]
  signed int v5; // [esp+224h] [ebp-214h]
  signed int v6; // [esp+228h] [ebp-210h]
  signed int i; // [esp+22Ch] [ebp-20Ch]
  char SubStr[516]; // [esp+230h] [ebp-208h] BYREF

  v5 = strlen(a1);
  v6 = strlen(a2);
  for ( i = 0; i < v5; ++i )
    Str[i] = tolower(a1[i]);
  Str[i] = 0;
  for ( i = 0; i < v6; ++i )
    SubStr[i] = tolower(a2[i]);
  SubStr[i] = 0;
  first_substring = rf_cstring_find_first_substring(Str, SubStr);
  if ( first_substring )
    return &a1[first_substring - Str];
  else
    return nullptr;
}

