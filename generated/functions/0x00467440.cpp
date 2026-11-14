// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467440 rf_options_menu_enter_and_build
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Native body consumes NO stack args,though panel14 initializer pushes ignored payload word. If buildBYTE6F602D0,construct5 contiguous68-byte buttons6F6110
// at0,0:Game key34,Video47,Audio30,Controls46,Back48;first4 button_more.tga,last button.tga,selected texture shared. Runtime labels localized;native fallback strings verified. Set
// pointer table6F6008[i]=6F6110+68*i. Call gameplay settings initializer,performance options builder,46CF40,468C90;build titlebar/Options label;set build latch AFTER construction.
// Small scoped receiver5734B0/5734C0 delegates verified passthrough/noop;SEH cleanup retained. EVERY
// entry:buttonXspeed6F601C=firstButtonWidth6F6124*open_x_scale;titleX6F6020=6F29C4/title speed6F6024=661E60;current/pending
// selectionDWORD661FF4/F8=-1,focus6F5FFC0,paneX6F5FF8=6F29C8,pane speed6F6028=0;set four pane-rootXDWORDs6F603C+44*i=closedX;mainInput6F602C1. Does not explicitly set main
// buttonX6F6004,attach callbacks in this body,play sound or persist options;separate frame/key routines own interaction.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Native animation467CE0 and readiness4676F0/467770 identify the actual main-button X position as FLOAT6F6004. Initializer467440 does not write it;it writes
// speed6F601C and title/pane coordinates instead. Corrected prior annotation's6F6018 address to6F6004;no database layout/type/code change. Controls builder468C90 has no local
// one-time guard;this parent build latch is its normal admission.
void rf_options_menu_enter_and_build()
{
  int j; // [esp+1Ch] [ebp-18h]
  int i; // [esp+20h] [ebp-14h]
  char v2; // [esp+27h] [ebp-Dh] BYREF
  int v3; // [esp+30h] [ebp-4h]

  if ( !unk_6F602D )
  {
    rf_receiver_passthrough_5734B0(&v2);
    v3 = 0;
    rf_ui_image_button_initialize(
      (int *)&unk_6F6110,
      "button_more.tga",
      "button_selected.tga",
      0,
      0,
      34,
      unk_88E078,
      unk_6F29A8);
    rf_ui_image_button_initialize(
      dword_6F6154,
      "button_more.tga",
      "button_selected.tga",
      0,
      0,
      47,
      unk_88E07C,
      unk_6F29A8);
    rf_ui_image_button_initialize(
      dword_6F6198,
      "button_more.tga",
      "button_selected.tga",
      0,
      0,
      30,
      unk_88E080,
      unk_6F29A8);
    rf_ui_image_button_initialize(
      dword_6F61DC,
      "button_more.tga",
      "button_selected.tga",
      0,
      0,
      46,
      unk_88E084,
      unk_6F29A8);
    rf_ui_image_button_initialize(dword_6F6220, "button.tga", "button_selected.tga", 0, 0, 48, unk_88E048, unk_6F29A8);
    for ( i = 0; i < 5; ++i )
      unk_6F6008[i] = (int)&unk_6F6110 + 68 * i;
    rf_gameplay_settings_menu_initialize();
    rf_ui_performance_options_build();
    rf_audio_build_panel_and_load_gains();
    rf_controls_build_panel_and_load_player();
    rf_ui_panel_initialize_bitmap(dword_6F60E0, "titlebar.tga", unk_6F29C4, unk_6F29B8);
    rf_ui_label_initialize_measured_text(dword_6F6268, (int)dword_6F60E0, 140, 12, unk_88D600, rf_pause_font);
    unk_6F602D = 1;
    v3 = -1;
    rf_receiver_ignored_noop_5734C0();
  }
  unk_6F601C = (double)unk_6F6124 * rf_main_menu_open_x_speed_scale;
  unk_6F6020 = (float)unk_6F29C4;
  unk_6F6024 = flt_661E60;
  dword_661FF4 = -1;
  dword_661FF8 = -1;
  unk_6F5FFC = 0;
  unk_6F5FF8 = (float)dword_6F29C8;
  unk_6F6028 = 0.0;
  for ( j = 0; j < 4; ++j )
    unk_6F603C[11 * j] = dword_6F29C8;
  unk_6F602C = 1;
}

