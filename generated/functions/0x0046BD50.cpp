// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046BD50 rf_gameplay_settings_menu_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Full native builder:visibleRows6F7B68=floor(binary32(authored height662434*scaleY/pixelRowHeight));NO own build latch/list reset. Refresh localized
// easy/medium/hard/insane labels;build gamesettings_panel.tga/root6F7BDC. Difficulty group7FA0->46B5C0,chooser7DE8 raw configured6612A8,left46B650/right46B680;Show1stPersonWeapon
// checkbox7CC0 loads raw player3894->46B6B0;AutoswitchWeapons8050 raw player3904->46B720;Explosives7B90 loads logical-not player3905->46B790. Priority group81E0
// press46B800/drag46B860,list7C94 geometry662428..34/press46B8C0,slider7D58 press+drag46B910,up/down46B9A0/9F0,MoveUp7C08->46BA70/MoveDown7D10->46BB70. Append to inline28
// draw6F8320/focus6F8398/meta children,ignore failures. Recompute count6F7B7C by scanning EXACT32 raw playerDWORD4436+4*i slots:only signedID>-1,first RFString
// atweapon_records+1360*ID compares nonempty via stricmp(empty literal637A5E),and flagsDWORD at912264+1360*ID has80 ->increment. NO ID<64/playerNULL guard BEFORE weapon-table
// dereferences,unlike rowdraw. Does NOT pack/filter/reorder priority array or build an index map;draw/move address first count raw slots directly,so count is eligibility tally only.
// Does not reset focus6F7B80/scroll6F7B84/selected6F7B88,ensure-visible,sync initial slider to stale scroll or save. Parent options build latch is normal one-time admission. Original
// geometry/empty string/native callbacks verified;previous autoswitch note preserved.
int rf_gameplay_settings_menu_initialize()
{
  const char *v0; // eax
  float value; // [esp+34h] [ebp-Ch]
  int v3; // [esp+38h] [ebp-8h]
  int i; // [esp+3Ch] [ebp-4h]
  int j; // [esp+3Ch] [ebp-4h]

  value = (double)dword_662434 * rf_ui_scale_y / (double)dword_6F299C;
  unk_6F7B68 = (int)rf_floor_float(value);
  rf_ui_panel_initialize_bitmap(dword_6F7BDC, "gamesettings_panel.tga", dword_6F29C8, rf_main_menu_title_y);
  dword_6F7B6C[0] = unk_88D58C;
  unk_6F7B70 = unk_88D590;
  unk_6F7B74 = unk_88D594;
  unk_6F7B78 = unk_88D598;
  rf_ui_label_initialize_measured_text(dword_6F80A0, (int)dword_6F7BDC, 285, 25, unk_88DE58, unk_6F29AC);
  rf_inline_dword_array28_append(dword_6F8320, (int)dword_6F80A0);
  rf_ui_label_initialize_measured_text(dword_6F80E0, (int)dword_6F7BDC, 215, 72, unk_88E168, unk_6F29AC);
  rf_inline_dword_array28_append(dword_6F8320, (int)dword_6F80E0);
  rf_ui_label_initialize_measured_text(dword_6F8120, (int)dword_6F7BDC, 215, 99, unk_88DE60, unk_6F29AC);
  rf_inline_dword_array28_append(dword_6F8320, (int)dword_6F8120);
  rf_ui_label_initialize_measured_text(dword_6F8160, (int)dword_6F7BDC, 215, 126, unk_88DE64, unk_6F29AC);
  rf_inline_dword_array28_append(dword_6F8320, (int)dword_6F8160);
  rf_ui_label_initialize_measured_text(dword_6F81A0, (int)dword_6F7BDC, 130, 170, unk_88DE68, unk_6F29AC);
  rf_inline_dword_array28_append(dword_6F8320, (int)dword_6F81A0);
  unk_6F7FA4 = dword_6F7BDC;
  unk_6F7FC0 = rf_gameplay_difficulty_group_press_apply;
  rf_inline_dword_array28_append(dword_6F8398, (int)&unk_6F7FA0);
  rf_ui_cycle_list_set_geometry(dword_6F7DE8, (int)dword_6F7BDC, 150, 18, 108, 26);
  for ( i = 0; i < 4; ++i )
    rf_ui_cycle_list_append_text(dword_6F7DE8, unk_6F29AC, (const char *)dword_6F7B6C[i], unk_6F29AC);
  unk_6F7F54 = dword_6612A8;
  rf_inline_dword_array28_append(dword_6F8320, (int)dword_6F7DE8);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F7FA0, dword_6F7DE8);
  rf_ui_image_button_initialize(
    &dword_6F7F58,
    "cyclebutton_l.tga",
    "cyclebutton_l_on.tga",
    -18,
    0,
    -1,
    (char *)&byte_6379E7,
    0);
  unk_6F7F5C = dword_6F7DE8;
  unk_6F7F78 = (int (__cdecl *)(_DWORD, _DWORD))rf_gameplay_difficulty_choice_previous;
  rf_inline_dword_array28_append(dword_6F8320, (int)&dword_6F7F58);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F7FA0, &dword_6F7F58);
  rf_ui_image_button_initialize(
    &dword_6F82D8,
    "cyclebutton_r.tga",
    "cyclebutton_r_on.tga",
    unk_6F7DFC,
    0,
    -1,
    (char *)&byte_6379ED,
    0);
  unk_6F82DC = dword_6F7DE8;
  unk_6F82F8 = (int (__cdecl *)(_DWORD, _DWORD))rf_gameplay_difficulty_choice_next;
  rf_inline_dword_array28_append(dword_6F8320, (int)&dword_6F82D8);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F7FA0, &dword_6F82D8);
  rf_ui_image_button_initialize(
    &dword_6F8410,
    (char *)&unk_6379EF,
    "indicator_selected.tga",
    110,
    16,
    -1,
    (char *)&byte_6379EE,
    0);
  unk_6F8414 = dword_6F7BDC;
  rf_inline_dword_array28_append(dword_6F8320, (int)&dword_6F8410);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F7FA0, &dword_6F8410);
  rf_ui_checkbox_initialize_471300(
    &dword_6F7CC0,
    (int)&unk_6379FD,
    (int)"checkbox_selected.tga",
    "checkbox_checked.tga",
    113,
    67,
    19,
    (char *)&byte_6379F7,
    0);
  unk_6F7CC4 = dword_6F7BDC;
  unk_6F7CE0 = rf_settings_toggle_first_person_weapon;
  byte_6F7D08[0] = *(_BYTE *)(rf_local_fpgun_player + 3894);
  rf_inline_dword_array28_append(dword_6F8320, (int)&dword_6F7CC0);
  rf_inline_dword_array28_append(dword_6F8398, (int)&dword_6F7CC0);
  rf_ui_checkbox_initialize_471300(
    &dword_6F8050,
    (int)&unk_6379FF,
    (int)"checkbox_selected.tga",
    "checkbox_checked.tga",
    113,
    93,
    17,
    (char *)&byte_6379FE,
    0);
  unk_6F8054 = dword_6F7BDC;
  unk_6F8070 = rf_settings_toggle_autoswitch_weapons;
  byte_6F8098[0] = *(_BYTE *)(rf_local_fpgun_player + 3904);
  rf_inline_dword_array28_append(dword_6F8320, (int)&dword_6F8050);
  rf_inline_dword_array28_append(dword_6F8398, (int)&dword_6F8050);
  rf_ui_checkbox_initialize_471300(
    &dword_6F7B90,
    (int)&unk_637A19,
    (int)"checkbox_selected.tga",
    "checkbox_checked.tga",
    113,
    119,
    45,
    (char *)&byte_637A07,
    0);
  unk_6F7B94 = dword_6F7BDC;
  unk_6F7BB0 = rf_settings_toggle_autoswitch_explosives;
  byte_6F7BD8[0] = *(_BYTE *)(rf_local_fpgun_player + 3905) == 0;
  rf_inline_dword_array28_append(dword_6F8320, (int)&dword_6F7B90);
  rf_inline_dword_array28_append(dword_6F8398, (int)&dword_6F7B90);
  unk_6F81E4 = dword_6F7BDC;
  unk_6F8200 = rf_gameplay_priority_group_press_dispatch;
  unk_6F8204 = rf_gameplay_priority_group_drag_dispatch;
  rf_inline_dword_array28_append(dword_6F8398, (int)&unk_6F81E0);
  unk_6F7C98 = dword_6F7BDC;
  unk_6F7CA0 = dword_662428;
  unk_6F7CA4 = dword_66242C;
  unk_6F7CA8 = dword_662430;
  unk_6F7CAC = dword_662434;
  unk_6F7CB4 = rf_gameplay_priority_list_select_from_pointer;
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F81E0, &dword_6F7C94);
  rf_ui_image_button_initialize(
    &dword_6F7DA0,
    (char *)&unk_637A1B,
    "indicator_selected.tga",
    110,
    164,
    -1,
    (char *)&byte_637A1A,
    0);
  unk_6F7DA4 = dword_6F7BDC;
  rf_inline_dword_array28_append(dword_6F8320, (int)&dword_6F7DA0);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F81E0, &dword_6F7DA0);
  rf_ui_slider_initialize_471620(
    (int)unk_6F7D58,
    (int)dword_6F7BDC,
    "slider_bar_vert.tga",
    "slider_bar_vert_on.tga",
    345,
    211,
    16,
    92,
    0.0,
    1.0);
  unk_6F7D78 = rf_gameplay_priority_scroll_from_slider;
  unk_6F7D7C = rf_gameplay_priority_scroll_from_slider;
  rf_inline_dword_array28_append(dword_6F8320, (int)unk_6F7D58);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F81E0, unk_6F7D58);
  rf_ui_image_button_initialize(
    &dword_6F7C50,
    "cyclebutton_u.tga",
    "cyclebutton_u_on.tga",
    344,
    191,
    -1,
    (char *)&byte_637A33,
    unk_6F29AC);
  unk_6F7C54 = dword_6F7BDC;
  unk_6F7C70 = rf_gameplay_priority_scroll_up;
  rf_inline_dword_array28_append(dword_6F8320, (int)&dword_6F7C50);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F81E0, &dword_6F7C50);
  rf_ui_image_button_initialize(
    &dword_6F8290,
    "cyclebutton_d.tga",
    "cyclebutton_d_on.tga",
    344,
    303,
    -1,
    (char *)&byte_637A47,
    unk_6F29AC);
  unk_6F8294 = dword_6F7BDC;
  unk_6F82B0 = rf_gameplay_priority_scroll_down;
  rf_inline_dword_array28_append(dword_6F8320, (int)&dword_6F8290);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F81E0, &dword_6F8290);
  unk_6F7B7C = 0;
  for ( j = 0; j < 32; ++j )
  {
    v3 = *(_DWORD *)(rf_local_fpgun_player + 4 * j + 4436);
    if ( v3 > -1 )
    {
      v0 = rf_string_object_c_str_or_empty((char *)&rf_weapon_records + 1360 * v3);
      if ( _stricmp(v0, byte_637A5E) )
      {
        if ( (unk_912264[340 * v3] & 0x80) != 0 )
          ++unk_6F7B7C;
      }
    }
  }
  rf_ui_image_button_initialize(
    &dword_6F7C08,
    "arrow_up_long.tga",
    "arrow_up_long_on.tga",
    130,
    327,
    22,
    unk_88DE6C,
    unk_6F29AC);
  unk_6F7C0C = dword_6F7BDC;
  unk_6F7C28 = rf_gameplay_priority_move_selected_up;
  rf_inline_dword_array28_append(dword_6F8320, (int)&dword_6F7C08);
  rf_inline_dword_array28_append(dword_6F8398, (int)&dword_6F7C08);
  rf_ui_image_button_initialize(
    &dword_6F7D10,
    "arrow_down_long.tga",
    "arrow_down_long_on.tga",
    232,
    327,
    32,
    unk_88DE70,
    unk_6F29AC);
  unk_6F7D14 = dword_6F7BDC;
  unk_6F7D30 = rf_gameplay_priority_move_selected_down;
  rf_inline_dword_array28_append(dword_6F8320, (int)&dword_6F7D10);
  return rf_inline_dword_array28_append(dword_6F8398, (int)&dword_6F7D10);
}

