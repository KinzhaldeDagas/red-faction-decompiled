// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004602E0 rf_multiplayer_menu_animate_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Reset viewport full screen,draw Mars. Integrate titleX6F485C += titleSpeed6F4860*frameDelta,round binary32;ORDERED strict below661E64 or above6F29C4
// clamps endpoint and zeroes speed;equal endpoints retain speed,NaN survives. Truncate titleX into titlebar+12 (6F4878),draw titlebar/label. Integrate profileX6F4848
// similarly:ordered strict below shared lower-bound clamps/stops;ordered >=6F29C8 (INCLUDING equality) commits currentPane=pending,pending=-1,sets speed0 ifcurrent==-1 else shared
// open speed,and clamps profileX upper. NaN does not commit/clamp. CurrentPane EXACT0 draws profile460E00(truncated profileX),which is logical X (shared old symbol names do not imply
// Y). Then integrate buttonX6F4854:ordered strict >openX or <closedX clamps/stops;equal bounds retain speed,NaN survives. Lay out exactly4 contiguous68-byte buttons;only BYTE9
// nonzero gets X=truncated buttonX and successive Y from first_enabled_row_y/row_step_y;draw each admitted button. Finish side-bars/overlays. No delta clamp,input gate,overshoot
// carry into next profile phase or render-color restore. EAX final delegate residue.
int rf_multiplayer_menu_animate_and_draw()
{
  int v1; // [esp+4h] [ebp-Ch]
  int v2; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  rf_renderer_reset_viewport_full_screen();
  rf_ui_draw_scrolling_mars_background();
  unk_6F485C = unk_6F4860 * rf_frame_delta_seconds + unk_6F485C;
  if ( unk_6F485C >= (double)dword_661E64 )
  {
    if ( unk_6F485C > (double)unk_6F29C4 )
    {
      unk_6F4860 = 0.0;
      unk_6F485C = (float)unk_6F29C4;
    }
  }
  else
  {
    unk_6F4860 = 0.0;
    unk_6F485C = (float)dword_661E64;
  }
  unk_6F4878 = (int)unk_6F485C;
  rf_ui_panel_render_bitmap(dword_6F486C);
  rf_ui_label_render((int)dword_6F4A10);
  unk_6F4848 = unk_6F4864 * rf_frame_delta_seconds + unk_6F4848;
  if ( unk_6F4848 >= (double)rf_main_menu_title_x_lower_bound )
  {
    if ( unk_6F4848 >= (double)unk_6F29C8 )
    {
      dword_661F8C = dword_661F90;
      dword_661F90 = -1;
      if ( dword_661F8C == -1 )
        unk_6F4864 = 0.0;
      else
        unk_6F4864 = rf_ui_open_transition_speed;
      unk_6F4848 = (float)unk_6F29C8;
    }
  }
  else
  {
    unk_6F4864 = 0.0;
    unk_6F4848 = (float)rf_main_menu_title_x_lower_bound;
  }
  if ( !dword_661F8C )
    rf_multiplayer_profile_draw_panel_and_portrait((int)unk_6F4848);
  unk_6F4854 = unk_6F4858 * rf_frame_delta_seconds + unk_6F4854;
  if ( unk_6F4854 <= (double)rf_main_menu_open_x )
  {
    if ( unk_6F4854 < (double)rf_main_menu_closed_x )
    {
      unk_6F4858 = 0.0;
      unk_6F4854 = (float)rf_main_menu_closed_x;
    }
  }
  else
  {
    unk_6F4858 = 0.0;
    unk_6F4854 = (float)rf_main_menu_open_x;
  }
  v2 = (int)unk_6F4854;
  v1 = rf_main_menu_first_enabled_row_y;
  for ( i = 0; i < 4; ++i )
  {
    if ( unk_6F48A1[68 * i] )
    {
      unk_6F48A4[17 * i] = v2;
      unk_6F48A8[17 * i] = v1;
      rf_ui_image_button_draw((int)&unk_6F4898 + 68 * i);
      v1 += rf_main_menu_row_step_y;
    }
  }
  return rf_ui_draw_side_bars_and_overlays();
}

