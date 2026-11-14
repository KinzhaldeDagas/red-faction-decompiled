// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057C610 rf_path_mkdir_backslash_chain_ignoring_errors
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl path. Unbounded-copies path into260-byte local, finds final BACKSLASH, terminates temporary there and recursively processes prefix. Nonzero recursive return propagates, but each level ignores _mkdir(originalPath) result and returns0; under ordinary recursion this cannot report mkdir failure. No existence/type check, slash normalization or drive-root special case. Forward slashes do not split recursion. Empty, leading or repeated backslashes can result in mkdir of empty/drive-prefix paths; original source path is not modified.
int __cdecl rf_path_mkdir_backslash_chain_ignoring_errors(char *Path)
{
  char v1; // al
  char *v3; // [esp+8h] [ebp-118h]
  char *v4; // [esp+Ch] [ebp-114h]
  char *last_char_wrapper; // [esp+10h] [ebp-110h]
  int v6; // [esp+14h] [ebp-10Ch]
  char Str[260]; // [esp+18h] [ebp-108h] BYREF

  v4 = Path;
  v3 = Str;
  do
  {
    v1 = *v4;
    *v3++ = *v4++;
  }
  while ( v1 );
  last_char_wrapper = rf_cstring_find_last_char_wrapper(Str, 92);
  if ( last_char_wrapper )
  {
    *last_char_wrapper = 0;
    v6 = rf_path_mkdir_backslash_chain_ignoring_errors(Str);
    if ( v6 )
      return v6;
  }
  _mkdir(Path);
  return 0;
}

