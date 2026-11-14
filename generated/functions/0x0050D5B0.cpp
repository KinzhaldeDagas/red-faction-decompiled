// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050D5B0 rf_weapon_table_initialize
// UNREALRED VERIFIED [combat-reaction-literal-names-20261111]: Registry order: require CURRENT #Primary Weapons, repeatedly parse5087F0/increment total until current #End; require CURRENT #Secondary Weapons, snapshot primaryCount911C7C=total, repeatedly50AC20/increment until #End, then finalize/close. All primary records contribute regardless player_wep flag. Trailing sections are not parsed. These loops show no count-capacity guard; the separate fixed64-record host boundary must be explicit, not described as a native rejection. Generic document section/name scans do not preserve this raw cursor admission.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Native registry cursor grammar: require CURRENT #Primary Weapons; until CURRENT #End parse full508990 via5087F0 and increment total. Require CURRENT #Secondary Weapons, capture primaryCount911C7C=total (ALL primary rows), parse via50AC20 until #End. No EOF/trailing-section validation. No name/visual filtering, no row deduplication, no table sorting. 5085B0 postprocess then parser close. Host publication must bind raw byte parse, ordered values and count to one source transaction; generic line-document name scan cannot establish native IDs.
void **rf_weapon_table_initialize()
{
  int i; // [esp+4h] [ebp-128h]
  void *self[69]; // [esp+8h] [ebp-124h] BYREF
  int v3; // [esp+128h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v3 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "weapons.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\weapon\\weapon.cpp",
      1711,
      "Unable to open weapons.tbl");
  for ( i = 0; i < 32; ++i )
  {
    rf_weapon_cycle_slots_runtime_icon[4 * i] = 0;
    rf_weapon_cycle_slots_weapon_index[4 * i] = -1;
    rf_weapon_cycle_slots_category[4 * i] = -1;
    rf_default_weapon_preference_order[i] = -1;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Primary Weapons");
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#End") )
  {
    rf_weapon_definition_register_player_order((int)self);
    ++dword_911C68;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Secondary Weapons");
  dword_911C7C = dword_911C68;
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#End") )
  {
    sub_50AC20(self);
    ++dword_911C68;
  }
  sub_5085B0();
  rf_memory_text_parser_close_buffer(self);
  v3 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

