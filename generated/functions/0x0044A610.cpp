// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A610 rf_hud_table_load_and_select_profile
// UNREALRED VERIFIED [hud-layout-profile] Loads hud.tbl colors and the #640x480, #800x600, #1024x768, and #1280x1024 coordinate sections, closes parsing, then selects a profile using its integer argument.
void **__cdecl rf_hud_table_load_and_select_profile(int a1)
{
  void *self[69]; // [esp+4h] [ebp-124h] BYREF
  int v3; // [esp+124h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v3 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "hud.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\gamesrc\\hud\\hud.cpp", 544, "Unable to open hud.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$HUD default color:");
  rf_text_parser_read_braced_rgba_bytes((int)self, byte_6EE6A8);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$HUD msg color:");
  rf_text_parser_read_braced_rgba_bytes((int)self, byte_6EE6A4);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$HUD msg bg color:");
  rf_text_parser_read_braced_rgba_bytes((int)self, byte_6EE6BC);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$HUD full color:");
  rf_text_parser_read_braced_rgba_bytes((int)self, &rf_hud_color_full_rgba);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$HUD mid color:");
  rf_text_parser_read_braced_rgba_bytes((int)self, &rf_hud_color_mid_rgba);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$HUD low color:");
  rf_text_parser_read_braced_rgba_bytes((int)self, &unk_6EE69C);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$HUD countdown color:");
  rf_text_parser_read_braced_rgba_bytes((int)self, rf_hud_countdown_color);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$HUD body msg color:");
  rf_text_parser_read_braced_rgba_bytes((int)self, byte_6EE6B8);
  rf_text_parser_find_before_stop_and_consume_required((char **)self, "#640x480", nullptr);
  rf_hud_layout_profile_parse_coordinates((const char **)self, (int)&rf_hud_layout_coordinates_640x480);
  rf_text_parser_find_before_stop_and_consume_required((char **)self, "#800x600", nullptr);
  rf_hud_layout_profile_parse_coordinates((const char **)self, (int)&rf_hud_layout_coordinates_800x600);
  rf_text_parser_find_before_stop_and_consume_required((char **)self, "#1024x768", nullptr);
  rf_hud_layout_profile_parse_coordinates((const char **)self, (int)&rf_hud_layout_coordinates_1024x768);
  rf_text_parser_find_before_stop_and_consume_required((char **)self, "#1280x1024", nullptr);
  rf_hud_layout_profile_parse_coordinates((const char **)self, (int)&rf_hud_layout_coordinates_1280x1024);
  rf_memory_text_parser_close_buffer(self);
  rf_hud_layout_profile_select_width(a1);
  v3 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

