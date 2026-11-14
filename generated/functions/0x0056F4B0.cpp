// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056F4B0 rf_console_draw_renderer_overlay_and_slide
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. If animation byte==1,step=trunc(frameDeltaSeconds*1000);visible byte==1 adds step until y>=192 then clamps192/clears animation,otherwise subtracts until y<=-11 then clamps-11/clears animation. If not animating and visible==0 returns0;otherwise forcesy192. Draws background rectangle width570F60,height y+11. Calls58DC50 on prompt with width-20 and5 into five-entry span arrays;copies spans into200B local without own count clamp and draws10px rows with prompt color180A5A1/defaultfontID-1/renderMode182ABBC. Then scroll marker if needed and up to500 nonempty ring strings backward,using their unaligned packed colorDWORDs,until y<0.300ms timer toggles cursor;when enabled draws underscore at measured final prompt
// width+3/current baseline. Uses scaled frame delta,so animation speed follows time divisor. AL is incidental renderer/timer result;no GDI path or bracket-color parser here.
unsigned __int8 rf_console_draw_renderer_overlay_and_slide()
{
  unsigned __int8 result; // al
  int physical_screen_width; // eax
  int v2; // eax
  int v3; // [esp-8h] [ebp-130h]
  int v4; // [esp-4h] [ebp-12Ch]
  int v5; // [esp+18h] [ebp-110h]
  int v6; // [esp+1Ch] [ebp-10Ch] BYREF
  int v7; // [esp+20h] [ebp-108h]
  int v8; // [esp+24h] [ebp-104h]
  size_t Count[5]; // [esp+28h] [ebp-100h] BYREF
  int v10; // [esp+3Ch] [ebp-ECh] BYREF
  int line_offsets[5]; // [esp+40h] [ebp-E8h] BYREF
  int i; // [esp+54h] [ebp-D4h]
  char Destination[200]; // [esp+58h] [ebp-D0h] BYREF
  int v14; // [esp+124h] [ebp-4h]

  if ( unk_180A485 == 1 )
  {
    v5 = (int)(rf_frame_delta_seconds * 1000.0);
    if ( byte_180A486[0] == 1 )
    {
      dword_180A498 += v5;
      if ( dword_180A498 >= 192 )
      {
        dword_180A498 = 192;
        unk_180A485 = 0;
      }
    }
    else
    {
      dword_180A498 -= v5;
      if ( dword_180A498 <= -11 )
      {
        dword_180A498 = -11;
        unk_180A485 = 0;
      }
    }
  }
  else
  {
    result = byte_180A486[0];
    if ( !byte_180A486[0] )
      return result;
    dword_180A498 = 192;
  }
  rf_render_color_set_packed_rgba8(byte_180A5AC);
  v4 = dword_182ABB8;
  v3 = dword_180A498 + 11;
  physical_screen_width = rf_renderer_get_physical_screen_width();
  rf_renderer_fill_rectangle_clipped(0, 0, physical_screen_width, v3, v4);
  v2 = rf_renderer_get_physical_screen_width();
  v8 = rf_text_wrap_into_offset_length_arrays((int *)Count, line_offsets, (const char *)&unk_180A4A0, v2 - 20, 5, 0, -1);
  v10 = 0;
  v6 = 0;
  for ( i = 0; i < v8; ++i )
  {
    strncpy(Destination, (const char *)&unk_180A4A0 + line_offsets[i], Count[i]);
    Destination[Count[i]] = 0;
    rf_console_draw_colored_text_overlay(4, dword_180A498 - 10 * (v8 - (i + 1)), (int)Destination, (int)&unk_180A5A1);
    rf_font_measure_text_extent(&v10, &v6, (unsigned __int8 *)Destination, -1, -1);
  }
  v14 = dword_180A498 - 10 * (i + 1);
  if ( dword_1809ABC < 0 )
  {
    v7 = dword_1809920 - 1;
    if ( dword_1809920 - 1 < 0 )
      v7 = 499;
  }
  else
  {
    v7 = dword_1809ABC;
    rf_console_draw_colored_text_overlay(4, v14, unk_88E28C, (int)&unk_180A49C);
    v14 -= 10;
  }
  for ( i = 0; i < 500; ++i )
  {
    if ( &unk_180A5B0[261 * v7 + 1 + strlen(&unk_180A5B0[261 * v7])] != &unk_180A5B0[261 * v7 + 1] )
      rf_console_draw_colored_text_overlay(4, v14, (int)&unk_180A5B0[261 * v7], (int)unk_180A6B1 + 261 * v7);
    v14 -= 10;
    if ( v14 < 0 )
      break;
    if ( --v7 < 0 )
      v7 = 499;
  }
  result = rf_clock_deadline_has_elapsed_half_period(&unk_180A5A8);
  if ( result == 1 )
  {
    rf_clock_deadline_set_wrapped_offset(&unk_180A5A8, 300);
    result = byte_180930D[0];
    byte_180930D[0] = byte_180930D[0] != 1;
  }
  if ( byte_180930D[0] == 1 )
    return rf_font_draw_text_screen(v10 + 3, dword_180A498, "_", -1, dword_182ABBC);
  return result;
}

