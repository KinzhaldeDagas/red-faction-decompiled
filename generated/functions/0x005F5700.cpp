// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F5700 rf_ui_inputbox_draw
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Absolute position,innerW=width-2*margin1420,innerH=height-2*textYOffset1424. Hidden returns before draw. Resets clip;blocked chooses palette1404+24/bitmap1452,else palette+0/bitmap1448. If no bitmap draws sunken face thickness1 and removes extra2 from available textWidth=innerW-cursorWidth1432;else white bitmap. Copies text632 into260-byte stack array or fills strlen bytes with passwordBYTE1412 when flags628&1;NO hard bound. Measures with fontID-1(default),not stored font1400;if too wide repeatedly measures growing trailing suffix from last byte,then chooses suffix just below available width. No bound on reverse-suffix search;negative availableWidth skips loop and can select pointer beyond NUL. Sets text clip at absolute+margin/textYOffset,innerW/innerH. Justification0 top,2 bottom by default
// font height,other center using metric58c0e0(-1);clamps vertical offset>=0;shadow palette+16 iff alpha19,foreground+12,draws using stored font1400 despite default-font measurement. When enabled and globally focused,changes clip to margin/cursorYOffset1428;cursor anim1440 starts if needed and advances at frame delta at suffixWidth,0;else cursor bitmap1444 white,or solid lines width1432,height1436 using normal palette+20. No blink timer,child draw,event or final clip/color restore. Return incidental draw/predicate/loop result.
void __thiscall rf_ui_inputbox_draw(int this)
{
  int v1; // eax
  int v2; // esi
  float v3; // [esp+8h] [ebp-180h]
  int v4; // [esp+Ch] [ebp-17Ch]
  float v5; // [esp+Ch] [ebp-17Ch]
  int v6; // [esp+10h] [ebp-178h]
  int v7; // [esp+24h] [ebp-164h]
  unsigned __int8 v8; // [esp+2Bh] [ebp-15Dh]
  unsigned __int8 *v9; // [esp+30h] [ebp-158h]
  unsigned __int8 *v10; // [esp+34h] [ebp-154h]
  unsigned __int8 *v12; // [esp+4Ch] [ebp-13Ch]
  int v13; // [esp+50h] [ebp-138h]
  signed int v14; // [esp+54h] [ebp-134h]
  int v15; // [esp+58h] [ebp-130h]
  int v16; // [esp+5Ch] [ebp-12Ch]
  int v17; // [esp+60h] [ebp-128h] BYREF
  int v18; // [esp+64h] [ebp-124h] BYREF
  unsigned __int8 v19[260]; // [esp+68h] [ebp-120h] BYREF
  int i; // [esp+170h] [ebp-18h]
  int v21; // [esp+174h] [ebp-14h]
  int v22; // [esp+178h] [ebp-10h]
  unsigned __int8 *v23; // [esp+17Ch] [ebp-Ch]
  int v24; // [esp+180h] [ebp-8h]
  size_t Size; // [esp+184h] [ebp-4h]

  v21 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
  v13 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
  v16 = *(_DWORD *)(this + 20) - 2 * *(_DWORD *)(this + 1420);
  v22 = *(_DWORD *)(this + 24) - 2 * *(_DWORD *)(this + 1424);
  if ( !(*(unsigned __int8 (__thiscall **)(int))(*(_DWORD *)this + 16))(this) )
  {
    rf_renderer_reset_viewport_full_screen();
    if ( rf_ui_gadget_is_interaction_blocked((_DWORD *)this) )
    {
      v12 = (unsigned __int8 *)(*(_DWORD *)(this + 1404) + 24);
      v14 = *(_DWORD *)(this + 1452);
    }
    else
    {
      v12 = *(unsigned __int8 **)(this + 1404);
      v14 = *(_DWORD *)(this + 1448);
    }
    v24 = v16 - *(_DWORD *)(this + 1432);
    if ( v14 < 0 )
    {
      rf_ui_gadget_draw_sunken_face((int *)this, v12, 1);
      v24 -= 2;
    }
    else
    {
      rf_render_color_set_rgba8(255, 255, 255, 255);
      v6 = unk_187CD38;
      v4 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
      v1 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
      rf_bitmap_draw_unscaled_clipped(v14, v1, v4, v6);
    }
    Size = strlen((const char *)(this + 632));
    if ( (*(_DWORD *)(this + 628) & 1) != 0 )
    {
      if ( (int)Size > 0 )
        memset(v19, *(char *)(this + 1412), Size);
      v19[Size] = 0;
    }
    else
    {
      v10 = (unsigned __int8 *)(this + 632);
      v9 = v19;
      do
      {
        v8 = *v10;
        *v9++ = *v10++;
      }
      while ( v8 );
    }
    rf_font_measure_text_extent(&v18, &v17, v19, -1, -1);
    if ( v18 <= v24 )
    {
      v23 = v19;
    }
    else
    {
      v18 = 0;
      i = 1;
      while ( v18 <= v24 )
        rf_font_measure_text_extent(&v18, &v17, &v19[Size - i++], -1, -1);
      v23 = &v19[Size - i + 2];
      rf_font_measure_text_extent(&v18, &v17, v23, -1, -1);
    }
    rf_renderer_set_viewport_and_relative_clip(*(_DWORD *)(this + 1420) + v21, *(_DWORD *)(this + 1424) + v13, v16, v22);
    v7 = *(_DWORD *)(this + 1416);
    if ( v7 )
    {
      if ( v7 == 2 )
      {
        v15 = v22 - rf_font_get_height_select_current(-1);
        if ( v12[19] )
          --v15;
        if ( v15 < 0 )
          v15 = 0;
        if ( v12[19] )
        {
          rf_render_color_set_packed_rgba8(v12 + 16);
          rf_font_draw_text_screen(1, v15 + 1, v23, *(_DWORD *)(this + 1400), dword_182ABBC);
        }
      }
      else
      {
        v2 = v22 / 2;
        v15 = v2 - (rf_font_get_spacing_select_current(-1) + 1) / 2;
        if ( v15 < 0 )
          v15 = 0;
        if ( v12[19] )
        {
          rf_render_color_set_packed_rgba8(v12 + 16);
          rf_font_draw_text_screen(1, v15 + 1, v23, *(_DWORD *)(this + 1400), dword_182ABBC);
        }
      }
      rf_render_color_set_packed_rgba8(v12 + 12);
      rf_font_draw_text_screen(0, v15, v23, *(_DWORD *)(this + 1400), dword_182ABBC);
    }
    else
    {
      if ( v12[19] )
      {
        rf_render_color_set_packed_rgba8(v12 + 16);
        rf_font_draw_text_screen(1, 1, v23, *(_DWORD *)(this + 1400), dword_182ABBC);
      }
      rf_render_color_set_packed_rgba8(v12 + 12);
      rf_font_draw_text_screen(0, 0, v23, *(_DWORD *)(this + 1400), dword_182ABBC);
    }
    if ( !rf_ui_gadget_is_interaction_blocked((_DWORD *)this) && dword_1CF75D8 == (_DWORD *)this )
    {
      rf_renderer_set_viewport_and_relative_clip(
        *(_DWORD *)(this + 1420) + v21,
        *(_DWORD *)(this + 1428) + v13,
        v16,
        *(_DWORD *)(this + 24) - *(_DWORD *)(this + 1428));
      if ( *(_DWORD *)(this + 1440) )
      {
        if ( !rf_vani_player_is_playing(*(_DWORD **)(this + 1440)) )
          rf_vani_player_start(*(_DWORD *)(this + 1440), 1);
        rf_vani_player_set_screen_position(*(_DWORD **)(this + 1440), v18, 0);
        rf_vani_player_advance_and_draw(*(_DWORD *)(this + 1440), rf_frame_delta_seconds);
      }
      else if ( *(int *)(this + 1444) < 0 )
      {
        rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 1404) + 20));
        for ( i = 0; i < *(_DWORD *)(this + 1432); ++i )
        {
          v5 = (float)(*(_DWORD *)(this + 1436) - 1);
          v3 = (float)(i + v18);
          rf_renderer_draw_screen_line_clipped(v3, 0.0, v3, v5, dword_187CC5C);
        }
      }
      else
      {
        rf_render_color_set_rgba8(255, 255, 255, 255);
        rf_bitmap_draw_unscaled_clipped(*(_DWORD *)(this + 1444), v18, 0, unk_187CD38);
      }
    }
  }
}

