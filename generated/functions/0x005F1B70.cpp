// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1B70 rf_ui_state_image_draw
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Arguments x,y,w,h,clipOffsetX,clipOffsetY. If clipOffsetX>=0,sets clip at(x+clipOffsetX,y+clipOffsetY,w,h) and draw coordinates=-clipOffsetX,-clipOffsetY;resets clip on every exit,without restoring prior clip. Mode1 draws bitmap+4 white and returns1;mode2 animation+8,mode3 bitmap then animation. For animation sets screen position;if not playing,start(player,1),walk +24 circular ring,call0x5F1B50 on each record with different player. That helper stops only mode2,not mode3. Advances/draws with rf_frame_delta_seconds. Modes0/other return0. No scaling to w/h,no player NULL guard,no ring termination guard. White render color not restored.
char __thiscall rf_ui_state_image_draw(int *this, int a2, int a3, int a4, int a5, int a6, int a7)
{
  int v8; // [esp+4h] [ebp-10h]
  int *j; // [esp+Ch] [ebp-8h]
  int *i; // [esp+10h] [ebp-4h]

  if ( a6 >= 0 )
  {
    rf_renderer_set_viewport_and_relative_clip(a6 + a2, a7 + a3, a4, a5);
    a2 = -a6;
    a3 = -a7;
  }
  v8 = *this;
  if ( *this == 1 )
  {
    rf_render_color_set_rgba8(255, 255, 255, 255);
    rf_bitmap_draw_unscaled_clipped(*(this + 1), a2, a3, unk_187CD38);
    if ( a6 >= 0 )
      rf_renderer_reset_viewport_full_screen();
    return 1;
  }
  else if ( v8 == 2 )
  {
    rf_vani_player_set_screen_position((_DWORD *)*(this + 2), a2, a3);
    if ( !rf_vani_player_is_playing((_DWORD *)*(this + 2)) )
    {
      rf_vani_player_start(*(this + 2), 1);
      for ( i = (int *)*(this + 6); i != this; i = (int *)i[6] )
      {
        if ( i[2] != *(this + 2) )
          rf_ui_state_image_stop_animation_only(i);
      }
    }
    rf_vani_player_advance_and_draw(*(this + 2), rf_frame_delta_seconds);
    if ( a6 >= 0 )
      rf_renderer_reset_viewport_full_screen();
    return 1;
  }
  else if ( v8 == 3 )
  {
    rf_render_color_set_rgba8(255, 255, 255, 255);
    rf_bitmap_draw_unscaled_clipped(*(this + 1), a2, a3, unk_187CD38);
    rf_vani_player_set_screen_position((_DWORD *)*(this + 2), a2, a3);
    if ( !rf_vani_player_is_playing((_DWORD *)*(this + 2)) )
    {
      rf_vani_player_start(*(this + 2), 1);
      for ( j = (int *)*(this + 6); j != this; j = (int *)j[6] )
      {
        if ( j[2] != *(this + 2) )
          rf_ui_state_image_stop_animation_only(j);
      }
    }
    rf_vani_player_advance_and_draw(*(this + 2), rf_frame_delta_seconds);
    if ( a6 >= 0 )
      rf_renderer_reset_viewport_full_screen();
    return 1;
  }
  else
  {
    if ( a6 >= 0 )
      rf_renderer_reset_viewport_full_screen();
    return 0;
  }
}

