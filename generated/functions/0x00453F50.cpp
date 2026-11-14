// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453F50 rf_extras_menu_initialize_once_and_open
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. ANY nonzero initializedBYTE6F1DC0 skips construction; otherwise store1 BEFORE first
// asset work. Initialize titlebar6F1E54("titlebar.tga",rawX6F29C4,rawY6F29B8), label6F1F40(parentADDRESS6F1E54,x140,y12,textDWORD88E390,fontDWORD6F29A4). Every XOR/JZ language branch
// forces localized-pointer path; embedded English Extras/CREDITS/SUMMONER-newline-TRAILER/GLASSHOUSE/BACK alternatives are unreachable, not NULL fallbacks. Initialize four buttons in
// order6F1E80/6F1E10/6F1EC8/6F1DC8, each(normal"button.tga",selected"button_selected.tga",X signed6F29A0,font6F29A8). Y/hotkey/label/callback: first
// integer661E48(PE58),46,88E394,453CE0; secondFRESH661E48+first button height6F1E98,31,88DA4C,453D00; thirdFRESHsecondY6F1E20+height6F1E28,34,88E39C,453D30;
// fourthFRESHthirdY6F1ED8+height6F1EE0,48,88E048,453DB0. Row additions wrap32. After each button install callback at its+32 and append its ADDRESS to BOTH inline lists6F1F0C
// then6F1F24 via454570, ignoring failures; no prior list clear or count assertion. Initialized latch remains1 after any partial/resource failure, no retry/rollback. EVERY call resets
// selection6F1DAC=0, buttonFloatX6F1DB0=F32(signed closed6F29A0), calls453BD0 open motion/sound, THEN activeBYTE6F1DA8=1, forwarding open-helperEAX. Does NOT reset
// titlebarFloatX6F1DB8 or validate assets/localized pointers/list storage.
int rf_extras_menu_initialize_once_and_open()
{
  int result; // eax

  if ( !unk_6F1DC0 )
  {
    unk_6F1DC0 = 1;
    rf_ui_panel_initialize_bitmap(dword_6F1E54, "titlebar.tga", unk_6F29C4, unk_6F29B8);
    rf_ui_label_initialize_measured_text(dword_6F1F40, (int)dword_6F1E54, 140, 12, unk_88E390, rf_pause_font);
    rf_ui_image_button_initialize(
      dword_6F1E80,
      "button.tga",
      "button_selected.tga",
      rf_main_menu_closed_x,
      rf_main_menu_first_enabled_row_y,
      46,
      unk_88E394,
      unk_6F29A8);
    unk_6F1EA0 = rf_extras_menu_request_credits_panel23;
    rf_inline_dword_array5_append(dword_6F1F0C, (int)dword_6F1E80);
    rf_inline_dword_array5_append(dword_6F1F24, (int)dword_6F1E80);
    rf_ui_image_button_initialize(
      dword_6F1E10,
      "button.tga",
      "button_selected.tga",
      rf_main_menu_closed_x,
      unk_6F1E98 + rf_main_menu_first_enabled_row_y,
      31,
      unk_88DA4C,
      unk_6F29A8);
    unk_6F1E30 = rf_extras_menu_play_summoner_trailer;
    rf_inline_dword_array5_append(dword_6F1F0C, (int)dword_6F1E10);
    rf_inline_dword_array5_append(dword_6F1F24, (int)dword_6F1E10);
    rf_ui_image_button_initialize(
      dword_6F1EC8,
      "button.tga",
      "button_selected.tga",
      rf_main_menu_closed_x,
      unk_6F1E28 + unk_6F1E20,
      34,
      unk_88E39C,
      unk_6F29A8);
    unk_6F1EE8 = rf_extras_menu_request_glass_house_level;
    rf_inline_dword_array5_append(dword_6F1F0C, (int)dword_6F1EC8);
    rf_inline_dword_array5_append(dword_6F1F24, (int)dword_6F1EC8);
    rf_ui_image_button_initialize(
      dword_6F1DC8,
      "button.tga",
      "button_selected.tga",
      rf_main_menu_closed_x,
      unk_6F1EE0 + unk_6F1ED8,
      48,
      unk_88E048,
      unk_6F29A8);
    unk_6F1DE8 = rf_extras_menu_request_stack_pop;
    rf_inline_dword_array5_append(dword_6F1F0C, (int)dword_6F1DC8);
    rf_inline_dword_array5_append(dword_6F1F24, (int)dword_6F1DC8);
  }
  dword_6F1DAC = 0;
  unk_6F1DB0 = (float)rf_main_menu_closed_x;
  result = rf_extras_menu_begin_open();
  unk_6F1DA8 = 1;
  return result;
}

