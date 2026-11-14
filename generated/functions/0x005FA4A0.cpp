// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FA4A0 rf_bluebeard_sound_basename_compare
// UNREALRED VERIFIED [mission-mover-effects-20261013] Comparator strips text through last backslash from BOTH operands, then _stricmp. Thus a flat RFL/sounds.tbl name resolves a bluebeard.bty record stored with a data\audio\... path. The metadata file path itself is not the runtime audio filename.
int __cdecl rf_bluebeard_sound_basename_compare(char *a1, char *a2)
{
  char *String2; // [esp+4h] [ebp-14h]
  char *v4; // [esp+Ch] [ebp-Ch]
  char *last_char_wrapper; // [esp+10h] [ebp-8h]

  last_char_wrapper = rf_cstring_find_last_char_wrapper(a1, 92);
  v4 = rf_cstring_find_last_char_wrapper(a2, 92);
  if ( v4 )
    String2 = v4 + 1;
  else
    String2 = a2;
  if ( last_char_wrapper )
    return _stricmp(last_char_wrapper + 1, String2);
  else
    return _stricmp(a1, String2);
}

