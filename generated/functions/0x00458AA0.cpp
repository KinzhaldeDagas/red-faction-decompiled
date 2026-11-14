// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458AA0 rf_ui_draw_side_bars_and_overlays
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Snapshot physical width,height; set whiteRGBA255. Query left bitmap661E6C dimensions into signed locals, ignore query status; truncate signed
// width*FLOATscaleX to physical left width. Blit left at(0,0,scaledWidth,physicalHeight),source(0,0,bitmapWidth,bitmapHeight),raw trailing0,0,LIVE187CD34. Reuse locals for
// right661E70 query, again unchecked; rightWidth=trunc(width*scaleX),rightX=trunc(wrapped(640-width)*scaleX), not physicalWidth-scaledWidth. Blit right full physical height with
// original source dimensions. No invalid-handle/minimum/dimension guard or own viewport reset. Nonzero BYTE6F29C0 then draws frame timing/history at
// wrapped(physicalW-120,physicalH-10). Independently reread BYTE6F29C1: nonzero calls458770 coordinate overlay LAST, whose green color remains; timing draw may also alter shared
// render state. Returns last executed draw/helper EAX, not Boolean.
int rf_ui_draw_side_bars_and_overlays()
{
  int result; // eax
  int v1; // [esp+4h] [ebp-18h] BYREF
  int physical_screen_width; // [esp+8h] [ebp-14h]
  int physical_screen_height; // [esp+Ch] [ebp-10h]
  int v4; // [esp+10h] [ebp-Ch] BYREF
  int v5; // [esp+14h] [ebp-8h]
  int v6; // [esp+18h] [ebp-4h]

  physical_screen_width = rf_renderer_get_physical_screen_width();
  physical_screen_height = rf_renderer_get_physical_screen_height();
  rf_render_color_set_rgba8(255, 255, 255, 255);
  rf_bitmap_get_resolved_dimensions(rf_ui_left_bar_bitmap, &v1, &v4);
  v6 = (int)((double)v1 * rf_ui_scale_x);
  rf_bitmap_blit_subrectangle_backend_dispatch(
    rf_ui_left_bar_bitmap,
    0,
    0,
    v6,
    physical_screen_height,
    0,
    0,
    v1,
    v4,
    0,
    0,
    unk_187CD34);
  rf_bitmap_get_resolved_dimensions(rf_ui_right_bar_bitmap, &v1, &v4);
  v6 = (int)((double)v1 * rf_ui_scale_x);
  v5 = (int)((double)(640 - v1) * rf_ui_scale_x);
  result = rf_bitmap_blit_subrectangle_backend_dispatch(
             rf_ui_right_bar_bitmap,
             v5,
             0,
             v6,
             physical_screen_height,
             0,
             0,
             v1,
             v4,
             0,
             0,
             unk_187CD34);
  if ( unk_6F29C0 )
    result = rf_debug_draw_frame_timing_text_and_history(physical_screen_width - 120, physical_screen_height - 10);
  if ( unk_6F29C1 )
    return rf_ui_draw_pointer_coordinate_overlay();
  return result;
}

