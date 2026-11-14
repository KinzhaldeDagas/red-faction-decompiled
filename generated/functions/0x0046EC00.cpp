// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046EC00 rf_ui_modal_build_controls
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Builds global modal controls with no own latch or list reset. Loads popup_top.tga at(120,120), popup_buttons.tga at(120,230). Top title6F8FA0=(20,8,300,20). Four72-byte
// action records6F8FE0+72*i parent bottom at(121,134/96/58/20), selected-button textures, initial hotkey-1, BYTE9=0, callbacks46E930/950/970/990. Appends each to draw inline20
// list6F8F30 and focus inline5 list6F8F84, clears user callback+68, calls set_focus on EACH. Password box6F8D48 at(85,50) parent top, indicator6F8D78 at(-20,0) parent password,
// edit6F8DC0 at(5,5), width230/font6F29A8 parent password; all are draw-list and edit-meta6F8E58 children. Appends edit meta as focus index4 and clears its flag9. Adds3 body
// widgets6F8C88+64*i parent top at(20,20*(i+2)),350x20. Does not initialize active/focus globals or reject repeated calls.
int rf_ui_modal_build_controls()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  rf_ui_panel_initialize_bitmap(dword_6F8F04, "popup_top.tga", 120, 120);
  rf_ui_panel_initialize_bitmap(dword_6F8E28, "popup_buttons.tga", 120, 230);
  rf_ui_text_widget_initialize(dword_6F8FA0, (int)dword_6F8F04, 20, 8, 300, 20, (char *)&byte_637E9E, 0);
  rf_inline_dword_array20_append(unk_6F8F30, (int)dword_6F8FA0);
  rf_ui_image_button_initialize(
    &dword_6F8FE0,
    (char *)&unk_637EB2,
    "popup_button_select.tga",
    121,
    134,
    -1,
    (char *)&byte_637E9F,
    0);
  unk_6F8FE4 = dword_6F8E28;
  unk_6F8FE9 = 0;
  unk_6F9000 = rf_ui_modal_action0_dispatch;
  rf_inline_dword_array20_append(unk_6F8F30, (int)&dword_6F8FE0);
  rf_inline_dword_array5_append(unk_6F8F84, (int)&dword_6F8FE0);
  unk_6F9024 = nullptr;
  rf_ui_button_set_focus(&dword_6F8FE0);
  rf_ui_image_button_initialize(
    &dword_6F9028,
    (char *)&unk_637EE4,
    "popup_button_select.tga",
    121,
    96,
    -1,
    (char *)&byte_637EB3,
    0);
  unk_6F902C = dword_6F8E28;
  unk_6F9031 = 0;
  unk_6F9048 = rf_ui_modal_action1_dispatch;
  rf_inline_dword_array20_append(unk_6F8F30, (int)&dword_6F9028);
  rf_inline_dword_array5_append(unk_6F8F84, (int)&dword_6F9028);
  unk_6F906C = nullptr;
  rf_ui_button_set_focus(&dword_6F9028);
  rf_ui_image_button_initialize(
    &dword_6F9070,
    (char *)&unk_637EE6,
    "popup_button_select.tga",
    121,
    58,
    -1,
    (char *)&byte_637EE5,
    0);
  unk_6F9074 = dword_6F8E28;
  unk_6F9079 = 0;
  unk_6F9090 = rf_ui_modal_action2_dispatch;
  rf_inline_dword_array20_append(unk_6F8F30, (int)&dword_6F9070);
  rf_inline_dword_array5_append(unk_6F8F84, (int)&dword_6F9070);
  unk_6F90B4 = nullptr;
  rf_ui_button_set_focus(&dword_6F9070);
  rf_ui_image_button_initialize(
    &dword_6F90B8,
    (char *)&unk_637F18,
    "popup_button_select.tga",
    121,
    20,
    -1,
    (char *)&byte_637EE7,
    0);
  unk_6F90BC = dword_6F8E28;
  unk_6F90C1 = 0;
  unk_6F90D8 = rf_ui_modal_action3_dispatch;
  rf_inline_dword_array20_append(unk_6F8F30, (int)&dword_6F90B8);
  rf_inline_dword_array5_append(unk_6F8F84, (int)&dword_6F90B8);
  unk_6F90FC = nullptr;
  rf_ui_button_set_focus(&dword_6F90B8);
  rf_ui_panel_initialize_bitmap(&dword_6F8D48, "password_box.tga", 85, 50);
  unk_6F8D4C = dword_6F8F04;
  rf_inline_dword_array20_append(unk_6F8F30, (int)&dword_6F8D48);
  rf_ui_meta_control_add_child_and_expand_bounds(unk_6F8E58, &dword_6F8D48);
  rf_ui_image_button_initialize(
    &dword_6F8D78,
    "indicator.tga",
    "indicator_selected.tga",
    -20,
    0,
    -1,
    (char *)&byte_637F19,
    0);
  unk_6F8D7C = &dword_6F8D48;
  rf_inline_dword_array20_append(unk_6F8F30, (int)&dword_6F8D78);
  rf_ui_meta_control_add_child_and_expand_bounds(unk_6F8E58, &dword_6F8D78);
  rf_ui_edit_initialize((int)&unk_6F8DC0, (int)&dword_6F8D48, 5, 5, (char *)&unk_637F1A, unk_6F29A8, 230);
  rf_inline_dword_array20_append(unk_6F8F30, (int)&unk_6F8DC0);
  rf_ui_meta_control_add_child_and_expand_bounds(unk_6F8E58, &unk_6F8DC0);
  rf_inline_dword_array5_append(unk_6F8F84, (int)unk_6F8E58);
  result = rf_ui_meta_control_clear_flag9(unk_6F8E58);
  for ( i = 0; i < 3; ++i )
  {
    rf_ui_text_widget_initialize(
      (int *)&unk_6F8C88 + 16 * i,
      (int)dword_6F8F04,
      20,
      20 * (i + 2),
      350,
      20,
      (char *)&byte_637F1B,
      0);
    result = rf_inline_dword_array20_append(unk_6F8F30, (int)&unk_6F8C88 + 64 * i);
  }
  return result;
}

