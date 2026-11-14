// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045BCD0 rf_multiplayer_setup_build_level_catalog_and_controls
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg,existing SEH/chunks retained. EVERY invocation clears master pair-array6F2E14;reads registry ListLAN default0
// and normalizes toLANBYTE6F5E51;constructs ONE reusable two-RFString record;enumerates vpack member names by extension "rfl" into packed NUL list. Candidate if case-insensitive
// SUBSTRING "m_","dm" or "ctf" occurs ANYWHERE,not strict prefix. Strip last extension into local128-byte Source (no capacity supplied here),assign record+8;construct owned8-byte
// filename argument and call45C9A0(record+0 output). IGNORE returnAL and append copied16-byte record regardless;failed title lookup leaves prior title in reused record,so candidate
// can inherit preceding title. Advance original packed list by strlen+1,free Block. Only if initBYTE6F2D00 zero:set1 BEFORE construction;build server_options_panel.tga parent6F2D0C
// and native child/draw/focus arrays;load ServerName/default localized88E140,LAN checkbox,3-choice game mode,10-choice max players(default
// INDEX4),ServerPasswordChecked(default0),ServerPassword(default empty),level-list,slider0..1,up/down,add/remove-all controls. Bind native callbacks in function comments of
// corresponding routines;password enabled byte mirrors checked state. visibleRows=trunc(120*scaleY/rowHeight);rebuild filtered list45CD00 and atexit45D130 ONLY inside one-time
// branch. Every exit resets focused control6F2CF4=0,704EFC=-1,editLatch6F2D01=0;apply mode-control flags45F7F0(currentMode),destroy temporary pair. Subsequent calls rescan master but
// do not explicitly rebuild filtered list here;45F7F0 changes state9 only. No server start,credential validation or network send.
void rf_multiplayer_setup_build_level_catalog_and_controls()
{
  int v0; // edx
  char v1; // [esp-8h] [ebp-918h] BYREF
  unsigned int v2; // [esp-4h] [ebp-914h] BYREF
  char *v3; // [esp+0h] [ebp-910h]
  char **v4; // [esp+4h] [ebp-90Ch]
  char *v5; // [esp+Ch] [ebp-904h]
  char *v6; // [esp+10h] [ebp-900h]
  const char *v7; // [esp+14h] [ebp-8FCh]
  int v8; // [esp+18h] [ebp-8F8h]
  const char *v9; // [esp+1Ch] [ebp-8F4h]
  const char *v10; // [esp+20h] [ebp-8F0h]
  const char *v11; // [esp+24h] [ebp-8ECh]
  const char *v12; // [esp+28h] [ebp-8E8h]
  int v13; // [esp+2Ch] [ebp-8E4h]
  int v14; // [esp+30h] [ebp-8E0h]
  char *v15; // [esp+38h] [ebp-8D8h]
  char *v16; // [esp+3Ch] [ebp-8D4h]
  _lambda_8b695f9820225e821433c25f6ed27cb8_ *v17; // [esp+40h] [ebp-8D0h]
  _DWORD *v18; // [esp+44h] [ebp-8CCh]
  char *v19; // [esp+48h] [ebp-8C8h]
  unsigned int *v20; // [esp+4Ch] [ebp-8C4h]
  char v21[4]; // [esp+50h] [ebp-8C0h] BYREF
  char v22[1028]; // [esp+54h] [ebp-8BCh] BYREF
  BYTE v23[4]; // [esp+458h] [ebp-4B8h] BYREF
  char v24[1024]; // [esp+45Ch] [ebp-4B4h] BYREF
  char Source[128]; // [esp+85Ch] [ebp-B4h] BYREF
  int v26; // [esp+8E0h] [ebp-30h] BYREF
  char *Str; // [esp+8E4h] [ebp-2Ch]
  void *Block; // [esp+8E8h] [ebp-28h] BYREF
  char *self[2]; // [esp+8ECh] [ebp-24h] BYREF
  int v30; // [esp+8F4h] [ebp-1Ch] BYREF
  BYTE Data[4]; // [esp+8FCh] [ebp-14h] BYREF
  int i; // [esp+900h] [ebp-10h]
  int v33; // [esp+90Ch] [ebp-4h]

  rf_two_rfstring_array16_clear_and_release(dword_6F2E14);
  rf_registry_read_dword_or_default(nullptr, "ListLAN", Data, 0);
  byte_6F5E51[0] = *(_DWORD *)Data != 0;
  rf_two_rfstring_prefix_construct(self);
  v33 = 0;
  rf_vpackfile_enumerate_member_names_by_extensions((char *)&off_6361F0, &Block, &v26, nullptr);
  for ( Str = (char *)Block; *Str; Str = v16 )
  {
    if ( rf_cstring_find_first_substring_case_insensitive(Str, "m_")
      || rf_cstring_find_first_substring_case_insensitive(Str, "dm")
      || rf_cstring_find_first_substring_case_insensitive(Str, (const char *)&off_6361FC) )
    {
      rf_path_copy_without_last_extension(Source, Str);
      rf_string_assign_from_cstr(&v30, Source);
      v4 = self;
      v20 = &v2;
      v18 = rf_string_construct_from_cstr(&v2, Str);
      rf_multiplayer_level_header_read_display_name(v2, v3, v4);
      v19 = &v1;
      v17 = rf_two_rfstring_copy_construct((_lambda_8b695f9820225e821433c25f6ed27cb8_ *)&v1, self);
      rf_two_rfstring_array16_append_owned(dword_6F2E14, v1, v2, (int)v3, (int)v4);
    }
    v16 = Str;
    v15 = Str + 1;
    v16 += strlen(v16);
    v14 = ++v16 - (Str + 1);
  }
  free(Block);
  if ( !unk_6F2D00 )
  {
    unk_6F2D00 = 1;
    rf_ui_panel_initialize_bitmap(dword_6F2D0C, "server_options_panel.tga", 0, rf_main_menu_title_y);
    unk_6F328C = dword_6F2D0C;
    unk_6F32A8 = rf_multiplayer_setup_server_name_press_dispatch;
    rf_inline_dword8_append_unless_exact_full(dword_6F2EBC, (int)&unk_6F3288);
    v13 = (int)dword_88E140;
    rf_registry_read_cstring_or_default(nullptr, lpValueName, v24, dword_88E140);
    rf_ui_edit_initialize((int)&unk_6F3110, (int)dword_6F2D0C, 136, 23, v24, unk_6F29AC, 181);
    unk_6F3130 = rf_multiplayer_setup_latch_server_name_edit;
    rf_inline_dword_array25_append(dword_6F3788, (int)&unk_6F3110);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3288, &unk_6F3110);
    rf_ui_image_button_initialize(
      &dword_6F3200,
      (char *)&off_63614B,
      "indicator_selected.tga",
      110,
      17,
      -1,
      (char *)&byte_636143,
      0);
    unk_6F3204 = dword_6F2D0C;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F3200);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3288, &dword_6F3200);
    v12 = dword_88DF1C;
    rf_ui_label_initialize_measured_text(dword_6F3248, (int)dword_6F2D0C, 330, unk_6F3120, dword_88DF1C, unk_6F29AC);
    rf_inline_dword_array25_append(dword_6F3788, (int)dword_6F3248);
    rf_ui_checkbox_initialize_471300(
      &dword_6F2D78,
      (int)&off_63615B,
      (int)"checkbox_selected.tga",
      "checkbox_checked.tga",
      113,
      46,
      -1,
      (char *)&byte_63614F,
      0);
    unk_6F2D7C = dword_6F2D0C;
    unk_6F2D98 = rf_multiplayer_setup_toggle_lan_only;
    unk_6F2DC0 = byte_6F5E51[0] != 0;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F2D78);
    rf_inline_dword8_append_unless_exact_full(dword_6F2EBC, (int)&dword_6F2D78);
    v11 = dword_88E3B8;
    rf_ui_label_initialize_measured_text(dword_6F3610, (int)&dword_6F2D78, 100, 7, dword_88E3B8, unk_6F29AC);
    rf_inline_dword_array25_append(dword_6F3788, (int)dword_6F3610);
    unk_6F3064 = dword_6F2D0C;
    unk_6F3080 = rf_multiplayer_setup_game_mode_press_dispatch;
    rf_inline_dword8_append_unless_exact_full(dword_6F2EBC, (int)&unk_6F3060);
    rf_ui_cycle_list_set_geometry(dword_6F3458, (int)dword_6F2D0C, 150, 82, 107, 12);
    for ( i = 0; i < 3; ++i )
      rf_ui_cycle_list_append_text(dword_6F3458, i, *(const char **)dword_6F3AE4[i], unk_6F29AC);
    rf_inline_dword_array25_append(dword_6F3788, (int)dword_6F3458);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3060, dword_6F3458);
    rf_ui_image_button_initialize(
      &dword_6F2DD0,
      "cyclebutton_l.tga",
      (char *)&unk_636167,
      -18,
      -6,
      -1,
      (char *)&byte_63615F,
      0);
    unk_6F2DD4 = dword_6F3458;
    unk_6F2DF0 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_setup_previous_game_mode;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F2DD0);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3060, &dword_6F2DD0);
    rf_ui_image_button_initialize(
      &dword_6F3410,
      "cyclebutton_r.tga",
      (char *)&unk_636183,
      unk_6F346C,
      -6,
      -1,
      (char *)&byte_636173,
      0);
    unk_6F3414 = dword_6F3458;
    unk_6F3430 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_setup_next_game_mode;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F3410);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3060, &dword_6F3410);
    rf_ui_image_button_initialize(
      &dword_6F3018,
      (char *)&unk_63619B,
      "indicator_selected.tga",
      -23,
      0,
      -1,
      (char *)&byte_63619A,
      0);
    unk_6F301C = &dword_6F2DD0;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F3018);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3060, &dword_6F3018);
    v10 = dword_88DF20;
    rf_ui_label_initialize_measured_text(dword_6F3698, (int)dword_6F2D0C, 285, unk_6F3468, dword_88DF20, unk_6F29AC);
    rf_inline_dword_array25_append(dword_6F3788, (int)dword_6F3698);
    unk_6F3364 = dword_6F2D0C;
    unk_6F3380 = rf_multiplayer_setup_player_count_press_dispatch;
    rf_inline_dword8_append_unless_exact_full(dword_6F2EBC, (int)&unk_6F3360);
    rf_ui_cycle_list_set_geometry(dword_6F37F0, (int)dword_6F2D0C, 150, 115, 107, 12);
    for ( i = 0; i < 10; ++i )
    {
      rf_format_signed_decimal_cstring(v21, 4, rf_multiplayer_host_player_count_choices[i]);
      rf_ui_cycle_list_append_text(dword_6F37F0, v0, v21, unk_6F29AC);
    }
    unk_6F395C = 4;
    rf_inline_dword_array25_append(dword_6F3788, (int)dword_6F37F0);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3360, dword_6F37F0);
    rf_ui_image_button_initialize(
      &dword_6F39F0,
      "cyclebutton_l.tga",
      (char *)&unk_6361AE,
      -18,
      -6,
      -1,
      (char *)&byte_6361A7,
      0);
    unk_6F39F4 = dword_6F37F0;
    unk_6F3A10 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_setup_previous_player_count_choice;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F39F0);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3360, &dword_6F39F0);
    rf_ui_image_button_initialize(
      &dword_6F39A8,
      "cyclebutton_r.tga",
      (char *)&unk_6361B2,
      unk_6F3804,
      -6,
      -1,
      (char *)&byte_6361AF,
      0);
    unk_6F39AC = dword_6F37F0;
    unk_6F39C8 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_setup_next_player_count_choice;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F39A8);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3360, &dword_6F39A8);
    rf_ui_image_button_initialize(
      &dword_6F3650,
      (char *)&unk_6361C3,
      "indicator_selected.tga",
      -23,
      0,
      -1,
      (char *)&byte_6361B3,
      0);
    unk_6F3654 = &dword_6F39F0;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F3650);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3360, &dword_6F3650);
    v9 = dword_88DF24;
    rf_ui_label_initialize_measured_text(dword_6F31C0, (int)dword_6F2D0C, 285, unk_6F3800, dword_88DF24, unk_6F29AC);
    rf_inline_dword_array25_append(dword_6F3788, (int)dword_6F31C0);
    unk_6F2F6C = dword_6F2D0C;
    unk_6F2F88 = rf_multiplayer_setup_password_press_dispatch;
    rf_inline_dword8_append_unless_exact_full(dword_6F2EBC, (int)&unk_6F2F68);
    rf_registry_read_dword_or_default(nullptr, off_661EBC, v23, 0);
    rf_ui_checkbox_initialize_471300(
      &dword_6F2E70,
      (int)&unk_6361E3,
      (int)"checkbox_selected.tga",
      "checkbox_checked.tga",
      113,
      138,
      25,
      (char *)&byte_6361D3,
      0);
    unk_6F2E74 = dword_6F2D0C;
    unk_6F2E90 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_setup_toggle_password_enabled;
    unk_6F2EB8 = *(_DWORD *)v23 != 0;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F2E70);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F2F68, &dword_6F2E70);
    rf_registry_read_cstring_or_default(nullptr, off_661EB8, v22, (BYTE *)&unk_6361E7);
    rf_ui_edit_initialize((int)&unk_6F36D8, (int)dword_6F2D0C, 215, 146, v22, unk_6F29AC, 132);
    unk_6F36E1 = unk_6F2EB8;
    unk_6F36F8 = rf_multiplayer_setup_latch_password_edit;
    rf_inline_dword_array25_append(dword_6F3788, (int)&unk_6F36D8);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F2F68, &unk_6F36D8);
    v8 = unk_88DB3C;
    rf_ui_label_initialize_measured_text(dword_6F2EE0, (int)dword_6F2D0C, 360, 146, unk_88DB3C, unk_6F29AC);
    rf_inline_dword_array25_append(dword_6F3788, (int)dword_6F2EE0);
    unk_6F3A3C = dword_6F2D0C;
    unk_6F3A58 = rf_multiplayer_setup_level_list_press_dispatch;
    unk_6F3A5C = rf_ui_dispatch_button_hit_6F3A60;
    rf_inline_dword8_append_unless_exact_full(dword_6F2EBC, (int)&unk_6F3A38);
    unk_6F3340 = dword_661EE8;
    unk_6F3344 = dword_661EEC;
    unk_6F3348 = dword_661EF0;
    unk_6F334C = dword_661EF4;
    unk_6F3338 = dword_6F2D0C;
    unk_6F3354 = rf_multiplayer_level_list_toggle_row;
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3A38, &dword_6F3334);
    rf_ui_image_button_initialize(
      &dword_6F3960,
      (char *)&unk_6361FB,
      "indicator_selected.tga",
      110,
      166,
      -1,
      (char *)&byte_6361F7,
      0);
    unk_6F3964 = dword_6F2D0C;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F3960);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3A38, &dword_6F3960);
    rf_ui_slider_initialize_471620(
      (int)flt_6F3740,
      (int)dword_6F2D0C,
      "slider_bar_vert.tga",
      "slider_bar_vert_on.tga",
      425,
      218,
      16,
      86,
      0.0,
      1.0);
    unk_6F3760 = rf_multiplayer_level_scroll_from_slider;
    unk_6F3764 = rf_multiplayer_level_scroll_from_slider;
    rf_inline_dword_array25_append(dword_6F3788, (int)flt_6F3740);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3A38, flt_6F3740);
    rf_ui_image_button_initialize(
      &dword_6F2F20,
      "cyclebutton_u.tga",
      "cyclebutton_u_on.tga",
      424,
      199,
      -1,
      (char *)&byte_636219,
      unk_6F29AC);
    unk_6F2F24 = dword_6F2D0C;
    unk_6F2F40 = rf_multiplayer_level_scroll_up;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F2F20);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3A38, &dword_6F2F20);
    rf_ui_image_button_initialize(
      &dword_6F3178,
      "cyclebutton_d.tga",
      "cyclebutton_d_on.tga",
      424,
      304,
      -1,
      (char *)&byte_63621A,
      unk_6F29AC);
    unk_6F317C = dword_6F2D0C;
    unk_6F3198 = rf_multiplayer_level_scroll_down;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F3178);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3A38, &dword_6F3178);
    v7 = dword_88DF28;
    rf_ui_label_initialize_measured_text(dword_6F2D38, (int)dword_6F2D0C, 132, 172, dword_88DF28, unk_6F29AC);
    rf_inline_dword_array25_append(dword_6F3788, (int)dword_6F2D38);
    v6 = dword_88E234;
    rf_ui_image_button_initialize(
      &dword_6F35C8,
      (char *)&unk_63621B,
      "lit_button_selected.tga",
      132,
      328,
      30,
      dword_88E234,
      unk_6F29AC);
    unk_6F35CC = dword_6F2D0C;
    unk_6F35E8 = rf_multiplayer_level_rotation_add_all_missing_rows;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F35C8);
    rf_inline_dword8_append_unless_exact_full(dword_6F2EBC, (int)&dword_6F35C8);
    v5 = dword_88E238;
    rf_ui_image_button_initialize(
      &dword_6F2E20,
      (char *)&unk_63622B,
      "lit_button_selected.tga",
      298,
      328,
      19,
      dword_88E238,
      unk_6F29AC);
    unk_6F2E24 = dword_6F2D0C;
    unk_6F2E40 = rf_multiplayer_level_rotation_remove_all;
    rf_inline_dword_array25_append(dword_6F3788, (int)&dword_6F2E20);
    rf_inline_dword8_append_unless_exact_full(dword_6F2EBC, (int)&dword_6F2E20);
    unk_6F2CF0 = (int)((double)dword_661EF4 * rf_ui_scale_y / (double)dword_6F299C);
    rf_multiplayer_setup_rebuild_filtered_level_list();
    atexit(rf_multiplayer_setup_destroy_level_catalogs);
  }
  unk_6F2CF4 = 0;
  dword_704EFC = -1;
  unk_6F2D01 = 0;
  rf_multiplayer_setup_apply_mode_control_flags(unk_6F35C4);
  v33 = -1;
  rf_two_rfstring_prefix_destroy((char *)self);
}

