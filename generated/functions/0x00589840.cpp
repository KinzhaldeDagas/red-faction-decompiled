// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589840 rf_character_find_primary_bone_substring
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Searches only primary bone-name records (base+76,stride76,count+72), calling rf_cstring_find_first_substring for each. Returns first matching bone index or-1. Does not search auxiliary/sphere/geometry names or validate pointers.
int __thiscall rf_character_find_primary_bone_substring(char *this, char *SubStr)
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < *((_DWORD *)this + 18); ++i )
  {
    if ( rf_cstring_find_first_substring(this + 76 * i + 76, SubStr) )
      return i;
  }
  return -1;
}

