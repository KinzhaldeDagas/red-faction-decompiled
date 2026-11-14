// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046A200 rf_ui_performance_options_build
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Noarg. InitbitsDWORD6F7B64 bits1/2/4 cache localized8 labels,High/Medium/Low/Custom,and Trilinear/Bilinear pointers ONCE;rest of body has NO build
// guard/list reset. Construct performance_panel.tga root6F69D4/eight labels;fixed inline35 draw6F7840/focus6F7980 lists via46B570,unchecked append results. Preset
// group7058->4699F0,chooser75A0 four choices/raw player3916;left469C40 NEXT/right469C80 PREVIOUS. Checkboxes
// Shadows7508->469FC0(player3906),Decals77A8->46A040(3907),DynamicLighting7758->46A0C0(3908),load raw bytes. Texture group6BF0->469CC0,chooser6CE8 High/Medium/Low/raw
// player3920;leftNEXT469D70/rightPREVIOUS469DA0. Character group78D0->469DD0,chooser7398 same3/raw player3924;leftNEXT469E50/rightPREVIOUS469E80. Filter group6A00->469EB0,chooser6E58
// Trilinear/Bilinear,zero-extended playerBYTE3912;leftPREVIOUS469F60/rightNEXT469F90. Gamma group6AB0 press+drag46A150,slider6CA0 press46A1B0 with authored binary32
// bounds0x3F333333(~0.7)..0x400CCCCD(~2.2),initialized from global gamma through clamped setter;no own global gamma/percent rewrite at construction. End apply_preset(raw
// player3916):known0..2 overrides previously loaded individual settings with preset tuple;3/custom retains tuple;invalid raw values still commit current tuple. No player/cursor
// validation,save,focus reset or rollback. Parent options build latch normally gates this body;direct repeats append/reconstruct. Native labels/callbacks/x87 arguments and original
// constants independently verified.
int rf_ui_performance_options_build()
{
  int i; // [esp+40h] [ebp-4h]
  int j; // [esp+40h] [ebp-4h]
  int k; // [esp+40h] [ebp-4h]
  int m; // [esp+40h] [ebp-4h]

  if ( (dword_6F7B64 & 1) == 0 )
  {
    dword_6F7B64 |= 1u;
    dword_6F7B44 = (const char *)unk_88DE7C;
    dword_6F7B48 = (const char *)unk_88DE80;
    dword_6F7B4C = (const char *)unk_88DE84;
    dword_6F7B50 = (const char *)unk_88DE88;
    dword_6F7B54 = (const char *)unk_88DE98;
    dword_6F7B58 = (const char *)unk_88DE9C;
    dword_6F7B5C = (const char *)unk_88DEA0;
    dword_6F7B60 = (const char *)unk_88DEA4;
  }
  if ( (dword_6F7B64 & 2) == 0 )
  {
    dword_6F7B64 |= 2u;
    dword_6F7B34[0] = unk_88DB84;
    unk_6F7B38 = unk_88DB80;
    unk_6F7B3C = unk_88DB7C;
    unk_6F7B40 = unk_88D6BC;
  }
  if ( (dword_6F7B64 & 4) == 0 )
  {
    dword_6F7B64 |= 4u;
    dword_6F7B2C[0] = unk_88DEB0;
    unk_6F7B30 = unk_88DEB4;
  }
  rf_ui_panel_initialize_bitmap(dword_6F69D4, "performance_panel.tga", dword_6F29C8, rf_main_menu_title_y);
  rf_ui_label_initialize_measured_text(dword_6F7108, (int)dword_6F69D4, 285, 25, dword_6F7B44, unk_6F29AC);
  rf_inline_dword_array35_append(dword_6F7840, (int)dword_6F7108);
  rf_ui_label_initialize_measured_text(dword_6F7148, (int)dword_6F69D4, 215, 58, dword_6F7B48, unk_6F29AC);
  rf_inline_dword_array35_append(dword_6F7840, (int)dword_6F7148);
  rf_ui_label_initialize_measured_text(dword_6F7188, (int)dword_6F69D4, 215, 84, dword_6F7B4C, unk_6F29AC);
  rf_inline_dword_array35_append(dword_6F7840, (int)dword_6F7188);
  rf_ui_label_initialize_measured_text(dword_6F71C8, (int)dword_6F69D4, 215, 110, dword_6F7B50, unk_6F29AC);
  rf_inline_dword_array35_append(dword_6F7840, (int)dword_6F71C8);
  rf_ui_label_initialize_measured_text(dword_6F7208, (int)dword_6F69D4, 285, 152, dword_6F7B54, unk_6F29AC);
  rf_inline_dword_array35_append(dword_6F7840, (int)dword_6F7208);
  rf_ui_label_initialize_measured_text(dword_6F7248, (int)dword_6F69D4, 285, 187, dword_6F7B58, unk_6F29AC);
  rf_inline_dword_array35_append(dword_6F7840, (int)dword_6F7248);
  rf_ui_label_initialize_measured_text(dword_6F7288, (int)dword_6F69D4, 285, 222, dword_6F7B5C, unk_6F29AC);
  rf_inline_dword_array35_append(dword_6F7840, (int)dword_6F7288);
  rf_ui_label_initialize_measured_text(dword_6F72C8, (int)dword_6F69D4, 285, 257, dword_6F7B60, unk_6F29AC);
  rf_inline_dword_array35_append(dword_6F7840, (int)dword_6F72C8);
  unk_6F705C = dword_6F69D4;
  unk_6F7078 = rf_performance_options_group_press_dispatch;
  rf_inline_dword_array35_append(dword_6F7980, (int)&unk_6F7058);
  rf_ui_cycle_list_set_geometry(dword_6F75A0, (int)dword_6F69D4, 153, 18, 98, 26);
  for ( i = 0; i < 4; ++i )
    rf_ui_cycle_list_append_text(dword_6F75A0, i, (const char *)dword_6F7B34[i], unk_6F29AC);
  unk_6F770C = *(_DWORD *)(rf_local_fpgun_player + 3916);
  rf_inline_dword_array35_append(dword_6F7840, (int)dword_6F75A0);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F7058, dword_6F75A0);
  rf_ui_image_button_initialize(
    &dword_6F7308,
    "cyclebutton_l.tga",
    "cyclebutton_l_on.tga",
    -18,
    0,
    -1,
    (char *)&byte_637689,
    0);
  unk_6F730C = dword_6F75A0;
  unk_6F7328 = (int (__cdecl *)(_DWORD, _DWORD))rf_performance_preset_cycle_next;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F7308);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F7058, &dword_6F7308);
  rf_ui_image_button_initialize(
    &dword_6F7AA0,
    "cyclebutton_r.tga",
    "cyclebutton_r_on.tga",
    unk_6F75B4,
    0,
    -1,
    (char *)&byte_63768A,
    0);
  unk_6F7AA4 = dword_6F75A0;
  unk_6F7AC0 = (int (__cdecl *)(_DWORD, _DWORD))rf_performance_preset_cycle_previous;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F7AA0);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F7058, &dword_6F7AA0);
  rf_ui_image_button_initialize(
    &dword_6F6BA8,
    (char *)&unk_637696,
    "indicator_selected.tga",
    110,
    17,
    -1,
    (char *)&byte_63768B,
    0);
  unk_6F6BAC = dword_6F69D4;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F6BA8);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F7058, &dword_6F6BA8);
  rf_ui_checkbox_initialize_471300(
    &dword_6F7508,
    (int)&unk_6376A9,
    (int)"checkbox_selected.tga",
    "checkbox_checked.tga",
    113,
    52,
    31,
    (char *)&byte_637697,
    0);
  unk_6F750C = dword_6F69D4;
  unk_6F7528 = rf_performance_toggle_shadows;
  byte_6F7550[0] = *(_BYTE *)(rf_local_fpgun_player + 3906);
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F7508);
  rf_inline_dword_array35_append(dword_6F7980, (int)&dword_6F7508);
  rf_ui_checkbox_initialize_471300(
    &dword_6F77A8,
    (int)&unk_6376AB,
    (int)"checkbox_selected.tga",
    "checkbox_checked.tga",
    113,
    78,
    32,
    (char *)&byte_6376AA,
    0);
  unk_6F77AC = dword_6F69D4;
  unk_6F77C8 = rf_performance_toggle_decals;
  byte_6F77F0[0] = *(_BYTE *)(rf_local_fpgun_player + 3907);
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F77A8);
  rf_inline_dword_array35_append(dword_6F7980, (int)&dword_6F77A8);
  rf_ui_checkbox_initialize_471300(
    &dword_6F7758,
    (int)&unk_6376D1,
    (int)"checkbox_selected.tga",
    "checkbox_checked.tga",
    113,
    104,
    21,
    (char *)&byte_6376BF,
    0);
  unk_6F775C = dword_6F69D4;
  unk_6F7778 = rf_performance_toggle_dynamic_lighting;
  byte_6F77A0[0] = *(_BYTE *)(rf_local_fpgun_player + 3908);
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F7758);
  rf_inline_dword_array35_append(dword_6F7980, (int)&dword_6F7758);
  unk_6F6BF4 = dword_6F69D4;
  unk_6F6C10 = rf_performance_texture_group_press_apply;
  rf_inline_dword_array35_append(dword_6F7980, (int)&unk_6F6BF0);
  rf_ui_cycle_list_set_geometry(dword_6F6CE8, (int)dword_6F69D4, 153, 145, 98, 26);
  for ( j = 0; j < 3; ++j )
    rf_ui_cycle_list_append_text(dword_6F6CE8, unk_6F29AC, (const char *)dword_6F7B34[j], unk_6F29AC);
  unk_6F6E54 = *(_DWORD *)(rf_local_fpgun_player + 3920);
  rf_inline_dword_array35_append(dword_6F7840, (int)dword_6F6CE8);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F6BF0, dword_6F6CE8);
  rf_ui_image_button_initialize(
    &dword_6F7A58,
    "cyclebutton_l.tga",
    "cyclebutton_l_on.tga",
    -18,
    0,
    -1,
    (char *)&byte_6376D2,
    0);
  unk_6F7A5C = dword_6F6CE8;
  unk_6F7A78 = (int (__cdecl *)(_DWORD, _DWORD))rf_performance_texture_choice_next;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F7A58);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F6BF0, &dword_6F7A58);
  rf_ui_image_button_initialize(
    &dword_6F7010,
    "cyclebutton_r.tga",
    "cyclebutton_r_on.tga",
    unk_6F6CFC,
    0,
    -1,
    (char *)&byte_6376D3,
    0);
  unk_6F7014 = dword_6F6CE8;
  unk_6F7030 = (int (__cdecl *)(_DWORD, _DWORD))rf_performance_texture_choice_previous;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F7010);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F6BF0, &dword_6F7010);
  rf_ui_image_button_initialize(
    &dword_6F6B60,
    (char *)&unk_6376F1,
    "indicator_selected.tga",
    110,
    144,
    -1,
    (char *)&byte_6376DB,
    0);
  unk_6F6B64 = dword_6F69D4;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F6B60);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F6BF0, &dword_6F6B60);
  unk_6F78D4 = dword_6F69D4;
  unk_6F78F0 = rf_performance_character_detail_group_press_apply;
  rf_inline_dword_array35_append(dword_6F7980, (int)&unk_6F78D0);
  rf_ui_cycle_list_set_geometry(dword_6F7398, (int)dword_6F69D4, 153, 179, 98, 26);
  for ( k = 0; k < 3; ++k )
    rf_ui_cycle_list_append_text(dword_6F7398, dword_6F7B34[k], (const char *)dword_6F7B34[k], unk_6F29AC);
  unk_6F7504 = *(_DWORD *)(rf_local_fpgun_player + 3924);
  rf_inline_dword_array35_append(dword_6F7840, (int)dword_6F7398);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F78D0, dword_6F7398);
  rf_ui_image_button_initialize(
    &dword_6F7A10,
    "cyclebutton_l.tga",
    "cyclebutton_l_on.tga",
    -18,
    0,
    -1,
    (char *)&byte_6376F2,
    0);
  unk_6F7A14 = dword_6F7398;
  unk_6F7A30 = (int (__cdecl *)(_DWORD, _DWORD))rf_performance_character_detail_choice_next;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F7A10);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F78D0, &dword_6F7A10);
  rf_ui_image_button_initialize(
    &dword_6F7350,
    "cyclebutton_r.tga",
    "cyclebutton_r_on.tga",
    unk_6F73AC,
    0,
    -1,
    (char *)&byte_6376F3,
    0);
  unk_6F7354 = dword_6F7398;
  unk_6F7370 = (int (__cdecl *)(_DWORD, _DWORD))rf_performance_character_detail_choice_previous;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F7350);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F78D0, &dword_6F7350);
  rf_ui_image_button_initialize(
    &dword_6F7710,
    (char *)&unk_637707,
    "indicator_selected.tga",
    110,
    178,
    -1,
    (char *)&byte_6376FB,
    0);
  unk_6F7714 = dword_6F69D4;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F7710);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F78D0, &dword_6F7710);
  unk_6F6A04 = dword_6F69D4;
  unk_6F6A20 = rf_performance_filter_group_press_apply;
  rf_inline_dword_array35_append(dword_6F7980, (int)&unk_6F6A00);
  rf_ui_cycle_list_set_geometry(dword_6F6E58, (int)dword_6F69D4, 153, 213, 98, 26);
  for ( m = 0; m < 2; ++m )
    rf_ui_cycle_list_append_text(dword_6F6E58, m, (const char *)dword_6F7B2C[m], unk_6F29AC);
  unk_6F6FC4 = *(unsigned __int8 *)(rf_local_fpgun_player + 3912);
  rf_inline_dword_array35_append(dword_6F7840, (int)dword_6F6E58);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F6A00, dword_6F6E58);
  rf_ui_image_button_initialize(
    &dword_6F77F8,
    "cyclebutton_l.tga",
    "cyclebutton_l_on.tga",
    -18,
    0,
    -1,
    (char *)&byte_63770D,
    0);
  unk_6F77FC = dword_6F6E58;
  unk_6F7818 = (int (__cdecl *)(_DWORD, _DWORD))rf_performance_filter_choice_previous;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F77F8);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F6A00, &dword_6F77F8);
  rf_ui_image_button_initialize(
    &dword_6F6FC8,
    "cyclebutton_r.tga",
    "cyclebutton_r_on.tga",
    unk_6F6E6C,
    0,
    -1,
    (char *)&byte_63770E,
    0);
  unk_6F6FCC = dword_6F6E58;
  unk_6F6FE8 = (int (__cdecl *)(_DWORD, _DWORD))rf_performance_filter_choice_next;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F6FC8);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F6A00, &dword_6F6FC8);
  rf_ui_image_button_initialize(
    &dword_6F7AE8,
    (char *)&unk_637719,
    "indicator_selected.tga",
    110,
    211,
    -1,
    (char *)&byte_63770F,
    0);
  unk_6F7AEC = dword_6F69D4;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F7AE8);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F6A00, &dword_6F7AE8);
  unk_6F6AB4 = dword_6F69D4;
  unk_6F6AD0 = rf_performance_gamma_group_dispatch;
  unk_6F6AD4 = rf_performance_gamma_group_dispatch;
  rf_inline_dword_array35_append(dword_6F7980, (int)&unk_6F6AB0);
  rf_ui_slider_initialize_471620(
    (int)flt_6F6CA0,
    (int)dword_6F69D4,
    "slider_bar.tga",
    "slider_bar_on.tga",
    145,
    250,
    118,
    20,
    0.69999999,
    2.2);
  unk_6F6CC0 = rf_ui_performance_gamma_slider_changed;
  rf_ui_slider_set_value_clamped(flt_6F6CA0, rf_graphics_gamma);
  rf_inline_dword_array35_append(dword_6F7840, (int)flt_6F6CA0);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F6AB0, flt_6F6CA0);
  rf_ui_image_button_initialize(
    &dword_6F7558,
    (char *)&unk_63771B,
    "indicator_selected.tga",
    110,
    246,
    -1,
    (char *)&byte_63771A,
    0);
  unk_6F755C = dword_6F69D4;
  rf_inline_dword_array35_append(dword_6F7840, (int)&dword_6F7558);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F6AB0, &dword_6F7558);
  return rf_performance_options_apply_preset(*(_DWORD *)(rf_local_fpgun_player + 3916));
}

