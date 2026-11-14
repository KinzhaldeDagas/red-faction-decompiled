// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049D7C0 rf_multiplayer_notification_feed_render
// UNREALRED VERIFIED [lan-killfeed-20261028] Death producer0x429820 selects style4 for local suicide/distinct local victim/distinct local killer and observer riot-stick deaths, selecting whole-row RGBA255/255/255. Ordinary observer, remote suicide and unresolved-killer messages select style5 and therefore default RGBA52/255/57. Fade alpha is shared with the panel.
char rf_multiplayer_notification_feed_render()
{
  int v0; // eax
  unsigned __int8 *v1; // eax
  unsigned __int8 *v2; // eax
  unsigned __int8 *v3; // eax
  unsigned __int8 *v4; // eax
  int v6; // [esp-4h] [ebp-44h]
  int v7; // [esp-4h] [ebp-44h]
  int v8; // [esp-4h] [ebp-44h]
  int v9; // [esp+Ch] [ebp-34h] BYREF
  int v10; // [esp+10h] [ebp-30h]
  int v11; // [esp+14h] [ebp-2Ch]
  int v12; // [esp+18h] [ebp-28h] BYREF
  float v13; // [esp+1Ch] [ebp-24h]
  int v14; // [esp+20h] [ebp-20h]
  int i; // [esp+24h] [ebp-1Ch]
  int viewport_width; // [esp+28h] [ebp-18h]
  int v17; // [esp+2Ch] [ebp-14h]
  int v18; // [esp+30h] [ebp-10h]
  unsigned __int8 v19; // [esp+37h] [ebp-9h]
  int v20; // [esp+38h] [ebp-8h]
  int viewport_height; // [esp+3Ch] [ebp-4h]

  if ( rf_replicator_is_armed(&rf_multiplayer_notification_hold_timer)
    || (LOBYTE(v0) = rf_replicator_is_armed(&rf_multiplayer_notification_fade_timer), (_BYTE)v0) )
  {
    viewport_width = rf_renderer_get_viewport_width();
    viewport_height = rf_renderer_get_viewport_height();
    v17 = 165;
    v18 = 97;
    v10 = viewport_width - 317;
    v11 = 102;
    v13 = 1.0;
    if ( rf_replicator_has_elapsed(&rf_multiplayer_notification_hold_timer)
      && !rf_replicator_is_armed(&rf_multiplayer_notification_fade_timer) )
    {
      rf_replicator_reset(&rf_multiplayer_notification_hold_timer);
      rf_replicator_arm_milliseconds(&rf_multiplayer_notification_fade_timer, 750);
    }
    if ( rf_replicator_is_armed(&rf_multiplayer_notification_fade_timer) )
    {
      if ( rf_replicator_has_elapsed(&rf_multiplayer_notification_fade_timer) )
      {
        LOBYTE(v0) = (unsigned __int8)rf_replicator_reset(&rf_multiplayer_notification_fade_timer);
        return v0;
      }
      v13 = (double)rf_replicator_signed_remaining_milliseconds(&rf_multiplayer_notification_fade_timer) / 750.0;
    }
    v19 = byte_757658[0];
    rf_render_color_set_rgba8(255, 255, 255, (int)((double)(byte_757658[0] != 0 ? 255 : 77) * v13));
    rf_renderer_fill_rectangle_clipped(157, 10, 2, 106, dword_182ABB8);
    rf_renderer_fill_rectangle_clipped(viewport_width - 158, 10, 2, 106, dword_182ABB8);
    rf_renderer_fill_rectangle_clipped(159, 10, v10, 2, dword_182ABB8);
    rf_renderer_fill_rectangle_clipped(159, 114, v10, 2, dword_182ABB8);
    rf_render_color_set_rgba8(0, 0, 0, (int)((double)(v19 != 0 ? 255 : 128) * v13));
    rf_renderer_fill_rectangle_clipped(159, 12, v10, 102, dword_182ABB8);
    rf_multiplayer_notification_rendered_row_count = 0;
    v0 = (int)(v13 * 255.0);
    v20 = v0;
    for ( i = 0; i < 8; ++i )
    {
      if ( rf_string_equals_case_insensitive(
             (int)&rf_multiplayer_notification_suffix_rows + 20 * i,
             (char *)&byte_63A3E6) )
      {
        LOBYTE(v0) = rf_string_equals_case_insensitive(
                       (int)&rf_multiplayer_notification_prefix_rows[20 * i],
                       (char *)&byte_63A3E7);
        if ( (_BYTE)v0 )
          break;
      }
      ++rf_multiplayer_notification_rendered_row_count;
      v14 = v17;
      v1 = (unsigned __int8 *)rf_string_object_c_str_or_empty(&rf_multiplayer_notification_prefix_rows[20 * i]);
      rf_font_measure_text_extent(&v12, &v9, v1, -1, -1);
      if ( rf_multiplayer_notification_style_rows[5 * i] )
      {
        switch ( rf_multiplayer_notification_style_rows[5 * i] )
        {
          case 1:
            v14 += v12;
            rf_render_color_set_rgba8(117, 117, 254, v20);
            v7 = dword_182ABBC;
            v3 = (unsigned __int8 *)rf_string_object_c_str_or_empty(&rf_multiplayer_notification_prefix_rows[20 * i]);
            rf_font_draw_text_screen(v17, v18, v3, -1, v7);
            rf_render_color_set_rgba8(255, 255, 255, v20);
            break;
          case 2:
            rf_render_color_set_rgba8(227, 48, 47, v20);
            break;
          case 3:
            rf_render_color_set_rgba8(117, 117, 254, v20);
            break;
          case 4:
            rf_render_color_set_rgba8(255, 255, 255, v20);
            break;
          default:
            rf_render_color_set_rgba8(52, 255, 57, v20);
            break;
        }
      }
      else
      {
        v14 += v12;
        rf_render_color_set_rgba8(227, 48, 47, v20);
        v6 = dword_182ABBC;
        v2 = (unsigned __int8 *)rf_string_object_c_str_or_empty(&rf_multiplayer_notification_prefix_rows[20 * i]);
        rf_font_draw_text_screen(v17, v18, v2, -1, v6);
        rf_render_color_set_rgba8(255, 255, 255, v20);
      }
      v8 = dword_182ABBC;
      v4 = (unsigned __int8 *)rf_string_object_c_str_or_empty((char *)&rf_multiplayer_notification_suffix_rows + 20 * i);
      LOBYTE(v0) = rf_font_draw_text_screen(v14, v18, v4, -1, v8);
      v18 -= v9;
    }
  }
  return v0;
}

