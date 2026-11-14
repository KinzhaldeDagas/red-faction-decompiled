// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004555D0 rf_save_list_a_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): LOAD screen initialization. Every entry first releases records6F21AC via517F40 then enumerates455AD0; zeroes control index6F1F88,offset6F1F9C,selected6F1FA0
// and arms deadline6F21FC with0. Initializes body currentX6F1F84 from signed6F29C8,velocity6F1F94 from661E50; title currentX6F1F8C from signed6F29C4,velocity6F1F90 from661E60.
// Nonzero initializedBYTE6F1F98 skips construction and returns incidental flag; first entry sets flag1 BEFORE row computation/resources, no rollback. First-only
// visible6F1F80=conversion(floor(FLOAT32(signed661DF8*scaleY/signed rowheight6F299C))); no denominator/minimum guard or resolution refresh. Initialize body6F2014 loadgame_panel.tga
// at(6F29C8,58),title6F1FA4 titlebar.tga at(6F29C4,6F29B8),label6F2388 parenttitle at(140,12),localized88E3A0,pausefont. List6F235C parentbody
// geometry661DEC/DF0/DF4/DF8,callback454890. Indicator6F2318 parentbody at(26,661DF0-30). Slider6F2200 parentbody at(661DEC+661DF4+2,661DF0+18),16x185,range0..1,click/drag454960;
// up6F22B8 at sameX,Y661DF0-2,callback4549E0; down6F21B8 atY661DF0+203,callback454A80. Three headers6F2040/2080/20C0 parentlist at
// X661DD4/DD8/DDC+1,Y-25,width661DE0/DE4/DE8-2,height20,localized88E3A4/88E2C4/88E3A8,font6F29AC. Load6F2248 at(28,296),hotkey38,label88E2CC,callback4545C0; back6F1FD0
// at(28,330),hotkey48,label88E088,callback454880; both parentbody,font6F29AC. Append render6F228C order [235C,2318,2200,22B8,21B8,2040,2080,20C0,2248,1FD0] with6F prefix. Append
// interactive6F22FC order [235C,2200,22B8,21B8,2248,1FD0]. All localized branches bypass embedded English. No own array-count reset inside once branch or resource/append-result
// validation; final EAX append/flag residue.
int rf_save_list_a_initialize()
{
  int result; // eax
  float value; // [esp+20h] [ebp-4h]

  rf_pointer_array_release_storage((void **)dword_6F21AC);
  rf_save_list_a_enumerate_records();
  dword_6F1F88 = 0;
  dword_6F1F9C = 0;
  dword_6F1FA0 = 0;
  rf_clock_deadline_set_wrapped_offset(&dword_6F21FC, 0);
  unk_6F1F84 = (float)unk_6F29C8;
  unk_6F1F94 = rf_ui_open_transition_speed;
  unk_6F1F8C = (float)unk_6F29C4;
  unk_6F1F90 = flt_661E60;
  result = byte_6F1F98[0];
  if ( !byte_6F1F98[0] )
  {
    byte_6F1F98[0] = 1;
    value = (double)dword_661DF8 * rf_ui_scale_y / (double)dword_6F299C;
    unk_6F1F80 = (int)rf_floor_float(value);
    rf_ui_panel_initialize_bitmap(dword_6F2014, "loadgame_panel.tga", unk_6F29C8, rf_main_menu_title_y);
    rf_ui_panel_initialize_bitmap(dword_6F1FA4, "titlebar.tga", unk_6F29C4, unk_6F29B8);
    rf_ui_label_initialize_measured_text(dword_6F2388, (int)dword_6F1FA4, 140, 12, unk_88E3A0, rf_pause_font);
    unk_6F2360 = dword_6F2014;
    unk_6F2368 = dword_661DEC;
    unk_6F236C = dword_661DF0;
    unk_6F2370 = dword_661DF4;
    unk_6F2374 = dword_661DF8;
    unk_6F237C = rf_save_list_a_select_or_activate_row;
    rf_inline_dword_array10_append(dword_6F228C, (int)&dword_6F235C);
    rf_inline_dword_array6_append_exact_limit(byte_6F22FC, (int)&dword_6F235C);
    rf_ui_image_button_initialize(
      &dword_6F2318,
      (char *)&unk_63533F,
      "indicator_selected.tga",
      26,
      dword_661DF0 - 30,
      -1,
      (char *)&byte_63533E,
      0);
    unk_6F231C = dword_6F2014;
    rf_inline_dword_array10_append(dword_6F228C, (int)&dword_6F2318);
    rf_ui_slider_initialize_471620(
      (int)unk_6F2200,
      (int)dword_6F2014,
      "slider_bar_vert.tga",
      "slider_bar_vert_on.tga",
      dword_661DEC + dword_661DF4 + 2,
      dword_661DF0 + 18,
      16,
      185,
      0.0,
      1.0);
    unk_6F2220 = rf_save_list_a_scroll_from_slider;
    unk_6F2224 = rf_save_list_a_scroll_from_slider;
    rf_inline_dword_array10_append(dword_6F228C, (int)unk_6F2200);
    rf_inline_dword_array6_append_exact_limit(byte_6F22FC, (int)unk_6F2200);
    rf_ui_image_button_initialize(
      &dword_6F22B8,
      "cyclebutton_u.tga",
      "cyclebutton_u_on.tga",
      dword_661DEC + dword_661DF4 + 2,
      dword_661DF0 - 2,
      -1,
      (char *)&byte_635345,
      0);
    unk_6F22BC = dword_6F2014;
    unk_6F22D8 = rf_save_list_a_scroll_up_one;
    rf_inline_dword_array10_append(dword_6F228C, (int)&dword_6F22B8);
    rf_inline_dword_array6_append_exact_limit(byte_6F22FC, (int)&dword_6F22B8);
    rf_ui_image_button_initialize(
      &dword_6F21B8,
      "cyclebutton_d.tga",
      "cyclebutton_d_on.tga",
      dword_661DEC + dword_661DF4 + 2,
      dword_661DF0 + 203,
      -1,
      (char *)&byte_635346,
      0);
    unk_6F21BC = dword_6F2014;
    unk_6F21D8 = rf_save_list_a_scroll_down_one;
    rf_inline_dword_array10_append(dword_6F228C, (int)&dword_6F21B8);
    rf_inline_dword_array6_append_exact_limit(byte_6F22FC, (int)&dword_6F21B8);
    rf_ui_text_widget_initialize(
      dword_6F2040,
      (int)&dword_6F235C,
      dword_661DD4 + 1,
      -25,
      dword_661DE0 - 2,
      20,
      unk_88E3A4,
      unk_6F29AC);
    rf_inline_dword_array10_append(dword_6F228C, (int)dword_6F2040);
    rf_ui_text_widget_initialize(
      dword_6F2080,
      (int)&dword_6F235C,
      dword_661DD8 + 1,
      -25,
      dword_661DE4 - 2,
      20,
      unk_88E2C4,
      unk_6F29AC);
    rf_inline_dword_array10_append(dword_6F228C, (int)dword_6F2080);
    rf_ui_text_widget_initialize(
      dword_6F20C0,
      (int)&dword_6F235C,
      dword_661DDC + 1,
      -25,
      dword_661DE8 - 2,
      20,
      unk_88E3A8,
      unk_6F29AC);
    rf_inline_dword_array10_append(dword_6F228C, (int)dword_6F20C0);
    rf_ui_image_button_initialize(
      &dword_6F2248,
      (char *)&unk_635347,
      "lit_button_selected.tga",
      28,
      296,
      38,
      unk_88E2CC,
      unk_6F29AC);
    unk_6F224C = dword_6F2014;
    unk_6F2268 = rf_save_list_a_load_selected;
    rf_inline_dword_array10_append(dword_6F228C, (int)&dword_6F2248);
    rf_inline_dword_array6_append_exact_limit(byte_6F22FC, (int)&dword_6F2248);
    rf_ui_image_button_initialize(
      &dword_6F1FD0,
      (char *)&unk_63534B,
      "lit_button_selected.tga",
      28,
      330,
      48,
      unk_88E088,
      unk_6F29AC);
    unk_6F1FD4 = dword_6F2014;
    unk_6F1FF0 = rf_frontend_panel_pop_adapter_454880;
    rf_inline_dword_array10_append(dword_6F228C, (int)&dword_6F1FD0);
    return rf_inline_dword_array6_append_exact_limit(byte_6F22FC, (int)&dword_6F1FD0);
  }
  return result;
}

