// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004589C0 rf_ui_draw_scrolling_mars_background
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Snapshot physical width/height first. Only handle661E68==-1 selects fallback pause-overlay(physicalDisplay1,scaleFLOAT1); no source-X update in
// fallback. Otherwise set whiteRGBA255; compute FLOAT32 sourceX6F29BC=oldX+FLOATspeed661E78(15)*frameDelta. Signed width661E74-640 wraps32 before FILD. Strict ORDERED sourceX>that
// bound resets0; equality,negative values and unordered NaN survive. This is overshoot discard, not modulo and not lower clamping. Convert sourceX via605F00 truncation;
// dispatch12args(bitmap,0,0,physicalW,physicalH,sourceX,0,640,480,0,0,LIVE187CD34). Ignores bitmap dimension/width/scale validity, no resource load or viewport reset here; forwards
// dispatch/fallback EAX.
int rf_ui_draw_scrolling_mars_background()
{
  int physical_screen_width; // [esp+8h] [ebp-8h]
  int physical_screen_height; // [esp+Ch] [ebp-4h]

  physical_screen_width = rf_renderer_get_physical_screen_width();
  physical_screen_height = rf_renderer_get_physical_screen_height();
  if ( rf_ui_mars_background_bitmap == -1 )
    return rf_pause_overlay_backing_render(1, 1.0);
  rf_render_color_set_rgba8(255, 255, 255, 255);
  rf_ui_mars_background_source_x = rf_ui_mars_scroll_speed * rf_frame_delta_seconds + rf_ui_mars_background_source_x;
  if ( rf_ui_mars_background_source_x > (double)(rf_ui_mars_background_width - 640) )
    rf_ui_mars_background_source_x = 0.0;
  return rf_bitmap_blit_subrectangle_backend_dispatch(
           rf_ui_mars_background_bitmap,
           0,
           0,
           physical_screen_width,
           physical_screen_height,
           (int)rf_ui_mars_background_source_x,
           0,
           640,
           480,
           0,
           0,
           unk_187CD34);
}

