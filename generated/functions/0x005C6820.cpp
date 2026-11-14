// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6820 rf_path_basename_backslash
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Returns the byte after the final backslash in a mutable string, or the original pointer if none. A trailing backslash therefore returns the terminating NUL. Does not recognize forward slash or allocate/copy; used by exception reporting.
char *__cdecl rf_path_basename_backslash(char *Str)
{
  char *last_char_wrapper; // [esp+0h] [ebp-4h]

  last_char_wrapper = rf_cstring_find_last_char_wrapper(Str, 92);
  if ( last_char_wrapper )
    return last_char_wrapper + 1;
  else
    return Str;
}

