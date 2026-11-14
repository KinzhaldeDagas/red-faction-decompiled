// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00466960 rf_host_menu_animate_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg. Reset viewport/draw Mars. Integrate titleX6F5E44 with speed6F5E48*delta,roundfloat;ordered strict<661E64/>6F29C4 clamps/stops,equality retains
// speed,NaN bypasses;truncatedX to titlebar+12,draw title/label. Integrate paneX6F5E2C:ordered strict<shared lower bound clamps/stops;ordered>=6F29C8 INCLUDING equality commits
// currentPane6F5E30=pending6F5E3C,pending=-1;current-1 stops else speed=shared open speed;clamp upper. NaN bypasses commit/clamp. Current0 ->setup draw(truncated paneX),1 ->rules
// draw;other values neither. Integrate buttonX6F5E38;ordered strict>openX/<closedX clamps/stops,equality retains speed,NaN bypasses. Write same truncatedX to exactly4
// contiguous68-byte buttons;iterate actual draw-list6F5E80 count,virtual0 ECXthis/NO stack args. Finish overlays. No input/active gate,delta clamp,persistence or rollback;shared
// symbols named vertical are reused for logical X.
int rf_host_menu_animate_and_draw()
{
  _DWORD *v0; // eax
  int i; // [esp+Ch] [ebp-4h]

  rf_renderer_reset_viewport_full_screen();
  rf_ui_draw_scrolling_mars_background();
  unk_6F5E44 = unk_6F5E48 * rf_frame_delta_seconds + unk_6F5E44;
  if ( unk_6F5E44 >= (double)dword_661E64 )
  {
    if ( unk_6F5E44 > (double)unk_6F29C4 )
    {
      unk_6F5E48 = 0.0;
      unk_6F5E44 = (float)unk_6F29C4;
    }
  }
  else
  {
    unk_6F5E48 = 0.0;
    unk_6F5E44 = (float)dword_661E64;
  }
  unk_6F5E60 = (int)unk_6F5E44;
  rf_ui_panel_render_bitmap(dword_6F5E54);
  rf_ui_label_render((int)&unk_6F5EA8);
  unk_6F5E2C = unk_6F5E4C * rf_frame_delta_seconds + unk_6F5E2C;
  if ( unk_6F5E2C >= (double)rf_main_menu_title_x_lower_bound )
  {
    if ( unk_6F5E2C >= (double)unk_6F29C8 )
    {
      unk_6F5E30 = unk_6F5E3C;
      unk_6F5E3C = -1;
      if ( unk_6F5E30 == -1 )
        unk_6F5E4C = 0.0;
      else
        unk_6F5E4C = rf_ui_open_transition_speed;
      unk_6F5E2C = (float)unk_6F29C8;
    }
  }
  else
  {
    unk_6F5E4C = 0.0;
    unk_6F5E2C = (float)rf_main_menu_title_x_lower_bound;
  }
  if ( unk_6F5E30 )
  {
    if ( unk_6F5E30 == 1 )
      rf_multiplayer_rules_draw_panel((int)unk_6F5E2C);
  }
  else
  {
    rf_multiplayer_setup_draw_panel_and_level_rows((int)unk_6F5E2C);
  }
  unk_6F5E38 = unk_6F5E40 * rf_frame_delta_seconds + unk_6F5E38;
  if ( unk_6F5E38 <= (double)rf_main_menu_open_x )
  {
    if ( unk_6F5E38 < (double)rf_main_menu_closed_x )
    {
      unk_6F5E40 = 0.0;
      unk_6F5E38 = (float)rf_main_menu_closed_x;
    }
  }
  else
  {
    unk_6F5E40 = 0.0;
    unk_6F5E38 = (float)rf_main_menu_open_x;
  }
  unk_6F5EF4 = (int)unk_6F5E38;
  unk_6F5F38 = (int)unk_6F5E38;
  unk_6F5F7C = (int)unk_6F5E38;
  unk_6F5FC0 = (int)unk_6F5E38;
  for ( i = 0; i < rf_receiver_get_first_dword(unk_6F5E80); ++i )
  {
    v0 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5E80, i);
    (**(void (__thiscall ***)(_DWORD, _DWORD))*v0)(*v0, *v0);
  }
  return rf_ui_draw_side_bars_and_overlays();
}

