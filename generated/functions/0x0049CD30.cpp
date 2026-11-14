// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049CD30 rf_multiplayer_hud_load_resources_and_register_cleanup
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet registry, field permutations, x87 transfers, face-list mutation and HUD native stores): Noarg
// caller-cleaned routine. In order loads hud_miniflag_red.tga->662920, hud_miniflag_blue.tga->662924, hud_miniflag_hilight.tga->662928, hud_flag_red.tga->66292C and
// hud_flag_blue.tga->662930; each bitmap loader receives(-1,1). Load rfpc-medium.vf spacing-1->662934; clear DWORD rendered notification row count77FE28; load bigfont.vf
// spacing-1->662940; register49CDF0 with atexit and return CRT registration result. Exact global addresses are from native store operands. No load failure checks, old handle release,
// notification-string clearing or duplicate-registration guard. Existing bitmap names distinguish their downstream roles but loader uses the literal filenames above.
int rf_multiplayer_hud_load_resources_and_register_cleanup()
{
  rf_compact_score_red_flag_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                       "hud_miniflag_red.tga",
                                       (void *)0xFFFFFFFF,
                                       1);
  rf_compact_score_blue_flag_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                        "hud_miniflag_blue.tga",
                                        (void *)0xFFFFFFFF,
                                        1);
  rf_compact_score_team_logo_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                        "hud_miniflag_hilight.tga",
                                        (void *)0xFFFFFFFF,
                                        1);
  rf_compact_score_red_microflag_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                            "hud_flag_red.tga",
                                            (void *)0xFFFFFFFF,
                                            1);
  rf_compact_score_blue_microflag_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                             "hud_flag_blue.tga",
                                             (void *)0xFFFFFFFF,
                                             1);
  dword_662934 = rf_font_load_with_spacing_override("rfpc-medium.vf", -1);
  rf_multiplayer_notification_rendered_row_count = 0;
  dword_662940 = rf_font_load_with_spacing_override("bigfont.vf", -1);
  return atexit(rf_multiplayer_hud_atexit_clear_notification_strings);
}

