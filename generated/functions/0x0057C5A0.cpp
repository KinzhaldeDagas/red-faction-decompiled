// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057C5A0 rf_path_find_last_dot_or_empty_literal
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl input cstring. Returns pointer to last dot anywhere in input using strrchr, including leading dot or dot in a parent directory. If none returns shared empty literal641545, not source end or NULL. Does not allocate/copy, skip separators or remove dot; no NULL guard.
char *__cdecl rf_path_find_last_dot_or_empty_literal(char *Str)
{
  char *v2; // [esp+0h] [ebp-4h]

  v2 = strrchr(Str, 46);
  if ( v2 )
    return v2;
  else
    return (char *)&unk_641545;
}

