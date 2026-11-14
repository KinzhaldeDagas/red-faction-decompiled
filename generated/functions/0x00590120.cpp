// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590120 rf_sound_name_hash_rotate6_case_sensitive
// UNREALRED VERIFIED [dsound-creation-20261028]: Null name returns-1; otherwise accumulator0,for each char rotate-left6 XOR sign-extended char,return accumulator. No lowercase normalization or absolute value. Empty string0. Name finder also uses case-insensitive comparison but hash itself remains case-sensitive.
int __cdecl rf_sound_name_hash_rotate6_case_sensitive(_BYTE *a1)
{
  int v2; // [esp+0h] [ebp-8h]
  _BYTE *i; // [esp+4h] [ebp-4h]

  if ( !a1 )
    return -1;
  v2 = 0;
  for ( i = a1; *i; ++i )
    v2 = __ROL4__(v2, 6) ^ (char)*i;
  return v2;
}

