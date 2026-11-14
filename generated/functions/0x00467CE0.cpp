// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467CE0 rf_options_menu_animate_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Reset viewport/draw Mars. TitleX6F6020 integrates speed6F6024*delta,roundfloat;ordered strict<661E64/>6F29C4 clamps/stops,equality retains speed,NaN
// bypasses;truncate into titlebar+12/draw title+label. PaneX6F5FF8 integrates speed6F6028;ordered strict<shared lower clamps/stops;ordered>=6F29C8 INCLUDING equality commits
// current661FF4=pending661FF8,pending=-1;current-1 speed0 else shared open speed,clamp upper. NaN bypasses. Draw current0 Game46C5B0,1 Video46B2A0,2 Audio46D710,3 Controls469650 with
// truncated paneX;others none. ButtonX is6F6004:integrate6F601C;ordered strict>openX/<closedX clamps/stops,equality retains speed,NaN bypasses. Exactly5 contiguous68-byte
// buttons:only BYTE9 nonzero gets truncatedX and successive Y beginning shared first-row/increment rowstep,then image draw. No delta/input/active gate,save or render-color restore.
// Shared constants named vertical are reused for X. Original PE draw-switch table verified.
int rf_options_menu_animate_and_draw()
{
  int v1; // [esp+4h] [ebp-Ch]
  int v2; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  rf_renderer_reset_viewport_full_screen();
  rf_ui_draw_scrolling_mars_background();
  unk_6F6020 = unk_6F6024 * rf_frame_delta_seconds + unk_6F6020;
  if ( unk_6F6020 >= (double)dword_661E64 )
  {
    if ( unk_6F6020 > (double)unk_6F29C4 )
    {
      unk_6F6024 = 0.0;
      unk_6F6020 = (float)unk_6F29C4;
    }
  }
  else
  {
    unk_6F6024 = 0.0;
    unk_6F6020 = (float)dword_661E64;
  }
  unk_6F60EC = (int)unk_6F6020;
  rf_ui_panel_render_bitmap(dword_6F60E0);
  rf_ui_label_render((int)dword_6F6268);
  unk_6F5FF8 = unk_6F6028 * rf_frame_delta_seconds + unk_6F5FF8;
  if ( unk_6F5FF8 >= (double)rf_main_menu_title_x_lower_bound )
  {
    if ( unk_6F5FF8 >= (double)dword_6F29C8 )
    {
      dword_661FF4 = dword_661FF8;
      dword_661FF8 = -1;
      if ( dword_661FF4 == -1 )
        unk_6F6028 = 0.0;
      else
        unk_6F6028 = rf_ui_open_transition_speed;
      unk_6F5FF8 = (float)dword_6F29C8;
    }
  }
  else
  {
    unk_6F6028 = 0.0;
    unk_6F5FF8 = (float)rf_main_menu_title_x_lower_bound;
  }
  switch ( dword_661FF4 )
  {
    case 0:
      rf_gameplay_draw_panel_and_priority_rows((int)unk_6F5FF8);
      break;
    case 1:
      rf_performance_draw_panel((int)unk_6F5FF8);
      break;
    case 2:
      rf_audio_draw_panel((int)unk_6F5FF8);
      break;
    case 3:
      rf_controls_draw_panel((int)unk_6F5FF8);
      break;
    default:
      break;
  }
  unk_6F6004 = unk_6F601C * rf_frame_delta_seconds + unk_6F6004;
  if ( unk_6F6004 <= (double)rf_main_menu_open_x )
  {
    if ( unk_6F6004 < (double)rf_main_menu_closed_x )
    {
      unk_6F601C = 0.0;
      unk_6F6004 = (float)rf_main_menu_closed_x;
    }
  }
  else
  {
    unk_6F601C = 0.0;
    unk_6F6004 = (float)rf_main_menu_open_x;
  }
  v2 = (int)unk_6F6004;
  v1 = rf_main_menu_first_enabled_row_y;
  for ( i = 0; i < 5; ++i )
  {
    if ( unk_6F6119[68 * i] )
    {
      unk_6F611C[17 * i] = v2;
      unk_6F6120[17 * i] = v1;
      rf_ui_image_button_draw((int)&unk_6F6110 + 68 * i);
      v1 += rf_main_menu_row_step_y;
    }
  }
  return rf_ui_draw_side_bars_and_overlays();
}

