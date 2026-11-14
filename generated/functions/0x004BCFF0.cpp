// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BCFF0 sub_4BCFF0
// UNREALRED VERIFIED [combat-native-weapon-layout-20261111]: Native damage lookup loops11 table slots662D94. Original PE data verified: slots0..8 = bash,bullet,armor piercing bullet,explosive,fire,energy,electrical,acid,scalding; slots9/10 NULL. Unknown/padded name reachesCRT_stricmp(String1,NULL), which invokes invalid-parameter handling before returningINT_MAX if handler returns. Thus decompiled final-1 is NOT proof of clean unknown-name failure in default runtime; host must distinguish this abnormal/unsupported dependency, never normalize whitespace into a known type or fabricate valid damage. Table receipt combat_weapon_registry_20261111/native_damage_names.json.
int __cdecl sub_4BCFF0(char *String1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 11; ++i )
  {
    if ( !_stricmp(String1, (&off_662D94)[i]) )
      return i;
  }
  return -1;
}

