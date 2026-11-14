// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592510 rf_vfile_get_backslash_basename_pointer
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This vfile object. Searches NUL path beginning object+5 for LAST backslash via strrchr;returns borrowed pointer after it,or object+5 if none. Does not recognize slash separators,copy,allocate,check NULL this or validate termination. Trailing backslash returns pointer to empty suffix. Used by mesh/scene binary readers to record source basename.
char *__thiscall rf_vfile_get_backslash_basename_pointer(char *this)
{
  char *last_char_wrapper; // [esp+4h] [ebp-4h]

  last_char_wrapper = rf_cstring_find_last_char_wrapper(this + 5, 92);
  if ( last_char_wrapper )
    return last_char_wrapper + 1;
  else
    return this + 5;
}

