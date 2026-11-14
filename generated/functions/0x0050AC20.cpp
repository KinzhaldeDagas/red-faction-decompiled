// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050AC20 sub_50AC20
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Secondary wrapper uses same full508990 grammar, including player_wep-conditional required Cycle/Pref/FineAim fields. It does not register/validate primary cycle/preference slots. Sets record+A8=1. Keep every row even duplicate/empty name or absent meshes.
void __cdecl sub_50AC20(_DWORD *a1)
{
  int i; // [esp+0h] [ebp-8h]
  char *v2; // [esp+4h] [ebp-4h]

  v2 = (char *)&rf_weapon_records + 1360 * dword_911C68;
  for ( i = 0; i < 10; ++i )
  {
    *(_DWORD *)&v2[4 * i + 456] = -1;
    *(_DWORD *)&v2[4 * i + 376] = -1;
    *(_DWORD *)&v2[4 * i + 416] = -1;
  }
  rf_weapon_definition_parse(a1, v2);
  *((_DWORD *)v2 + 42) = 1;
}

