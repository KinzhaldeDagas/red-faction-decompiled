// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057C380 rf_path_replace_last_dot_suffix_unbounded
// UNREALRED VERIFIED [mesh-streaming-20260930] Calls 0x57C440 to remove the input extension, then appends the requested extension (adding a dot if absent). This replaces an existing suffix; it is not an append-only default-extension helper.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl destination, source, requested extension. Calls57C440 to copy source before last dot ANYWHERE in full path (parent-directory dots qualify). If extension does not begin dot, appends one dot, then appends extension including NUL, all without destination capacity/overlap checks. Empty extension therefore still produces final dot. Raw copy loop leaves EAX one byte BEFORE destination append point, not destination base or final string end; for empty copied prefix with dot-leading extension this can be destination-1. No validation of separators or multiple dots in requested extension.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Pickup static filename consumer5B7F80 requests literal .v3m. Helper57C440 removes last dot ANYWHERE (including directory dots), then appends requested suffix. Leading/trailing/inner ASCII whitespace are not trimmed; whitespace after a replaced suffix naturally disappears because suffix is discarded. Do not use host clean-basename extension logic before this native operation.
char *__cdecl rf_path_replace_last_dot_suffix_unbounded(char *a1, char *Str, const char *a3)
{
  char *result; // eax
  char *v5; // [esp+Ch] [ebp-20h]
  unsigned int v6; // [esp+10h] [ebp-1Ch]

  rf_path_copy_without_last_extension(a1, Str);
  if ( *a3 != 46 )
    *(_WORD *)&a1[strlen(a1)] = 46;
  v6 = strlen(a3) + 1;
  v5 = a1 - 1;
  do
    result = v5;
  while ( *++v5 );
  qmemcpy(v5, a3, v6);
  return result;
}

