// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00463CC0 rf_browser_enter_and_build_controls
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. Cache localized headings once via init bits6F5E24. EVERY entry:focus3,mainX6F5194=closedX6F29C8/speed6F52BC=shared open
// speed,titleX6F51B4=6F29C4/speed6F52B8=661E60,input661F95=1;arm doubleClick5554/UIhold57DC/join537C offset0,trackerActive0,clear pendingIP,set startup flag. Only build latch6F52CB0
// formats user-directory+svrlist.adr/favlist.adr using unbounded sprintf. Allocate favorite storage512*100 once ifNULL. Read ListLAN default0,normalize into6F52DB;LAN clears
// live/visible/displayselection/rawselection then refresh;online loads caches and rebuilds. Set active6F52CA=1. Already-built exits HERE,so checkbox is not resynchronized from
// reloaded registry on reentry. First build sets latch BEFORE further work;registry notice default0 displays once/writes1;simultaneous ping default16 clamped1..32. Measure
// glyphA6;visibleRows=floor(binary32(listHeight*scaleY/rowHeight)). If online,start discovery BEFORE constructing controls. Build panel/title/status,Cancel461D40,LAN461D70,filter
// previous/next/group,three mode choices+All selected3,list462370,slider/up/down,six column sort callbacks0..5 and arrow. Join->existing join
// routine,GetServers->463050,Add->464CD0,Back->464AC0,RefreshSelected->464C50,RefreshAll->464AD0. Draw/focus lists are fixed inline32 arrays via43CBB0;append failures ignored. Does
// not reset build latch/favoriteCount/scroll/cancel globally or roll back partial construction. Position channels are X despite shared symbol names.
int rf_browser_enter_and_build_controls()
{
  int result; // eax
  float value; // [esp+34h] [ebp-58h]
  BYTE v2[4]; // [esp+78h] [ebp-14h] BYREF
  BYTE v3[4]; // [esp+7Ch] [ebp-10h] BYREF
  BYTE Data[4]; // [esp+80h] [ebp-Ch] BYREF
  int i; // [esp+84h] [ebp-8h] BYREF
  char Buffer; // [esp+88h] [ebp-4h] BYREF
  _BYTE v7[3]; // [esp+89h] [ebp-3h] BYREF

  if ( (dword_6F5E24 & 1) == 0 )
  {
    dword_6F5E24 |= 1u;
    unk_6F5E1C = unk_88E150;
    unk_6F5E20 = unk_88E154;
  }
  if ( (dword_6F5E24 & 2) == 0 )
  {
    dword_6F5E24 |= 2u;
    unk_6F5E04 = (char *)unk_88DFB4;
    unk_6F5E08 = (char *)unk_88E17C;
    unk_6F5E0C = (char *)unk_88DFBC;
    unk_6F5E10 = (char *)unk_88E158;
    unk_6F5E14 = (char *)unk_88E15C;
    unk_6F5E18 = (char *)unk_88E180;
  }
  unk_6F519C = 3;
  unk_6F5194 = (float)unk_6F29C8;
  unk_6F52BC = rf_ui_open_transition_speed;
  unk_6F51B4 = (float)unk_6F29C4;
  unk_6F52B8 = flt_661E60;
  byte_661F95 = 1;
  rf_clock_deadline_set_wrapped_offset(&dword_6F5554, 0);
  unk_6F51A2 = 0;
  rf_clock_deadline_set_wrapped_offset(&dword_6F57DC, 0);
  rf_clock_deadline_set_wrapped_offset(&dword_6F537C, 0);
  rf_join_pending_ipv4_clear();
  rf_set_startup_session_flag();
  if ( !unk_6F52CB )
  {
    sprintf(unk_6F51B8, "%s%s", &unk_189CD90, "svrlist.adr");
    sprintf(unk_6F5090, "%s%s", &unk_189CD90, "favlist.adr");
  }
  if ( !unk_6F52E8 )
    unk_6F52E8 = operator new(0xC800u);
  rf_registry_read_dword_or_default(nullptr, "ListLAN", Data, 0);
  unk_6F52DB = *(_DWORD *)Data != 0;
  if ( *(_DWORD *)Data != 0 )
  {
    dword_6F51A8 = 0;
    MEMORY[0x6F5088] = 0;
    unk_6F52E0 = 0;
    dword_661F9C = -1;
    rf_browser_begin_refresh_existing_rows();
  }
  else
  {
    rf_browser_load_cache_and_favorites();
    rf_browser_rebuild_filtered_sorted_row_indices();
  }
  unk_6F52CA = 1;
  result = unk_6F52CB;
  if ( !unk_6F52CB )
  {
    unk_6F52CB = 1;
    rf_registry_read_dword_or_default(nullptr, off_661FE8, v3, 0);
    if ( !*(_DWORD *)v3 )
    {
      rf_ui_show_ok_modal(unk_88E250, unk_88E254, 0, 0);
      rf_registry_write_dword(nullptr, off_661FE8, 1);
    }
    rf_registry_read_dword_or_default(nullptr, off_661FEC, v2, 16);
    *(_DWORD *)&dword_661F98 = *(_DWORD *)v2;
    rf_integer_clamp_in_place(&dword_661F98, 1, 32);
    sprintf(&Buffer, "%c", -90);
    rf_font_measure_text_extent(&dword_6F51AC, &i, (unsigned __int8 *)&Buffer, &v7[strlen(&Buffer)] - v7, dword_6F29B4);
    value = (double)dword_661FDC * rf_ui_scale_y / (double)dword_6F299C;
    unk_6F508C = (int)rf_floor_float(value);
    if ( !unk_6F52DB )
      rf_browser_start_discovery();
    rf_ui_panel_initialize_bitmap(dword_6F547C, "server_list_panel.tga", unk_6F29C8, rf_main_menu_title_y);
    rf_ui_panel_initialize_bitmap(dword_6F53C4, "titlebar.tga", unk_6F29C4, unk_6F29B8);
    rf_ui_label_initialize_measured_text(dword_6F5CE8, (int)dword_6F53C4, 140, 12, unk_88E08C, rf_pause_font);
    rf_ui_text_widget_initialize(dword_6F5A20, (int)dword_6F547C, 32, 20, 415, 12, (char *)&byte_636857, unk_6F29AC);
    rf_ui_button_set_focus(dword_6F5A20);
    rf_ui_image_button_initialize(
      &dword_6F5770,
      (char *)&unk_63688E,
      "lit_button_small_selected.tga",
      430,
      14,
      46,
      unk_88D760,
      unk_6F29A8);
    unk_6F5774 = dword_6F547C;
    unk_6F5790 = rf_browser_cancel_discovery_and_queries;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F5770);
    rf_inline_dword_array32_append(unk_6F5C60, (int)&dword_6F5770);
    rf_ui_checkbox_initialize_471300(
      &unk_6F5D70,
      (int)&unk_636897,
      (int)"checkbox_selected.tga",
      "checkbox_checked.tga",
      31,
      52,
      38,
      (char *)&byte_63688F,
      0);
    unk_6F5D74 = dword_6F547C;
    unk_6F5D90 = rf_multiplayer_menu_toggle_lan;
    byte_6F5DB8[0] = unk_6F52DB != 0;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&unk_6F5D70);
    rf_inline_dword_array32_append(unk_6F5C60, (int)&unk_6F5D70);
    rf_ui_label_initialize_measured_text(dword_6F5A60, (int)&unk_6F5D70, 100, 7, dword_88E3B8, unk_6F29AC);
    rf_inline_dword_array32_append(unk_6F5B90, (int)dword_6F5A60);
    unk_6F54AC = dword_6F547C;
    unk_6F54C8 = rf_browser_filter_group_press_dispatch;
    rf_inline_dword_array32_append(unk_6F5C60, (int)&unk_6F54A8);
    rf_ui_cycle_list_set_geometry(unk_6F5828, (int)dword_6F547C, 313, 51, 107, 26);
    for ( i = 0; i < 3; ++i )
      rf_ui_cycle_list_append_text(unk_6F5828, *(_DWORD *)dword_6F3AE4[i], *(const char **)dword_6F3AE4[i], unk_6F29AC);
    rf_ui_cycle_list_append_text(unk_6F5828, unk_6F29AC, unk_88E164, unk_6F29AC);
    unk_6F5994 = unk_6F5990 - 1;
    rf_inline_dword_array32_append(unk_6F5B90, (int)unk_6F5828);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F54A8, unk_6F5828);
    rf_ui_image_button_initialize(
      &dword_6F5338,
      "cyclebutton_l.tga",
      (char *)&unk_6368CB,
      -18,
      0,
      -1,
      (char *)&byte_6368CA,
      0);
    unk_6F533C = unk_6F5828;
    unk_6F5358 = (int (__cdecl *)(_DWORD, _DWORD))rf_browser_mode_filter_previous;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F5338);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F54A8, &dword_6F5338);
    rf_ui_image_button_initialize(
      &dword_6F57E0,
      "cyclebutton_r.tga",
      (char *)&unk_63693D,
      unk_6F583C,
      0,
      -1,
      (char *)&byte_6368CF,
      0);
    unk_6F57E4 = unk_6F5828;
    unk_6F5800 = (int (__cdecl *)(_DWORD, _DWORD))rf_browser_mode_filter_next;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F57E0);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F54A8, &dword_6F57E0);
    rf_ui_image_button_initialize(
      &dword_6F5438,
      (char *)&unk_63693F,
      "indicator_selected.tga",
      273,
      52,
      -1,
      (char *)&byte_63693E,
      0);
    unk_6F543C = dword_6F547C;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F5438);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F54A8, &dword_6F5438);
    rf_ui_label_initialize_measured_text(dword_6F59E0, (int)&dword_6F57E0, unk_6F57F4 + 8, 8, unk_88DFA4, unk_6F29AC);
    rf_inline_dword_array32_append(unk_6F5B90, (int)dword_6F59E0);
    unk_6F57C0 = dword_661FD0;
    unk_6F57C4 = dword_661FD4;
    unk_6F57C8 = dword_661FD8;
    unk_6F57CC = dword_661FDC;
    unk_6F57B8 = dword_6F547C;
    unk_6F57D4 = rf_browser_list_press_or_join;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F57B4);
    rf_inline_dword_array32_append(unk_6F5C60, (int)&dword_6F57B4);
    rf_ui_image_button_initialize(
      &dword_6F5D28,
      (char *)&unk_636947,
      "indicator_selected.tga",
      -5,
      -31,
      -1,
      (char *)&byte_636946,
      0);
    unk_6F5D2C = &dword_6F57B4;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F5D28);
    rf_ui_slider_initialize_471620(
      (int)unk_6F53F0,
      (int)dword_6F547C,
      "slider_bar_vert.tga",
      "slider_bar_vert_on.tga",
      522,
      136,
      16,
      135,
      0.0,
      1.0);
    unk_6F5410 = rf_browser_scroll_from_slider;
    unk_6F5414 = rf_browser_scroll_from_slider;
    rf_inline_dword_array32_append(unk_6F5B90, (int)unk_6F53F0);
    rf_inline_dword_array32_append(unk_6F5C60, (int)unk_6F53F0);
    rf_ui_image_button_initialize(
      &dword_6F5B48,
      "cyclebutton_u.tga",
      "cyclebutton_u_on.tga",
      522,
      120,
      -1,
      (char *)&byte_6369BF,
      0);
    unk_6F5B4C = dword_6F547C;
    unk_6F5B68 = rf_browser_scroll_up;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F5B48);
    rf_inline_dword_array32_append(unk_6F5C60, (int)&dword_6F5B48);
    rf_ui_image_button_initialize(
      &dword_6F5AB8,
      "cyclebutton_d.tga",
      "cyclebutton_d_on.tga",
      522,
      271,
      -1,
      (char *)&byte_6369C6,
      0);
    unk_6F5ABC = dword_6F547C;
    unk_6F5AD8 = rf_browser_scroll_down;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F5AB8);
    rf_inline_dword_array32_append(unk_6F5C60, (int)&dword_6F5AB8);
    rf_ui_text_widget_initialize(
      dword_6F55F0,
      (int)&dword_6F57B4,
      dword_661FA0,
      dword_661FE4,
      dword_661FB8,
      30,
      unk_6F5E04,
      unk_6F29B0);
    unk_6F5610 = rf_browser_sort_by_favorites;
    rf_inline_dword_array32_append(unk_6F5C60, (int)dword_6F55F0);
    rf_ui_text_widget_initialize(
      dword_6F5630,
      (int)&dword_6F57B4,
      dword_661FA4,
      dword_661FE4,
      dword_661FBC,
      30,
      unk_6F5E08,
      unk_6F29B0);
    unk_6F5650 = rf_browser_sort_by_server_name;
    rf_inline_dword_array32_append(unk_6F5C60, (int)dword_6F5630);
    rf_ui_text_widget_initialize(
      dword_6F5670,
      (int)&dword_6F57B4,
      dword_661FA8,
      dword_661FE4,
      dword_661FC0,
      30,
      unk_6F5E0C,
      unk_6F29B0);
    unk_6F5690 = rf_browser_sort_by_ping;
    rf_inline_dword_array32_append(unk_6F5C60, (int)dword_6F5670);
    rf_ui_text_widget_initialize(
      dword_6F56B0,
      (int)&dword_6F57B4,
      dword_661FAC,
      dword_661FE4,
      dword_661FC4,
      30,
      unk_6F5E10,
      unk_6F29B0);
    unk_6F56D0 = rf_browser_sort_by_map_name;
    rf_inline_dword_array32_append(unk_6F5C60, (int)dword_6F56B0);
    rf_ui_text_widget_initialize(
      dword_6F56F0,
      (int)&dword_6F57B4,
      dword_661FB0,
      dword_661FE4,
      dword_661FC8,
      30,
      unk_6F5E14,
      unk_6F29B0);
    unk_6F5710 = rf_browser_sort_by_players;
    rf_inline_dword_array32_append(unk_6F5C60, (int)dword_6F56F0);
    rf_ui_text_widget_initialize(
      dword_6F5730,
      (int)&dword_6F57B4,
      dword_661FB4,
      dword_661FE4,
      dword_661FCC,
      30,
      unk_6F5E18,
      unk_6F29B0);
    unk_6F5750 = rf_browser_sort_by_game_type;
    rf_inline_dword_array32_append(unk_6F5C60, (int)dword_6F5730);
    rf_ui_image_button_initialize(
      &dword_6F5C18,
      "sort_arrow.tga",
      (char *)&unk_6369D7,
      0,
      dword_661FE4 + 15,
      -1,
      (char *)&byte_6369C7,
      0);
    unk_6F5C1C = &dword_6F57B4;
    rf_ui_image_button_initialize(
      &dword_6F55A8,
      (char *)&unk_6369EE,
      "lit_button_selected.tga",
      28,
      296,
      36,
      unk_88DFA8,
      unk_6F29A8);
    unk_6F55AC = dword_6F547C;
    unk_6F55C8 = rf_multiplayer_menu_join_selected_server;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F55A8);
    rf_inline_dword_array32_append(unk_6F5C60, (int)&dword_6F55A8);
    rf_ui_image_button_initialize(
      &dword_6F5998,
      (char *)&unk_6369EF,
      "lit_button_selected.tga",
      192,
      296,
      34,
      unk_88DFAC,
      unk_6F29A8);
    unk_6F599C = dword_6F547C;
    unk_6F59B8 = rf_browser_start_discovery;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F5998);
    rf_inline_dword_array32_append(unk_6F5C60, (int)&dword_6F5998);
    rf_ui_image_button_initialize(
      &dword_6F5DC0,
      (char *)&unk_636A35,
      "lit_button_selected.tga",
      356,
      296,
      30,
      unk_88DFB0,
      unk_6F29A8);
    unk_6F5DC4 = dword_6F547C;
    unk_6F5DE0 = rf_browser_prompt_manual_address;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F5DC0);
    rf_inline_dword_array32_append(unk_6F5C60, (int)&dword_6F5DC0);
    rf_ui_image_button_initialize(
      &dword_6F52F0,
      (char *)&unk_636A36,
      "lit_button_selected.tga",
      28,
      330,
      48,
      unk_88E088,
      unk_6F29A8);
    unk_6F52F4 = dword_6F547C;
    unk_6F5310 = rf_browser_request_back;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F52F0);
    rf_inline_dword_array32_append(unk_6F5C60, (int)&dword_6F52F0);
    rf_ui_image_button_initialize(
      &dword_6F5B00,
      (char *)&unk_636A37,
      "lit_button_selected.tga",
      192,
      330,
      18,
      unk_88DFC4,
      unk_6F29A8);
    unk_6F5B04 = dword_6F547C;
    unk_6F5B20 = rf_browser_queue_selected_server_query;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F5B00);
    rf_inline_dword_array32_append(unk_6F5C60, (int)&dword_6F5B00);
    rf_ui_image_button_initialize(
      &dword_6F5380,
      (char *)&unk_636A3E,
      "lit_button_selected.tga",
      356,
      330,
      19,
      unk_88DFC8,
      unk_6F29A8);
    unk_6F5384 = dword_6F547C;
    unk_6F53A0 = rf_browser_queue_all_server_queries;
    rf_inline_dword_array32_append(unk_6F5B90, (int)&dword_6F5380);
    return rf_inline_dword_array32_append(unk_6F5C60, (int)&dword_6F5380);
  }
  return result;
}

