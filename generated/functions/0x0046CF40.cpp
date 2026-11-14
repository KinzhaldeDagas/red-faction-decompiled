// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046CF40 rf_audio_build_panel_and_load_gains
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Noarg;NO own build guard/list reset. Construct audio_panel.tga root6F8514. Refresh localized labels each call:Sound Effects Volume88DEB8,Music
// Volume88DEBC,Messages Volume88DEC0. For channel0/1/2 build groups6F85D0/6F8468/6F8818 with BOTH press+drag callbacks46CD90/46CE20/46CEB0;sliders6F8788/6F8540/6F8588 press
// callbacks46CDF0/46CE80/46CF10. Authored ranges0.0..1.0;load raw global channel gain through unchecked getter46D9D0,then slider clamp;does NOT copy clamped UI value back to gain at
// initialization. Add labels/sliders/indicator controls to inline11 draw6F88C4 and groups to inline11 focus6F88F4,plus meta child links;ignore append returns. Getter argument slot
// reused for FLOAT slider value (native no separate caller cleanup). Parent options build latch normally limits invocation;direct repeats reconstruct/append. No focus reset,player
// dereference,channel setters,ramp/sample playback,save or rollback in own body;return final meta-child delegate residue.
int rf_audio_build_panel_and_load_gains()
{
  float unchecked; // [esp+4h] [ebp-10h]
  float v2; // [esp+4h] [ebp-10h]
  float v3; // [esp+4h] [ebp-10h]

  rf_ui_panel_initialize_bitmap(dword_6F8514, "audio_panel.tga", dword_6F29C8, rf_main_menu_title_y);
  unk_6F8458 = dword_88DEB8;
  dword_6F845C = (const char *)unk_88DEBC;
  dword_6F8460 = (const char *)unk_88DEC0;
  rf_ui_label_initialize_measured_text(dword_6F86C8, (int)dword_6F8514, 285, 79, dword_88DEB8, unk_6F29AC);
  rf_inline_dword_array11_append(dword_6F88C4, (int)dword_6F86C8);
  rf_ui_label_initialize_measured_text(dword_6F8708, (int)dword_6F8514, 285, 112, dword_6F845C, unk_6F29AC);
  rf_inline_dword_array11_append(dword_6F88C4, (int)dword_6F8708);
  rf_ui_label_initialize_measured_text(dword_6F8748, (int)dword_6F8514, 285, 145, dword_6F8460, unk_6F29AC);
  rf_inline_dword_array11_append(dword_6F88C4, (int)dword_6F8748);
  unk_6F85D4 = dword_6F8514;
  unk_6F85F0 = rf_audio_effects_group_dispatch;
  unk_6F85F4 = rf_audio_effects_group_dispatch;
  rf_inline_dword_array11_append(dword_6F88F4, (int)&unk_6F85D0);
  rf_ui_slider_initialize_471620(
    (int)unk_6F8788,
    (int)dword_6F8514,
    "slider_bar.tga",
    "slider_bar_on.tga",
    141,
    74,
    118,
    20,
    0.0,
    1.0);
  unk_6F87A8 = rf_audio_effects_gain_from_pointer;
  unchecked = rf_sound_channel_group_gain_get_unchecked(0);
  rf_ui_slider_set_value_clamped(unk_6F8788, unchecked);
  rf_inline_dword_array11_append(dword_6F88C4, (int)unk_6F8788);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F85D0, unk_6F8788);
  rf_ui_image_button_initialize(
    &dword_6F87D0,
    (char *)&unk_637CAA,
    "indicator_selected.tga",
    110,
    70,
    -1,
    (char *)&byte_637CA9,
    0);
  unk_6F87D4 = dword_6F8514;
  rf_inline_dword_array11_append(dword_6F88C4, (int)&dword_6F87D0);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F85D0, &dword_6F87D0);
  unk_6F846C = dword_6F8514;
  unk_6F8488 = rf_audio_music_group_dispatch;
  unk_6F848C = rf_audio_music_group_dispatch;
  rf_inline_dword_array11_append(dword_6F88F4, (int)&unk_6F8468);
  rf_ui_slider_initialize_471620(
    (int)unk_6F8540,
    (int)dword_6F8514,
    "slider_bar.tga",
    "slider_bar_on.tga",
    141,
    108,
    118,
    21,
    0.0,
    1.0);
  unk_6F8560 = rf_audio_music_gain_from_pointer;
  v2 = rf_sound_channel_group_gain_get_unchecked(1);
  rf_ui_slider_set_value_clamped(unk_6F8540, v2);
  rf_inline_dword_array11_append(dword_6F88C4, (int)unk_6F8540);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F8468, unk_6F8540);
  rf_ui_image_button_initialize(
    &dword_6F8928,
    (char *)&unk_637CB9,
    "indicator_selected.tga",
    110,
    104,
    -1,
    (char *)&byte_637CAB,
    0);
  unk_6F892C = dword_6F8514;
  rf_inline_dword_array11_append(dword_6F88C4, (int)&dword_6F8928);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F8468, &dword_6F8928);
  unk_6F881C = dword_6F8514;
  unk_6F8838 = rf_audio_messages_group_dispatch;
  unk_6F883C = rf_audio_messages_group_dispatch;
  rf_inline_dword_array11_append(dword_6F88F4, (int)&unk_6F8818);
  rf_ui_slider_initialize_471620(
    (int)unk_6F8588,
    (int)dword_6F8514,
    "slider_bar.tga",
    "slider_bar_on.tga",
    141,
    142,
    118,
    20,
    0.0,
    1.0);
  unk_6F85A8 = rf_audio_messages_gain_from_pointer;
  v3 = rf_sound_channel_group_gain_get_unchecked(2);
  rf_ui_slider_set_value_clamped(unk_6F8588, v3);
  rf_inline_dword_array11_append(dword_6F88C4, (int)unk_6F8588);
  rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F8818, unk_6F8588);
  rf_ui_image_button_initialize(
    &dword_6F8680,
    (char *)&unk_637CBB,
    "indicator_selected.tga",
    110,
    138,
    -1,
    (char *)&byte_637CBA,
    0);
  unk_6F8684 = dword_6F8514;
  rf_inline_dword_array11_append(dword_6F88C4, (int)&dword_6F8680);
  return rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F8818, &dword_6F8680);
}

