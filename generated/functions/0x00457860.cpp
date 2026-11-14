// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00457860 rf_save_list_b_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): SAVE screen initialization. Every entry zeroes control index6F23D4,offset6F23E8,selected6F23EC,modeBYTE6F23D0; body
// currentX6F23CC=float(signed6F29C8),velocity6F23E0=661E50;title currentX6F23D8=float(signed6F29C4),velocity6F23DC=661E60; arm deadline6F2664(0). Calls456160 enumeration WITHOUT
// prior record-array release, so repeated entry can append duplicates unless external caller cleared records. Nonzero initializedBYTE6F23E4 skips construction; first entry sets1
// BEFORE resources/row math. First-only visible6F23C8=convert(floor(FLOAT32(signed661E20*scaleY/signed rowheight6F299C))), no zero/min guard or resolution refresh. Body6F24A4
// savegame_panel.tga at(6F29C8,58);title6F2434 titlebar.tga at(6F29C4,6F29B8);label6F2958 parenttitle,(140,12),localized88E2D0,pausefont. Group6F25B8 parentbody,callback4564C0;
// edit6F2748 parentbody,(50,41),initial savegame,font6F29AC,raw final argument200,callback456520; indicator6F2700 parentbody,(27,35). Add edit/indicator children to group via4720F0,
// one stack child argument. Save6F26B8 parentbody,(275,35),hotkey31,label88E2D8,callback456720; back6F23F0 parentbody,(28,330),hotkey48,label88E088,callback4564B0. Group6F27F8
// parentbody,callback456950; list6F2590 parentbody geometry661E14/18/1C/20,callback4569B0;indicator6F2668 parentbody,(26,661E18-30); add list/indicator children to second group.
// Slider6F2910 parentbody at(661E14+661E1C+2,661E18+18),width16,height661E20-32,range0..1,callbacks456AA0. Up6F27B0 sameX,Y661E18-2,callback456B20;down6F2460
// Y661E18+661E20-16,callback456BC0; parentbody. Headers6F24D0/2510/2550 parentlist,X661DFC/E00/E04+1,Y-25,width661E08/E0C/E10-2,height20,labels88E3A4/88E2C4/88E3A8,font6F29AC.
// Render6F28A8 append order [2748,2700,26B8,23F0,2590,2668,2910,27B0,2460,24D0,2510,2550];interactive6F28EC [25B8,26B8,23F0,27F8,2910,27B0,2460],6F prefixes. No own group child-count
// reset, duplicate/resource/append-failure guard or rollback; once flag persists failures. Return append/flag residue.
int rf_save_list_b_initialize()
{
  int result; // eax
  float value; // [esp+20h] [ebp-4h]

  dword_6F23D4 = 0;
  dword_6F23E8 = 0;
  dword_6F23EC = 0;
  byte_6F23D0[0] = 0;
  unk_6F23CC = (float)unk_6F29C8;
  unk_6F23E0 = rf_ui_open_transition_speed;
  unk_6F23D8 = (float)unk_6F29C4;
  unk_6F23DC = flt_661E60;
  rf_clock_deadline_set_wrapped_offset(&dword_6F2664, 0);
  rf_save_list_b_enumerate_valid_save_records();
  result = byte_6F23E4[0];
  if ( !byte_6F23E4[0] )
  {
    byte_6F23E4[0] = 1;
    value = (double)dword_661E20 * rf_ui_scale_y / (double)dword_6F299C;
    unk_6F23C8 = (int)rf_floor_float(value);
    rf_ui_panel_initialize_bitmap(dword_6F24A4, "savegame_panel.tga", unk_6F29C8, rf_main_menu_title_y);
    rf_ui_panel_initialize_bitmap(dword_6F2434, "titlebar.tga", unk_6F29C4, unk_6F29B8);
    rf_ui_label_initialize_measured_text(dword_6F2958, (int)dword_6F2434, 140, 12, unk_88E2D0, rf_pause_font);
    unk_6F25BC = dword_6F24A4;
    unk_6F25D8 = rf_save_list_b_dispatch_edit_group_click;
    rf_inline_dword_array7_append_exact_limit(byte_6F28EC, (int)&unk_6F25B8);
    rf_ui_edit_initialize((int)byte_6F2748, (int)dword_6F24A4, 50, 41, "savegame", unk_6F29AC, 200);
    unk_6F2768 = rf_frontend_toggle_byte6f23d0;
    rf_inline_dword_array16_append_exact_limit(dword_6F28A8, (int)byte_6F2748);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F25B8, byte_6F2748);
    rf_ui_image_button_initialize(
      &dword_6F2700,
      (char *)&unk_635491,
      "indicator_selected.tga",
      27,
      35,
      -1,
      (char *)&byte_63548B,
      0);
    unk_6F2704 = dword_6F24A4;
    rf_inline_dword_array16_append_exact_limit(dword_6F28A8, (int)&dword_6F2700);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F25B8, &dword_6F2700);
    rf_ui_image_button_initialize(
      &dword_6F26B8,
      (char *)&unk_635492,
      "lit_button_small_selected.tga",
      275,
      35,
      31,
      unk_88E2D8,
      unk_6F29AC);
    unk_6F26BC = dword_6F24A4;
    unk_6F26D8 = rf_save_list_b_request_save;
    rf_inline_dword_array16_append_exact_limit(dword_6F28A8, (int)&dword_6F26B8);
    rf_inline_dword_array7_append_exact_limit(byte_6F28EC, (int)&dword_6F26B8);
    rf_ui_image_button_initialize(
      &dword_6F23F0,
      (char *)&unk_635493,
      "lit_button_selected.tga",
      28,
      330,
      48,
      unk_88E088,
      unk_6F29AC);
    unk_6F23F4 = dword_6F24A4;
    unk_6F2410 = rf_frontend_panel_pop_adapter_4564b0;
    rf_inline_dword_array16_append_exact_limit(dword_6F28A8, (int)&dword_6F23F0);
    rf_inline_dword_array7_append_exact_limit(byte_6F28EC, (int)&dword_6F23F0);
    unk_6F27FC = dword_6F24A4;
    unk_6F2818 = rf_save_list_b_dispatch_list_group_click;
    rf_inline_dword_array7_append_exact_limit(byte_6F28EC, (int)&unk_6F27F8);
    unk_6F2594 = dword_6F24A4;
    unk_6F259C = dword_661E14;
    unk_6F25A0 = dword_661E18;
    unk_6F25A4 = dword_661E1C;
    unk_6F25A8 = dword_661E20;
    unk_6F25B0 = rf_save_list_b_select_or_activate_row;
    rf_inline_dword_array16_append_exact_limit(dword_6F28A8, (int)&dword_6F2590);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F27F8, &dword_6F2590);
    rf_ui_image_button_initialize(
      &dword_6F2668,
      (char *)&unk_63549A,
      "indicator_selected.tga",
      26,
      dword_661E18 - 30,
      -1,
      (char *)&byte_635499,
      0);
    unk_6F266C = dword_6F24A4;
    rf_inline_dword_array16_append_exact_limit(dword_6F28A8, (int)&dword_6F2668);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F27F8, &dword_6F2668);
    rf_ui_slider_initialize_471620(
      (int)unk_6F2910,
      (int)dword_6F24A4,
      "slider_bar_vert.tga",
      "slider_bar_vert_on.tga",
      dword_661E14 + dword_661E1C + 2,
      dword_661E18 + 18,
      16,
      dword_661E20 - 32,
      0.0,
      1.0);
    unk_6F2930 = rf_save_list_b_scroll_from_slider;
    unk_6F2934 = rf_save_list_b_scroll_from_slider;
    rf_inline_dword_array16_append_exact_limit(dword_6F28A8, (int)unk_6F2910);
    rf_inline_dword_array7_append_exact_limit(byte_6F28EC, (int)unk_6F2910);
    rf_ui_image_button_initialize(
      &dword_6F27B0,
      "cyclebutton_u.tga",
      "cyclebutton_u_on.tga",
      dword_661E14 + dword_661E1C + 2,
      dword_661E18 - 2,
      -1,
      (char *)&byte_63549B,
      0);
    unk_6F27B4 = dword_6F24A4;
    unk_6F27D0 = rf_save_list_b_scroll_up_one;
    rf_inline_dword_array16_append_exact_limit(dword_6F28A8, (int)&dword_6F27B0);
    rf_inline_dword_array7_append_exact_limit(byte_6F28EC, (int)&dword_6F27B0);
    rf_ui_image_button_initialize(
      &dword_6F2460,
      "cyclebutton_d.tga",
      "cyclebutton_d_on.tga",
      dword_661E14 + dword_661E1C + 2,
      dword_661E18 + dword_661E20 - 16,
      -1,
      (char *)byte_6354B2,
      0);
    unk_6F2464 = dword_6F24A4;
    unk_6F2480 = rf_save_list_b_scroll_down_one;
    rf_inline_dword_array16_append_exact_limit(dword_6F28A8, (int)&dword_6F2460);
    rf_inline_dword_array7_append_exact_limit(byte_6F28EC, (int)&dword_6F2460);
    rf_ui_text_widget_initialize(
      dword_6F24D0,
      (int)&dword_6F2590,
      dword_661DFC + 1,
      -25,
      dword_661E08 - 2,
      20,
      unk_88E3A4,
      unk_6F29AC);
    rf_inline_dword_array16_append_exact_limit(dword_6F28A8, (int)dword_6F24D0);
    rf_ui_text_widget_initialize(
      dword_6F2510,
      (int)&dword_6F2590,
      dword_661E00 + 1,
      -25,
      dword_661E0C - 2,
      20,
      unk_88E2C4,
      unk_6F29AC);
    rf_inline_dword_array16_append_exact_limit(dword_6F28A8, (int)dword_6F2510);
    rf_ui_text_widget_initialize(
      dword_6F2550,
      (int)&dword_6F2590,
      dword_661E04 + 1,
      -25,
      dword_661E10 - 2,
      20,
      unk_88E3A8,
      unk_6F29AC);
    return rf_inline_dword_array16_append_exact_limit(dword_6F28A8, (int)dword_6F2550);
  }
  return result;
}

