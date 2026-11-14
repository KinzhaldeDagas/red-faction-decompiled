// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507CE0 sub_507CE0
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: First registered wholeCI name wins in911488 stride20 count911480 via5609B0/CRTdefaultASCII; no trim, hyphen/space/underscore alias normalization, or none/empty special spelling. Unknown=>-1; a registered empty name is an ordinary valid ordinal. Weapon parser binds this exact signed ID at+24.
int __cdecl sub_507CE0(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < unk_911480; ++i )
  {
    if ( rf_string_equals_case_insensitive((int)&unk_911488 + 20 * i, String2) )
      return i;
  }
  return -1;
}

