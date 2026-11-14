// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC1A0 sub_4BC1A0
// UNREALRED VERIFIED [combat-native-pickups-20261111]: V3D Type maps exact case-insensitive RFString character->2, static->1, anim->3; every other spelling/empty returns0. No whitespace trim or generic static fallback.
int __cdecl sub_4BC1A0(int a1)
{
  if ( rf_string_equals_case_insensitive(a1, "character") )
    return 2;
  if ( rf_string_equals_case_insensitive(a1, "static") )
    return 1;
  if ( rf_string_equals_case_insensitive(a1, "anim") )
    return 3;
  return 0;
}

