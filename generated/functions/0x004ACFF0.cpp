// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ACFF0 sub_4ACFF0
// UNREALRED VERIFIED [combat-native-pickup-runtime-20261111]: Scans5 exact CI RFString names662C4C in order: Multi Invulnerability0, Multi Damage Amplifier1, Multi Super Armor2, Multi Super Health3, Multi Nanoshield4. Unknown=-1.473940 passes INSTANCE+29C RFString (script/name supplied to473280), not definition class/handler. Its200 armor/life caps apply only instance-name kinds2/3.
int __cdecl sub_4ACFF0(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 5; ++i )
  {
    if ( rf_string_equals_case_insensitive(a1, (&off_662C4C)[i]) )
      return i;
  }
  return -1;
}

