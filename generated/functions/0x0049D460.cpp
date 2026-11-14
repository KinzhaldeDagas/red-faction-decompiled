// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049D460 rf_multiplayer_time_left_render
// UNREALRED VERIFIED [multiplayer-hud] Formats Time Left as hours:minutes:seconds, advances green alpha by frame_delta*500 to 192, and right-aligns it 161 pixels from the viewport edge and 16 from the bottom.
int rf_multiplayer_time_left_render()
{
  int result; // eax
  int viewport_width; // eax
  int v2; // [esp-10h] [ebp-11Ch]
  int v3; // [esp-4h] [ebp-110h]
  char Buffer[256]; // [esp+4h] [ebp-108h] BYREF
  int v5; // [esp+108h] [ebp-4h]

  result = rf_multiplayer_time_left_visible;
  if ( rf_multiplayer_time_left_visible
    && rf_multiplayer_time_left_seconds >= 0
    && rf_multiplayer_time_left_minutes >= 0
    && rf_multiplayer_time_left_hours >= 0 )
  {
    v5 = 0;
    if ( byte_66291A == 1 )
    {
      rf_multiplayer_time_left_alpha = rf_frame_delta_seconds * 500.0 + rf_multiplayer_time_left_alpha;
      if ( rf_multiplayer_time_left_alpha > 192.0 )
      {
        rf_multiplayer_time_left_alpha = 192.0;
        byte_66291A = 0;
      }
    }
    sprintf(
      Buffer,
      "Time Left: %2.2d:%2.2d:%2.2d",
      rf_multiplayer_time_left_hours,
      rf_multiplayer_time_left_minutes,
      rf_multiplayer_time_left_seconds);
    rf_render_color_set_rgba8(0, 255, 0, (int)rf_multiplayer_time_left_alpha);
    v3 = dword_182ABBC;
    v2 = rf_renderer_get_viewport_height() - 16;
    viewport_width = rf_renderer_get_viewport_width();
    return rf_font_draw_text_aligned(1, viewport_width - 161, v2, (unsigned __int8 *)Buffer, -1, v3);
  }
  return result;
}

