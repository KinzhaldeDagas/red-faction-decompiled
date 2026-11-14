// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004595D0 rf_main_menu_update_layout_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Reads no stack arguments, although4597E0 passes a byte-valued DWORD. Resets full viewport then4589C0 scrolling background. Repeated LIVE getters gate
// title/status work: pending panel neither5 nor4 AND current panel!=15. Admitted titleX=FLOAT32(velocity*frameDelta+oldTitleX); ordered titleX<signed lower125 clamps to lower and clears
// velocity; ordered titleX>signed DWORD6F29C8 clamps upper and clears velocity; equality retains velocity. Unordered comparisons preserve NaN through both tests. Converts titleX via605F00 into
// title DWORD6F2C8C, draws title4710E0 and label4703F0. Independently integrates currentX toFLOAT32 every invocation; ordered X>signed openX clamps open and zeroes X velocity,
// otherwise ordered X<signed closedX clamps closed and zeroes it. Equality/unordered leave velocity and value. Converts X via605F00; row starts signed661E48=58. If LIVE pending
// not5/4, each nonzero enabled BYTE6F2A61+68*i for8 records gets X/Y fields+12/+16, is drawn, and rowY increases signed661E4C=61 with32-bit wrap only for enabled rows. Draw
// bars458AA0 and disabled-overlay458F20. Finally LIVE pending5/4 enables mouse centering via58AD90(1), then45A110(0); otherwise no final background call. No generic clamp
// finite-check, temporal snapshot of panel globals, interaction admission or normalized return; EAX from final getter/helper.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Axis correction verified against native coordinate helpers46FC70/46FCA0 and title initialization: animated title field6F2C8C is receiver6F2C80+12, X.
// Current6F29D8 and velocity6F2A08 are title X; title Y at+16 remains a separate constructor coordinate. Shared661E50 is an opening transition speed, not a universal vertical speed.
// Prior detailed contract retained with corrected axes.
int rf_main_menu_update_layout_and_draw()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-Ch]
  int v2; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  rf_renderer_reset_viewport_full_screen();
  rf_ui_draw_scrolling_mars_background();
  if ( rf_ui_pending_panel_id_get() != 5 && rf_ui_pending_panel_id_get() != 4 && rf_ui_panel_stack_current_id() != 15 )
  {
    rf_main_menu_title_current_x = rf_main_menu_title_x_velocity * rf_frame_delta_seconds + rf_main_menu_title_current_x;
    if ( rf_main_menu_title_current_x >= (double)rf_main_menu_title_x_lower_bound )
    {
      if ( rf_main_menu_title_current_x > (double)unk_6F29C8 )
      {
        rf_main_menu_title_x_velocity = 0.0;
        rf_main_menu_title_current_x = (float)unk_6F29C8;
      }
    }
    else
    {
      rf_main_menu_title_x_velocity = 0.0;
      rf_main_menu_title_current_x = (float)rf_main_menu_title_x_lower_bound;
    }
    unk_6F2C8C = (int)rf_main_menu_title_current_x;
    rf_ui_image_button_draw((int)dword_6F2C80);
    rf_ui_label_render((int)dword_6F2A18);
  }
  rf_main_menu_current_x = rf_main_menu_x_velocity * rf_frame_delta_seconds + rf_main_menu_current_x;
  if ( rf_main_menu_current_x <= (double)rf_main_menu_open_x )
  {
    if ( rf_main_menu_current_x < (double)rf_main_menu_closed_x )
    {
      rf_main_menu_x_velocity = 0.0;
      rf_main_menu_current_x = (float)rf_main_menu_closed_x;
    }
  }
  else
  {
    rf_main_menu_x_velocity = 0.0;
    rf_main_menu_current_x = (float)rf_main_menu_open_x;
  }
  v2 = (int)rf_main_menu_current_x;
  v1 = rf_main_menu_first_enabled_row_y;
  if ( rf_ui_pending_panel_id_get() != 5 && rf_ui_pending_panel_id_get() != 4 )
  {
    for ( i = 0; i < 8; ++i )
    {
      if ( unk_6F2A61[68 * i] )
      {
        unk_6F2A64[17 * i] = v2;
        unk_6F2A68[17 * i] = v1;
        rf_ui_image_button_draw((int)&rf_main_menu_buttons + 68 * i);
        v1 += rf_main_menu_row_step_y;
      }
    }
    rf_ui_draw_side_bars_and_overlays();
    rf_ui_debug_build_overlay_disabled();
  }
  if ( rf_ui_pending_panel_id_get() == 5 || (result = rf_ui_pending_panel_id_get(), result == 4) )
  {
    rf_mouse_set_centering_permission_byte(1);
    return rf_ui_draw_mars_background_if_zero_flag(0);
  }
  return result;
}

