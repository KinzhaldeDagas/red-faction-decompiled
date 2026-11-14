// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005087F0 rf_weapon_definition_register_player_order
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Primary wrapper uses full508990 result. Only player_wep flag0x80 rows require signed cycle/preference each0..31 and unique among primary player_wep rows. Nonplayer rows count too. Secondary50AC20 does NOT apply primary slot validation. Record+A8=0 for primary; source order is global ID.
_DWORD *__cdecl rf_weapon_definition_register_player_order(int a1)
{
  int i; // [esp+0h] [ebp-8h]
  _DWORD *v3; // [esp+4h] [ebp-4h]

  v3 = (_DWORD *)((char *)&rf_weapon_records + 1360 * dword_911C68);
  for ( i = 0; i < 10; ++i )
  {
    v3[i + 114] = -1;
    v3[i + 94] = -1;
    v3[i + 104] = -1;
  }
  rf_weapon_definition_parse(a1, (int)v3);
  if ( (v3[153] & 0x80) != 0 )
  {
    if ( v3[332] >= 0x20u )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\gamesrc\\weapon\\weapon.cpp",
        1660,
        "Invalid cycle position in weapons.tbl!");
    if ( rf_weapon_cycle_slots_weapon_index[4 * v3[332]] != -1 )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\gamesrc\\weapon\\weapon.cpp",
        1664,
        "Duplicate cycle positions in weapons.tbl!");
    rf_weapon_cycle_slots_weapon_index[4 * v3[332]] = dword_911C68;
    rf_weapon_cycle_slots_category[4 * v3[332]] = v3[328];
    if ( v3[333] >= 0x20u )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\gamesrc\\weapon\\weapon.cpp",
        1674,
        "Invalid pref position in weapons.tbl!");
    if ( rf_default_weapon_preference_order[v3[333]] != -1 )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\gamesrc\\weapon\\weapon.cpp",
        1678,
        "Duplicate pref positions in weapons.tbl!");
    rf_default_weapon_preference_order[v3[333]] = dword_911C68;
  }
  v3[42] = 0;
  return v3;
}

