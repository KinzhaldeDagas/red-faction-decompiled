// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458860 rf_ui_initialize_presentation
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Snapshot physical width then height; x87 FILD signed32, divide DOUBLE literals640.0/480.0, FSTP FLOAT32 scale661E34/661E38. EVERY invocation
// loads five font handles with spacing-1: rfpc-large.vf ->6F29A4 pausefont; rfpc-medium.vf separately ->6F29A8 and6F29AC;rfpc-small.vf ->6F29B0; adaptive6F29B4 uses medium for signed
// physicalWidth<1280 else large. Calls font-height/current-font selector on adaptive handle, stores height6F299C. No prior font release/once gate/validation. Each bitmap
// independently loaded ONLY if its current handle==-1, with raw args(name,-1,0):mars_background.tga->661E68,bar_left.tga->661E6C,bar_right.tga->661E70. Mars load additionally warms
// returned handle and queries dimensions, stores width661E74 and discards local height, even when load failed. Bars not warmed here. Does not reset scroll6F29BC or release stale
// resources. Path-dependent final EAX from last actual helper; no uniform status, rollback or load-error guard.
int rf_ui_initialize_presentation()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-Ch] BYREF
  int physical_screen_width; // [esp+4h] [ebp-8h]
  int physical_screen_height; // [esp+8h] [ebp-4h]

  physical_screen_width = rf_renderer_get_physical_screen_width();
  physical_screen_height = rf_renderer_get_physical_screen_height();
  rf_ui_scale_x = (double)physical_screen_width / 640.0;
  rf_ui_scale_y = (double)physical_screen_height / 480.0;
  rf_pause_font = rf_font_load_with_spacing_override("rfpc-large.vf", -1);
  unk_6F29A8 = rf_font_load_with_spacing_override("rfpc-medium.vf", -1);
  unk_6F29AC = rf_font_load_with_spacing_override("rfpc-medium.vf", -1);
  unk_6F29B0 = rf_font_load_with_spacing_override("rfpc-small.vf", -1);
  if ( physical_screen_width >= 1280 )
    dword_6F29B4 = rf_font_load_with_spacing_override("rfpc-large.vf", -1);
  else
    dword_6F29B4 = rf_font_load_with_spacing_override("rfpc-medium.vf", -1);
  result = rf_font_get_height_select_current(dword_6F29B4);
  dword_6F299C = result;
  if ( rf_ui_mars_background_bitmap == -1 )
  {
    rf_ui_mars_background_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                     "mars_background.tga",
                                     (void *)0xFFFFFFFF,
                                     0);
    rf_renderer_bind_texture_for_level_warmup(rf_ui_mars_background_bitmap);
    result = rf_bitmap_get_resolved_dimensions(rf_ui_mars_background_bitmap, &rf_ui_mars_background_width, &v1);
  }
  if ( rf_ui_left_bar_bitmap == -1 )
  {
    result = rf_bitmap_load_with_optional_mipmap_generation("bar_left.tga", (void *)0xFFFFFFFF, 0);
    rf_ui_left_bar_bitmap = result;
  }
  if ( rf_ui_right_bar_bitmap == -1 )
  {
    result = rf_bitmap_load_with_optional_mipmap_generation("bar_right.tga", (void *)0xFFFFFFFF, 0);
    rf_ui_right_bar_bitmap = result;
  }
  return result;
}

