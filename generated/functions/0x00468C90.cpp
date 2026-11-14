// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00468C90 rf_controls_build_panel_and_load_player
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg;NO own build latch/list reset. visibleRows6F62A8=floor(binary32(listHeight66201C*scaleY/pixelRowHeight));actionCount6F62AC=unchecked playerDWORD3824. Build
// controls_panel.tga/root6F632C,localized Mouse Sensitivity/Mouse Y Invert labels. Sensitivity group6778 press+drag->468060,slider6730 press->4680C0 with initial
// playerFLOAT228;invert checkbox6870->4680F0 loads raw playerBYTE3845. Binding group64B8 press->468730/drag->4687B0;list62C0 geometry662010..1C press->468320;vertical slider6428
// press+drag4688D0;up/down468810/8860;help63A0;ChangeBinding6358->468160;Defaults62E8->4682D0. Populate inline30 draw/focus lists6F68C0/6F6940 and meta children;append results
// ignored. End capture468020. Parent options build latch normally limits invocation;direct repeats reconstruct controls/append duplicates until capacity. Does not reset
// focus6F62B0,scroll6F62B8,selected6F62BC,validate actionCount/player or save. Localized fallbacks,callback addresses and original geometry verified.
int *rf_controls_build_panel_and_load_player()
{
  int height_select_current; // eax
  float value; // [esp+18h] [ebp-4h]

  value = (double)dword_66201C * rf_ui_scale_y / (double)dword_6F299C;
  unk_6F62A8 = (int)rf_floor_float(value);
  unk_6F62AC = *(_DWORD *)(rf_local_fpgun_player + 3824);
  rf_ui_panel_initialize_bitmap(dword_6F632C, "controls_panel.tga", dword_6F29C8, rf_main_menu_title_y);
  rf_ui_label_initialize_measured_text(dword_6F65B0, (int)dword_6F632C, 285, 22, unk_88DE74, unk_6F29AC);
  rf_inline_dword_array30_append(unk_6F68C0, (int)dword_6F65B0);
  rf_ui_label_initialize_measured_text(dword_6F65F0, (int)dword_6F632C, 215, 55, unk_88DE78, unk_6F29AC);
  rf_inline_dword_array30_append(unk_6F68C0, (int)dword_6F65F0);
  unk_6F677C = dword_6F632C;
  unk_6F6798 = rf_controls_sensitivity_group_dispatch;
  unk_6F679C = rf_controls_sensitivity_group_dispatch;
  rf_inline_dword_array30_append(unk_6F6940, (int)&unk_6F6778);
  rf_ui_slider_initialize_471620(
    (int)unk_6F6730,
    (int)dword_6F632C,
    "slider_bar.tga",
    "slider_bar_on.tga",
    138,
    21,
    118,
    20,
    0.0,
    1.0);
  unk_6F6750 = rf_controls_sensitivity_from_pointer;
  rf_ui_slider_set_value_clamped(unk_6F6730, *(float *)(rf_local_fpgun_player + 228));
  rf_inline_dword_array30_append(unk_6F68C0, (int)unk_6F6730);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F6778, unk_6F6730);
  rf_ui_image_button_initialize(
    &dword_6F6470,
    (char *)&unk_6373BF,
    "indicator_selected.tga",
    111,
    17,
    -1,
    (char *)&byte_6373B3,
    0);
  unk_6F6474 = dword_6F632C;
  rf_inline_dword_array30_append(unk_6F68C0, (int)&dword_6F6470);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F6778, &dword_6F6470);
  rf_ui_checkbox_initialize_471300(
    &unk_6F6870,
    (int)&unk_6373CB,
    (int)"checkbox_selected.tga",
    "checkbox_checked.tga",
    113,
    49,
    23,
    (char *)&byte_6373CA,
    0);
  unk_6F6874 = dword_6F632C;
  unk_6F6890 = rf_controls_toggle_mouse_y_invert;
  byte_6F68B8[0] = *(_BYTE *)(rf_local_fpgun_player + 3845);
  rf_inline_dword_array30_append(unk_6F68C0, (int)&unk_6F6870);
  rf_inline_dword_array30_append(unk_6F6940, (int)&unk_6F6870);
  unk_6F64BC = dword_6F632C;
  unk_6F64D8 = rf_controls_binding_group_press_dispatch;
  unk_6F64DC = rf_controls_binding_group_drag_dispatch;
  rf_inline_dword_array30_append(unk_6F6940, (int)&unk_6F64B8);
  rf_ui_image_button_initialize(
    &dword_6F6568,
    (char *)&unk_6373D6,
    "indicator_selected.tga",
    110,
    106,
    -1,
    (char *)&byte_6373D5,
    0);
  unk_6F656C = dword_6F632C;
  rf_inline_dword_array30_append(unk_6F68C0, (int)&dword_6F6568);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F64B8, &dword_6F6568);
  unk_6F62C4 = dword_6F632C;
  unk_6F62CC = dword_662010;
  unk_6F62D0 = dword_662014;
  unk_6F62D4 = dword_662018;
  unk_6F62D8 = dword_66201C;
  unk_6F62E0 = rf_controls_action_list_press;
  rf_inline_dword_array30_append(unk_6F68C0, (int)&dword_6F62C0);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F64B8, &dword_6F62C0);
  rf_ui_slider_initialize_471620(
    (int)unk_6F6428,
    (int)dword_6F632C,
    "slider_bar_vert.tga",
    "slider_bar_vert_on.tga",
    418,
    130,
    16,
    132,
    0.0,
    1.0);
  unk_6F6448 = rf_controls_scroll_actions_from_slider;
  unk_6F644C = rf_controls_scroll_actions_from_slider;
  rf_inline_dword_array30_append(unk_6F68C0, (int)unk_6F6428);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F64B8, unk_6F6428);
  rf_ui_image_button_initialize(
    &dword_6F6828,
    "cyclebutton_u.tga",
    "cyclebutton_u_on.tga",
    417,
    110,
    -1,
    (char *)&byte_6373D7,
    0);
  unk_6F682C = dword_6F632C;
  unk_6F6848 = rf_controls_scroll_actions_up;
  rf_inline_dword_array30_append(unk_6F68C0, (int)&dword_6F6828);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F64B8, &dword_6F6828);
  rf_ui_image_button_initialize(
    &dword_6F63E0,
    "cyclebutton_d.tga",
    "cyclebutton_d_on.tga",
    417,
    262,
    -1,
    (char *)&byte_6373DD,
    0);
  unk_6F63E4 = dword_6F632C;
  unk_6F6400 = rf_controls_scroll_actions_down;
  rf_inline_dword_array30_append(unk_6F68C0, (int)&dword_6F63E0);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F64B8, &dword_6F63E0);
  height_select_current = rf_font_get_height_select_current(unk_6F29AC);
  rf_ui_text_widget_initialize(
    dword_6F63A0,
    (int)dword_6F632C,
    133,
    94,
    150,
    height_select_current,
    (char *)&byte_6373DE,
    0);
  rf_inline_dword_array30_append(unk_6F68C0, (int)dword_6F63A0);
  rf_ui_image_button_initialize(
    &dword_6F6358,
    (char *)&unk_6373DF,
    "lit_button_selected.tga",
    112,
    294,
    46,
    unk_88D6D0,
    unk_6F29AC);
  unk_6F635C = dword_6F632C;
  unk_6F6378 = rf_controls_change_selected_binding;
  rf_inline_dword_array30_append(unk_6F68C0, (int)&dword_6F6358);
  rf_inline_dword_array30_append(unk_6F6940, (int)&dword_6F6358);
  rf_ui_image_button_initialize(
    &dword_6F62E8,
    byte_6373E9,
    "lit_button_selected.tga",
    112,
    328,
    32,
    unk_88DE4C,
    unk_6F29AC);
  unk_6F62EC = dword_6F632C;
  unk_6F6308 = rf_controls_prompt_reset_defaults;
  rf_inline_dword_array30_append(unk_6F68C0, (int)&dword_6F62E8);
  rf_inline_dword_array30_append(unk_6F6940, (int)&dword_6F62E8);
  return rf_controls_binding_capture_end();
}

