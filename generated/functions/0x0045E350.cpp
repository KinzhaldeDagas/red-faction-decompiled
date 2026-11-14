// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045E350 rf_multiplayer_rules_build_controls_once
// UNREALRED VERIFIED [lan-match-flow-20261028] Advanced-server panel initialization builds the seven minute choices at 0x661F20 [5,10,15,20,30,45,60] and selects index 4, hence 30 minutes. It builds thirteen frag choices at 0x661F3C [1,5,10,15,20,25,30,35,40,45,50,75,100] and selects index 6, hence 30 frags. These are native UI choices/defaults; no unlimited-zero choice is present in these lists.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Full native builder closure now checked. Any nonzero initBYTE6F3AF4 skips whole body;zero sets1 BEFORE constructing advanced_server_panel.tga parent6F3EC4 (no rollback).
// Build time chooser6F3AF8 at(150,20):7 original minutes661F20 [5,10,15,20,30,45,60],index4->30. Kill chooser6F4068 at(150,54):13 values661F3C
// [1,5,10,15,20,25,30,35,40,45,50,75,100],index6->30. Capture chooser6F44A8 at(150,218):7 values661F70 [1,3,5,10,15,20,25],index2->5. Numeric strings formatted with capacity4.
// Time/kill/capture group press callbacksEC90/ED50/EE10;previous/next callbacksECF0/ED20,EDB0/EDE0,EE70/EEA0. Five checkbox controls3E78/4388/4018/3F38/43D8
// bindEED0/EF30/EF90/EFF0/F050,original fallback labels Team damage,Fall damage,Weapons stay,Force respawn,Balance teams;runtime uses localization pointers. Populate fixed10
// focus-list6F4358 and fixed30 draw-list6F4298 plus meta child links,ignoring append results. Labels/indicator/arrow textures and parent links constructed natively. No gameplay-rule
// apply,registry load/persistence,mode-control state update,focus-index reset or atexit cleanup in body. Nominal return raw already-init byte or final append residue,not uniform
// initialized/success status. Original minute/frag finding retained.
int rf_multiplayer_rules_build_controls_once()
{
  int result; // eax
  int v1; // edx
  int v2; // edx
  char v3[4]; // [esp+20h] [ebp-10h] BYREF
  char v4[4]; // [esp+24h] [ebp-Ch] BYREF
  char v5[4]; // [esp+28h] [ebp-8h] BYREF
  int i; // [esp+2Ch] [ebp-4h]

  result = byte_6F3AF4[0];
  if ( !byte_6F3AF4[0] )
  {
    byte_6F3AF4[0] = 1;
    rf_ui_panel_initialize_bitmap(dword_6F3EC4, "advanced_server_panel.tga", 0, rf_main_menu_title_y);
    unk_6F3D84 = dword_6F3EC4;
    unk_6F3DA0 = rf_multiplayer_rules_time_limit_press_dispatch;
    rf_inline_dword_array10_append(unk_6F4358, (int)&unk_6F3D80);
    rf_ui_cycle_list_set_geometry(unk_6F3AF8, (int)dword_6F3EC4, 150, 20, 107, 12);
    for ( i = 0; i < 7; ++i )
    {
      rf_format_signed_decimal_cstring(v5, 4, dword_661F20[i]);
      rf_ui_cycle_list_append_text(unk_6F3AF8, v1, v5, unk_6F29AC);
    }
    unk_6F3C64 = 4;
    rf_inline_dword_array30_append(dword_6F4298, (int)unk_6F3AF8);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3D80, unk_6F3AF8);
    rf_ui_image_button_initialize(
      &dword_6F4658,
      "cyclebutton_l.tga",
      (char *)&unk_636497,
      -18,
      -6,
      -1,
      (char *)&byte_636496,
      0);
    unk_6F465C = unk_6F3AF8;
    unk_6F4678 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_rules_previous_time_choice;
    rf_inline_dword_array30_append(dword_6F4298, (int)&dword_6F4658);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3D80, &dword_6F4658);
    rf_ui_image_button_initialize(
      &dword_6F3C68,
      "cyclebutton_r.tga",
      (char *)&unk_6364AB,
      unk_6F3B0C,
      -6,
      -1,
      (char *)&byte_6364AA,
      0);
    unk_6F3C6C = unk_6F3AF8;
    unk_6F3C88 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_rules_next_time_choice;
    rf_inline_dword_array30_append(dword_6F4298, (int)&dword_6F3C68);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3D80, &dword_6F3C68);
    rf_ui_image_button_initialize(
      &dword_6F3CB0,
      (char *)&unk_6364BF,
      "indicator_selected.tga",
      -23,
      0,
      -1,
      (char *)&byte_6364BE,
      0);
    unk_6F3CB4 = &dword_6F4658;
    rf_inline_dword_array30_append(dword_6F4298, (int)&dword_6F3CB0);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F3D80, &dword_6F3CB0);
    rf_ui_label_initialize_measured_text(dword_6F4468, (int)dword_6F3EC4, 285, unk_6F3B08, unk_88E058, unk_6F29AC);
    rf_inline_dword_array30_append(dword_6F4298, (int)dword_6F4468);
    unk_6F479C = dword_6F3EC4;
    unk_6F47B8 = rf_multiplayer_rules_kill_limit_press_dispatch;
    rf_inline_dword_array10_append(unk_6F4358, (int)&unk_6F4798);
    rf_ui_cycle_list_set_geometry(unk_6F4068, (int)dword_6F3EC4, 150, 54, 107, 12);
    for ( i = 0; i < 13; ++i )
    {
      rf_format_signed_decimal_cstring(v4, 4, dword_661F3C[i]);
      rf_ui_cycle_list_append_text(unk_6F4068, v2, v4, unk_6F29AC);
    }
    unk_6F41D4 = 6;
    rf_inline_dword_array30_append(dword_6F4298, (int)unk_6F4068);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F4798, unk_6F4068);
    rf_ui_image_button_initialize(
      &dword_6F3E30,
      "cyclebutton_l.tga",
      (char *)&unk_6364E1,
      -18,
      -6,
      -1,
      (char *)&byte_6364D7,
      0);
    unk_6F3E34 = unk_6F4068;
    unk_6F3E50 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_rules_previous_kill_choice;
    rf_inline_dword_array30_append(dword_6F4298, (int)&dword_6F3E30);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F4798, &dword_6F3E30);
    rf_ui_image_button_initialize(
      &dword_6F3F88,
      "cyclebutton_r.tga",
      (char *)&unk_6364E3,
      unk_6F407C,
      -6,
      -1,
      (char *)&byte_6364E2,
      0);
    unk_6F3F8C = unk_6F4068;
    unk_6F3FA8 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_rules_next_kill_choice;
    rf_inline_dword_array30_append(dword_6F4298, (int)&dword_6F3F88);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F4798, &dword_6F3F88);
    rf_ui_image_button_initialize(
      &dword_6F46A0,
      (char *)&unk_6364F7,
      "indicator_selected.tga",
      -23,
      0,
      -1,
      (char *)&byte_6364F6,
      0);
    unk_6F46A4 = &dword_6F3E30;
    rf_inline_dword_array30_append(dword_6F4298, (int)&dword_6F46A0);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F4798, &dword_6F46A0);
    rf_ui_label_initialize_measured_text(dword_6F3D40, (int)dword_6F3EC4, 285, unk_6F4078, unk_88E05C, unk_6F29AC);
    rf_inline_dword_array30_append(dword_6F4298, (int)dword_6F3D40);
    rf_ui_checkbox_initialize_471300(
      &unk_6F3E78,
      (int)&unk_63650B,
      (int)"checkbox_selected.tga",
      "checkbox_checked.tga",
      113,
      78,
      20,
      (char *)&byte_63650A,
      0);
    unk_6F3E7C = dword_6F3EC4;
    unk_6F3E98 = rf_multiplayer_rules_toggle_team_damage;
    rf_inline_dword_array30_append(dword_6F4298, (int)&unk_6F3E78);
    rf_inline_dword_array10_append(unk_6F4358, (int)&unk_6F3E78);
    rf_ui_label_initialize_measured_text(dword_6F41D8, (int)dword_6F3EC4, 213, unk_6F3E88 + 7, unk_88DF80, unk_6F29AC);
    rf_inline_dword_array30_append(dword_6F4298, (int)dword_6F41D8);
    rf_ui_checkbox_initialize_471300(
      &unk_6F4388,
      (int)&unk_63652E,
      (int)"checkbox_selected.tga",
      "checkbox_checked.tga",
      113,
      103,
      20,
      (char *)&byte_636523,
      0);
    unk_6F438C = dword_6F3EC4;
    unk_6F43A8 = rf_multiplayer_rules_toggle_fall_damage;
    rf_inline_dword_array30_append(dword_6F4298, (int)&unk_6F4388);
    rf_inline_dword_array10_append(unk_6F4358, (int)&unk_6F4388);
    rf_ui_label_initialize_measured_text(dword_6F4318, (int)dword_6F3EC4, 213, unk_6F4398 + 7, unk_88DF7C, unk_6F29AC);
    rf_inline_dword_array30_append(dword_6F4298, (int)dword_6F4318);
    rf_ui_checkbox_initialize_471300(
      &unk_6F4018,
      (int)&unk_636545,
      (int)"checkbox_selected.tga",
      "checkbox_checked.tga",
      113,
      130,
      20,
      (char *)&byte_63652F,
      0);
    unk_6F401C = dword_6F3EC4;
    unk_6F4038 = rf_multiplayer_rules_toggle_weapons_stay;
    rf_inline_dword_array30_append(dword_6F4298, (int)&unk_6F4018);
    rf_inline_dword_array10_append(unk_6F4358, (int)&unk_6F4018);
    rf_ui_label_initialize_measured_text(dword_6F4428, (int)dword_6F3EC4, 213, unk_6F4028 + 7, unk_88E04C, unk_6F29AC);
    rf_inline_dword_array30_append(dword_6F4298, (int)dword_6F4428);
    rf_ui_checkbox_initialize_471300(
      &unk_6F3F38,
      (int)&unk_636547,
      (int)"checkbox_selected.tga",
      "checkbox_checked.tga",
      113,
      156,
      20,
      (char *)&byte_636546,
      0);
    unk_6F3F3C = dword_6F3EC4;
    unk_6F3F58 = rf_multiplayer_rules_toggle_force_respawn;
    rf_inline_dword_array30_append(dword_6F4298, (int)&unk_6F3F38);
    rf_inline_dword_array10_append(unk_6F4358, (int)&unk_6F3F38);
    rf_ui_label_initialize_measured_text(dword_6F4258, (int)dword_6F3EC4, 213, unk_6F3F48 + 7, unk_88E050, unk_6F29AC);
    rf_inline_dword_array30_append(dword_6F4298, (int)dword_6F4258);
    rf_ui_checkbox_initialize_471300(
      &unk_6F43D8,
      (int)&unk_63655F,
      (int)"checkbox_selected.tga",
      "checkbox_checked.tga",
      113,
      182,
      20,
      (char *)&byte_63655E,
      0);
    unk_6F43DC = dword_6F3EC4;
    unk_6F43F8 = rf_multiplayer_rules_toggle_balance_teams;
    rf_inline_dword_array30_append(dword_6F4298, (int)&unk_6F43D8);
    rf_inline_dword_array10_append(unk_6F4358, (int)&unk_6F43D8);
    rf_ui_label_initialize_measured_text(dword_6F4618, (int)dword_6F3EC4, 213, unk_6F43E8 + 7, unk_88E054, unk_6F29AC);
    rf_inline_dword_array30_append(dword_6F4298, (int)dword_6F4618);
    unk_6F46EC = dword_6F3EC4;
    unk_6F4708 = rf_multiplayer_rules_capture_limit_press_dispatch;
    rf_inline_dword_array10_append(unk_6F4358, (int)&unk_6F46E8);
    rf_ui_cycle_list_set_geometry(unk_6F44A8, (int)dword_6F3EC4, 150, 218, 107, 12);
    for ( i = 0; i < 7; ++i )
    {
      rf_format_signed_decimal_cstring(v3, 4, dword_661F70[i]);
      rf_ui_cycle_list_append_text(unk_6F44A8, (int)v3, v3, unk_6F29AC);
    }
    unk_6F4614 = 2;
    rf_inline_dword_array30_append(dword_6F4298, (int)unk_6F44A8);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F46E8, unk_6F44A8);
    rf_ui_image_button_initialize(
      &dword_6F3FD0,
      "cyclebutton_l.tga",
      (char *)&unk_636582,
      -18,
      -6,
      -1,
      (char *)&byte_636581,
      0);
    unk_6F3FD4 = unk_6F44A8;
    unk_6F3FF0 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_rules_previous_capture_choice;
    rf_inline_dword_array30_append(dword_6F4298, (int)&dword_6F3FD0);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F46E8, &dword_6F3FD0);
    rf_ui_image_button_initialize(
      &dword_6F3EF0,
      "cyclebutton_r.tga",
      (char *)&unk_63659A,
      unk_6F44BC,
      -6,
      -1,
      (char *)&byte_636583,
      0);
    unk_6F3EF4 = unk_6F44A8;
    unk_6F3F10 = (int (__cdecl *)(_DWORD, _DWORD))rf_multiplayer_rules_next_capture_choice;
    rf_inline_dword_array30_append(dword_6F4298, (int)&dword_6F3EF0);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F46E8, &dword_6F3EF0);
    rf_ui_image_button_initialize(
      &dword_6F3CF8,
      byte_6365BD,
      "indicator_selected.tga",
      -23,
      0,
      -1,
      (char *)&byte_63659B,
      0);
    unk_6F3CFC = &dword_6F3FD0;
    rf_inline_dword_array30_append(dword_6F4298, (int)&dword_6F3CF8);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F46E8, &dword_6F3CF8);
    rf_ui_label_initialize_measured_text(dword_6F4218, (int)dword_6F3EC4, 285, unk_6F44B8, unk_88E060, unk_6F29AC);
    return rf_inline_dword_array30_append(dword_6F4298, (int)dword_6F4218);
  }
  return result;
}

