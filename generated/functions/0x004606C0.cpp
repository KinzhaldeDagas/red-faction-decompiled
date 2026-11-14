// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004606C0 rf_multiplayer_profile_build_and_load
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. If buildBYTE6F4AD4 zero,construct player_config_panel.tga at6F4ADC,name edit6F4B08 with group callback4605D0,character group callback4605E0,left/right
// arrows460640/460680,portrait click460680,localized labels/indicators. Populate inline5 focus-list6F5028 and inline25 draw-list6F4FC0 plus meta child links;append results unchecked.
// Copy FIRST DWORD of every character-table entry(stride320) to bitmap cache6F4A58[i],using runtime characterCount without local cache bound. Portrait rectangle
// logical(134,93,273,239). Set build latch AFTER construction. EVERY invocation:unguarded localPlayer+8 RFString ->strncpy63 into local68-byte buffer,force index63NUL,load edit
// control4706C0;clear dirtyBYTE6F4AD6;read localPlayerDWORD3932 into current index6F4AD8 with no validation. No explicit edit-latch/focus reset,bitmap load,name commit or network
// send. Return current character index residue.
int rf_multiplayer_profile_build_and_load()
{
  const char *v0; // eax
  int result; // eax
  int i; // [esp+8h] [ebp-4Ch]
  char Destination[68]; // [esp+Ch] [ebp-48h] BYREF

  if ( !unk_6F4AD4 )
  {
    rf_ui_panel_initialize_bitmap(dword_6F4ADC, "player_config_panel.tga", 0, rf_main_menu_title_y);
    unk_6F4C8C = dword_6F4ADC;
    unk_6F4CA8 = rf_multiplayer_profile_latch_name_edit;
    rf_inline_dword_array5_append(dword_6F5028, (int)&unk_6F4C88);
    rf_ui_edit_initialize((int)byte_6F4B08, (int)dword_6F4ADC, 136, 23, (char *)&unk_636798, unk_6F29AC, 136);
    rf_inline_dword_array25_append(dword_6F4FC0, (int)byte_6F4B08);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F4C88, byte_6F4B08);
    rf_ui_image_button_initialize(
      &dword_6F4B70,
      (char *)&unk_63679A,
      "indicator_selected.tga",
      110,
      17,
      -1,
      (char *)&byte_636799,
      0);
    unk_6F4B74 = dword_6F4ADC;
    rf_inline_dword_array25_append(dword_6F4FC0, (int)&dword_6F4B70);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F4C88, &dword_6F4B70);
    rf_ui_label_initialize_measured_text(dword_6F4D38, (int)dword_6F4ADC, 285, unk_6F4B18, unk_88E144, unk_6F29AC);
    rf_inline_dword_array25_append(dword_6F4FC0, (int)dword_6F4D38);
    unk_6F4EEC = dword_6F4ADC;
    unk_6F4F08 = rf_multiplayer_profile_character_press_dispatch;
    rf_inline_dword_array5_append(dword_6F5028, (int)&unk_6F4EE8);
    for ( i = 0; i < rf_multiplayer_character_count; ++i )
      unk_6F4A58[i] = rf_multiplayer_character_table[80 * i];
    rf_ui_image_button_initialize(
      &dword_6F5040,
      "cyclebutton_l.tga",
      (char *)&unk_6367B3,
      132,
      68,
      -1,
      (char *)&byte_63679B,
      0);
    unk_6F5044 = dword_6F4ADC;
    unk_6F5060 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_profile_previous_character;
    rf_inline_dword_array25_append(dword_6F4FC0, (int)&dword_6F5040);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F4EE8, &dword_6F5040);
    rf_ui_image_button_initialize(
      &dword_6F4BB8,
      "cyclebutton_r.tga",
      (char *)&unk_6367D3,
      390,
      68,
      -1,
      (char *)&byte_6367D2,
      0);
    unk_6F4BBC = dword_6F4ADC;
    unk_6F4BD8 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_profile_next_character;
    rf_inline_dword_array25_append(dword_6F4FC0, (int)&dword_6F4BB8);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F4EE8, &dword_6F4BB8);
    rf_ui_image_button_initialize(
      &dword_6F4C40,
      (char *)&unk_6367E7,
      "indicator_selected.tga",
      110,
      68,
      -1,
      (char *)&byte_6367E6,
      0);
    unk_6F4C44 = dword_6F4ADC;
    rf_inline_dword_array25_append(dword_6F4FC0, (int)&dword_6F4C40);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F4EE8, &dword_6F4C40);
    rf_ui_label_initialize_measured_text(dword_6F4C00, (int)dword_6F4ADC, 200, 72, unk_88E148, unk_6F29AC);
    rf_inline_dword_array25_append(dword_6F4FC0, (int)dword_6F4C00);
    unk_6F4FA0 = 134;
    unk_6F4FA4 = 93;
    unk_6F4FA8 = 273;
    unk_6F4FAC = 239;
    unk_6F4F98 = dword_6F4ADC;
    unk_6F4FB4 = rf_multiplayer_profile_next_character;
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F4EE8, &unk_6F4F94);
    unk_6F4AD4 = 1;
  }
  v0 = rf_string_object_c_str_or_empty((const void *)(rf_local_fpgun_player + 8));
  strncpy(Destination, v0, 0x3Fu);
  Destination[63] = 0;
  rf_ui_edit_set_text_bounded(byte_6F4B08, Destination, unk_6F29AC);
  unk_6F4AD6 = 0;
  result = *(_DWORD *)(rf_local_fpgun_player + 3932);
  dword_6F4AD8 = result;
  return result;
}

