// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046DA30 rf_persona_history_panel_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Message-history panel entry. Every call resets DWORDs6F8980/6F8978 to137 and arms repeat deadline6F8A04 for200ms. On first build (BYTE6F89B4==0), sets latch BEFORE loading
// message_log.vbm, obtains bitmap/viewport dimensions, stores binary32 scale=viewportWidth/640.0 in6F8990 and uses it for BOTH axes. Center6F89AC/B0 is
// trunc(viewportDimension-bitmapDimension*scale) divided by2 with signed truncation. Clip origin6F8970/7C adds trunc(scale*30/41); width6F8994=trunc(scale*313),
// height6F8974=trunc(scale*296). Loads rfpc-medium.vf/large.vf with spacing-1. Builds focus list6F8C08 with scroll meta6F8AE0 and Close6F89C0; draw list6F8B90 holds
// Up/Down/slider/Close. Meta press/drag are46DD80/46DDF0, child callbacks Up46DEE0/Down46DF40/slider46DFC0. Up=(466,79), Down=(466,361), slider=(467,99,18,260), range[0,1];
// Close=(241,392), hotkey46, callback46E0E0. Every entry resets slider0/viewoffset6F899C=0 and computes range6F898C=remaining-height minus clip-height, with no positive-range clamp.
// Incoming ECX is not read; existing stored type retained. No resource-failure guard or list rebuild/reset after the latch.
int __thiscall rf_persona_history_panel_initialize(void *this)
{
  int result; // eax

  unk_6F8980 = 137;
  unk_6F8978 = 137;
  rf_clock_deadline_set_wrapped_offset(&dword_6F8A04, 200);
  if ( !unk_6F89B4 )
  {
    unk_6F89B4 = 1;
    dword_6F89A0 = rf_bitmap_load_with_optional_mipmap_generation("message_log.vbm", (void *)0xFFFFFFFF, 0);
    rf_bitmap_get_resolved_dimensions(dword_6F89A0, &dword_6F89A4, &dword_6F89A8);
    dword_6F8984 = rf_renderer_get_viewport_width();
    dword_6F8988 = rf_renderer_get_viewport_height();
    unk_6F8990 = (double)dword_6F8984 / 640.0;
    unk_6F89AC = (int)((double)dword_6F8984 - (double)dword_6F89A4 * unk_6F8990) / 2;
    unk_6F89B0 = (int)((double)dword_6F8988 - (double)dword_6F89A8 * unk_6F8990) / 2;
    unk_6F8970 = unk_6F89AC + (int)(unk_6F8990 * 30.0);
    unk_6F897C = unk_6F89B0 + (int)(unk_6F8990 * 41.0);
    unk_6F8994 = (int)(unk_6F8990 * 313.0);
    unk_6F8974 = (int)(unk_6F8990 * 296.0);
    unk_757BB0 = rf_font_load_with_spacing_override("rfpc-medium.vf", -1);
    unk_757664 = rf_font_load_with_spacing_override("rfpc-large.vf", -1);
    unk_6F8AE4 = 0;
    unk_6F8B00 = rf_persona_history_scroll_group_press;
    unk_6F8B04 = rf_persona_history_scroll_group_drag;
    rf_inline_dword_array28_append(unk_6F8C08, (int)&unk_6F8AE0);
    rf_ui_image_button_initialize(
      &dword_6F8A98,
      "cyclebutton_u.tga",
      "cyclebutton_u_on.tga",
      466,
      79,
      -1,
      (char *)&byte_637D9F,
      unk_6F29AC);
    unk_6F8A9C = 0;
    unk_6F8AB8 = rf_persona_history_scroll_up;
    rf_inline_dword_array28_append(unk_6F8B90, (int)&dword_6F8A98);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F8AE0, &dword_6F8A98);
    rf_ui_image_button_initialize(
      &dword_6F8A50,
      "cyclebutton_d.tga",
      "cyclebutton_d_on.tga",
      466,
      361,
      -1,
      (char *)&byte_637DAE,
      unk_6F29AC);
    unk_6F8A54 = 0;
    unk_6F8A70 = rf_persona_history_scroll_down;
    rf_inline_dword_array28_append(unk_6F8B90, (int)&dword_6F8A50);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F8AE0, &dword_6F8A50);
    rf_ui_slider_initialize_471620(
      (int)unk_6F8A08,
      0,
      "slider_bar_vert.tga",
      "slider_bar_vert_on.tga",
      467,
      99,
      18,
      260,
      0.0,
      1.0);
    unk_6F8A28 = rf_persona_history_scroll_slider_pointer;
    unk_6F8A2C = rf_persona_history_scroll_slider_pointer;
    rf_inline_dword_array28_append(unk_6F8B90, (int)unk_6F8A08);
    rf_ui_meta_control_add_child_and_expand_bounds(&unk_6F8AE0, unk_6F8A08);
    rf_ui_image_button_initialize(
      &dword_6F89C0,
      (char *)&unk_637DAF,
      "popup_button_select.tga",
      241,
      392,
      46,
      unk_88E268,
      unk_6F29AC);
    unk_6F89C4 = 0;
    unk_6F89E0 = rf_persona_history_request_close;
    rf_inline_dword_array28_append(unk_6F8B90, (int)&dword_6F89C0);
    rf_inline_dword_array28_append(unk_6F8C08, (int)&dword_6F89C0);
  }
  rf_ui_slider_set_value_clamped(unk_6F8A08, 0.0);
  unk_6F899C = 0;
  result = rf_persona_history_remaining_layout_height() - unk_6F8974;
  unk_6F898C = result;
  return result;
}

