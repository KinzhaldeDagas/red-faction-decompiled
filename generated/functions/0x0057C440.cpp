// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057C440 rf_path_copy_without_last_extension
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Copies source up to last dot into destination and adds NUL; no dot copies entire source including NUL. Dot search covers whole string, with no separator check, so a dot in a parent directory also qualifies. No destination size argument/NULL guard. EAX differs by branch (memcpy destination versus advancing copy pointer), not a uniform length.
_BYTE *__cdecl rf_path_copy_without_last_extension(void *a1, char *Str)
{
  char v2; // cl
  _BYTE *result; // eax
  _BYTE *v4; // [esp+8h] [ebp-10h]
  char *v5; // [esp+Ch] [ebp-Ch]
  char *v6; // [esp+14h] [ebp-4h]

  v6 = strrchr(Str, 46);
  if ( v6 )
  {
    result = memcpy(a1, Str, v6 - Str);
    *((_BYTE *)a1 + v6 - Str) = 0;
  }
  else
  {
    v5 = Str;
    v4 = a1;
    do
    {
      v2 = *v5;
      *v4 = *v5++;
      result = ++v4;
    }
    while ( v2 );
  }
  return result;
}

