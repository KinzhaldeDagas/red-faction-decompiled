// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00445C90 rf_game_constants_parse
// UNREALRED VERIFIED [respawn-surrounding]: Parses game.tbl Min/Max Fall Damage Height into globals 0x681E34/0x681E6C. This RF.exe has no runtime reader xrefs to either global; the active contact producer at 0x4D4BF0 uses its own speed formula.
void **rf_game_constants_parse()
{
  float v1; // [esp+8h] [ebp-128h]
  void *self[69]; // [esp+Ch] [ebp-124h] BYREF
  int v3; // [esp+12Ch] [ebp-4h]

  atexit(rf_clear_strings6F2C78_and87C65C);
  rf_memory_text_parser_construct_empty(self);
  v3 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "game.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\gamewide\\gameconstants.cpp",
      231,
      "Unable to open game.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Min Fall Damage Height:");
  unk_681E34 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Max Fall Damage Height:");
  unk_681E6C = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Max Entity Jump Height:");
  unk_681E28 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  v1 = rf_physics_gravity_acceleration * 2.0 * unk_681E28;
  unk_681E1C = rf_sqrt_float(v1);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Player Footstep Pan:");
  unk_6E671C = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Player Step Distance:");
  unk_6E6714 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Player Step Distance Climb:");
  unk_6E6718 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$First Level Filename:");
  rf_text_parser_read_delimited_rfstring(self, &unk_6FC308, 34, 34);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Lava Damage Per Second:");
  unk_681E2C = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Acid Damage Per Second:");
  unk_681E30 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Legs Pos Y:");
  unk_87FBD4 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Legs Pos Z:");
  unk_87FBD8 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Legs FOV:");
  unk_87FBF4 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Main Menu Music Filename:");
  rf_text_parser_read_delimited_rfstring(self, unk_6F2C78, 34, 34);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "$Intro Movie Filename:") )
    rf_text_parser_read_delimited_rfstring(self, dword_6FC464, 34, 34);
  else
    rf_string_assign_from_cstr(dword_6FC464, (char *)byte_63385E);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Default Player Weapon:");
  rf_text_parser_read_delimited_rfstring(self, unk_87C65C, 34, 34);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Multi Damage Modifier:");
  flt_662DC0 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Multi Player Acceleration:");
  unk_87BF44 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+No Geomod Limit") )
    unk_6FCCF9 = 1;
  rf_memory_text_parser_close_buffer(self);
  v3 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

