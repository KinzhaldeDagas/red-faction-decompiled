// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006068B0 _strstr
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(haystack, needle), returns first complete
// substring start or NULL. Empty needle returns haystack without reading haystack. One-byte needle restores its saved registers, zero-extends first byte into EAX, and tail-jumps
// directly into strchr body609486, leaving the original haystack stack slot in place; this is intentional shared code, not a missing return. Longer needles scan first two bytes, then
// compare remaining bytes in pairs, checking needle terminators before each haystack read. On mismatch restart from the second byte of the previous candidate, retaining overlapping
// matches; haystack NUL before a new candidate returns NULL. Returned pointer borrows haystack; no writes, allocation, locale folding or NULL validation.
char *__cdecl strstr(const char *Str, const char *SubStr)
{
  char v2; // dl
  const char *v3; // edi
  char v4; // dh
  const char *v5; // ecx
  char *v6; // esi
  char v7; // al
  char v9; // ah
  char v10; // al
  char v11; // al

  v2 = *SubStr;
  v3 = Str;
  if ( !*SubStr )
    return (char *)Str;
  v4 = SubStr[1];
  if ( !v4 )
    JUMPOUT(0x609486);
findnext:
  v5 = SubStr;
  v6 = (char *)(v3 + 1);
  if ( *v3 == v2 )
    goto first_char_found;
  if ( *v3 )
  {
    while ( 2 )
    {
      v7 = *v6++;
      while ( v7 == v2 )
      {
first_char_found:
        v7 = *v6++;
        if ( v7 == v4 )
        {
          v3 = v6 - 1;
          while ( 1 )
          {
            v9 = v5[2];
            if ( !v9 )
              break;
            v10 = *v6;
            v6 += 2;
            if ( v10 != v9 )
              goto findnext;
            v11 = v5[3];
            if ( !v11 )
              break;
            v5 += 2;
            if ( v11 != *(v6 - 1) )
              goto findnext;
          }
          return (char *)(v3 - 1);
        }
      }
      if ( v7 )
        continue;
      break;
    }
  }
  return nullptr;
}

